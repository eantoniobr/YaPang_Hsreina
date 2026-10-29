// The JP 983 effect interpreter (JpFxInterpreter.h; JP RTTI name
// FxInterpreter), from the JP exe's bodies (node scripts/disasm.ts --jp
// 0x<va>).
#include "JpFxInterpreter.h"

#include <stdlib.h>
#include <string.h>

#include <algorithm>

#include "fxbox.h"
#include "fxsequence.h"
#include "fxspray.h"
#include "partsinfo.h"
#include "wbone.h"
#include "wpuppet.h"
#include "wresrcmng.h"

class WMatrix;

extern WMatrix g_camera;

// The script words (commonutil.cpp; not declared in commonutil.h yet). Both
// skip leading blanks and return the position after the word read;
// GetCharsTillSpace returns NULL at the end of the script.
const char* GetStrConst(const char* pSrc, char* pDest);
const char* GetCharsTillSpace(const char* pSrc, char* pDest);

// lib: 0x88e830, 0x883b40 (the scalar deleting destructors)

// The live instances (JP 0xe7d5c4).
int JpFxInterpreter::s_instanceCount = 0;

namespace {

// The JP Attacher's inequality (both limits, then the four matrix /
// offset pointers); KR fx.h has no such member.
// 0x878d60
bool AttacherDiffers(const Attacher& a, const Attacher& b) {
	if (a.m_fLimitA == b.m_fLimitA && a.m_fLimitB == b.m_fLimitB) {
		for (int i = 0; i < 4; ++i) {
			if (a.m_pMatrix[i] != b.m_pMatrix[i] || a.m_pOffset[i] != b.m_pOffset[i])
				return true;
		}
		return false;
	}
	return true;
}

// GetCharsTillSpace with the end of the script as an empty string rather
// than NULL (the JP reads on).
const char* ReadPlainWord(const char* script, char* word) {
	const char* next = GetCharsTillSpace(script, word);
	return next != NULL ? next : "";
}

// The script words AttachRange / AttachFrame accept: 1 to 63 characters.
bool IsWordLength(const char* word) {
	size_t len = strlen(word);
	return len != 0 && len < 0x40;
}

} // namespace

// The functor of ResetPartEffect's std::for_each.
// lib: 0x8868e0 (std::for_each<std::list<void*>::iterator, JpFxDetachFn>, the
// operator() below inlined)
struct JpFxDetachFn {
	explicit JpFxDetachFn(JpFxInterpreter* owner) : m_owner(owner) {}
	void operator()(void* fx) const;
	JpFxInterpreter* m_owner;
};

// 0x87f2d0
void JpFxInterpreter::SetFxBox(CFxBox* fxBox) {
	if (fxBox != NULL)
		m_fxBox = fxBox;
	if (m_fxBox != NULL) {
		m_fxBox->Init(g_resrcmng);
		m_fxBox->SetCamera(&g_camera);
		// Not written: the JP then sets the box's frame time (CFxBox +4,
		// KR m_frameTime) to 33.333332f (0xcff420); the member is protected
		// in fxbox.h and this class is not its friend. The box's constructor
		// already sets 33.333f.
	}
}

// 0x880d40 (the callback 0x880c10 is the vcall thunk of slot 1)
void JpFxInterpreter::RegisterCallback(CFxBox* fxBox) {
	sFxKeeper keeper;
	keeper.m_pKeeper = this;
	keeper.m_pfnCallBack = &CFxKeeper::EmptyFx;
	if (fxBox != NULL)
		fxBox->AddFxKeeper(keeper);
	else
		WSingleton<CFx>::Instance()->AddFxKeeper(keeper);
}

// 0x883010
JpFxInterpreter::sFxInfo::~sFxInfo() {
}

// 0x8846e0
JpFxInterpreter::sFxInfo::sFxInfo(int effectId, int id, int type, int group, void* fx, const Attacher* attacher, const char* name, bool flag, int param, const char* token)
	: m_unknown20(true), m_effectId(effectId), m_group(group), m_id(id), m_type(type), m_fx(fx),
	  m_attacher(*attacher), m_unknown7c(flag), m_param(param), m_unknown84(false), m_unknown85(true) {
	if (name != NULL)
		m_name.assign(name, strlen(name));
	if (token != NULL)
		m_token.assign(token, strlen(token));
}

// 0x8847e0
JpFxInterpreter::sFxInfo::sFxInfo(int id, int type, int group, const Attacher* attacher, const char* name, int param, const char* token)
	: m_unknown20(true), m_effectId(0), m_group(group), m_id(id), m_type(type), m_fx(NULL),
	  m_attacher(*attacher), m_unknown7c(false), m_param(param), m_unknown84(false), m_unknown85(true) {
	if (name != NULL)
		m_name.assign(name, strlen(name));
	if (token != NULL)
		m_token.assign(token, strlen(token));
}

// 0x8848e0
bool JpFxInterpreter::sFxInfo::IsSame(const sFxInfo& other) const {
	if (m_id != other.m_id || m_type != other.m_type || m_group != other.m_group)
		return false;
	if (m_name.compare(other.m_name) != 0)
		return false;
	if (m_token.compare(other.m_token) != 0)
		return false;
	if (AttacherDiffers(m_attacher, other.m_attacher))
		return false;
	return m_unknown7c == other.m_unknown7c;
}

// 0x884ac0
bool JpFxInterpreter::IsSameFx(sFxInfo query, const sFxInfo* stored) const {
	return query.IsSame(*stored);
}

// 0x884c80
void JpFxInterpreter::ResetFxInfo(void* fx) {
	if (fx != NULL) {
		std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator it = m_fxInfos.find(fx);
		if (it != m_fxInfos.end())
			it->second.reset();
	}
}

// 0x884e10
void JpFxInterpreter::OnFxDeleted(void* fx) {
	if (fx != NULL) {
		std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator it = m_fxInfos.find(fx);
		if (it != m_fxInfos.end() && it->second.use_count() > 0)
			it->second.reset();
	}
}

// Port only: KR CFxKeeper names slot 1 EmptyFx; the JP slot 1 is
// OnFxDeleted itself.
void JpFxInterpreter::EmptyFx(void* fx) {
	OnFxDeleted(fx);
}

// 0x885570
void* JpFxInterpreter::FindSpray(std::string name, const char* token, const Attacher* attacher, int partTid, int layer, int param) {
	if ((unsigned int)layer < 4 && m_partEffects[layer].size() != 0) {
		std::map<int, std::list<void*> >::iterator it = m_partEffects[layer].find(partTid);
		if (it != m_partEffects[layer].end()) {
			for (std::list<void*>::iterator fx = it->second.begin(); fx != it->second.end(); ++fx) {
				void* effect = *fx;
				std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator info = m_fxInfos.find(effect);
				if (info != m_fxInfos.end() && info->second.get() != NULL) {
					sFxInfo* stored = info->second.get();
					if (IsSameFx(sFxInfo(stored->m_id, EFFECT_SPRAY, stored->m_group, attacher, name.c_str(), param, token), stored))
						return effect;
				}
			}
		}
	}
	return NULL;
}

// 0x8856c0
void* JpFxInterpreter::FindSequence(std::string name, const char* token, const Attacher* attacher, int partTid, int layer, int param) {
	if ((unsigned int)layer < 4 && m_partEffects[layer].size() != 0) {
		std::map<int, std::list<void*> >::iterator it = m_partEffects[layer].find(partTid);
		if (it != m_partEffects[layer].end()) {
			for (std::list<void*>::iterator fx = it->second.begin(); fx != it->second.end(); ++fx) {
				void* effect = *fx;
				std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator info = m_fxInfos.find(effect);
				if (info != m_fxInfos.end() && info->second.get() != NULL) {
					sFxInfo* stored = info->second.get();
					if (IsSameFx(sFxInfo(stored->m_id, EFFECT_SEQUENCE, stored->m_group, attacher, name.c_str(), param, token), stored))
						return effect;
				}
			}
		}
	}
	return NULL;
}

// 0x885840
void JpFxInterpreter::DetachEffect(void* fx, int type, bool releaseInfo) {
	if (fx == NULL)
		return;
	if (m_fxBox != NULL) {
		bool sequence = type == EFFECT_SEQUENCE;
		if (type == EFFECT_NONE) {
			if (m_fxBox->FindSpray(static_cast<CFxSpray*>(fx)))
				type = EFFECT_SPRAY;
			sequence = m_fxBox->FindSequence(static_cast<CFxSequence*>(fx));
		}
		if (sequence)
			m_fxBox->DeleteSequence(static_cast<CFxSequence*>(fx), true);
		else if (type == EFFECT_SPRAY)
			m_fxBox->DeleteSpray(static_cast<CFxSpray*>(fx));
	} else {
		CFx* fxs = WSingleton<CFx>::Instance();
		if (fxs == NULL)
			return;
		bool sequence = type == EFFECT_SEQUENCE;
		if (type == EFFECT_NONE) {
			if (fxs->FindSpray(static_cast<CFxSpray*>(fx)))
				type = EFFECT_SPRAY;
			sequence = fxs->FindSequence(static_cast<CFxSequence*>(fx));
		}
		if (sequence)
			fxs->CloseSequence(static_cast<CFxSequence*>(fx), true);
		else if (type == EFFECT_SPRAY)
			fxs->CloseSpray(static_cast<CFxSpray*>(fx));
	}
	if (releaseInfo)
		ResetFxInfo(fx);
}

void JpFxDetachFn::operator()(void* fx) const {
	m_owner->DetachEffect(fx, JpFxInterpreter::EFFECT_NONE, true);
}

// 0x887c10
void JpFxInterpreter::ResetPartEffect(int layer, int partTid) {
	if ((unsigned int)layer < 4) {
		std::map<int, std::list<void*> >::iterator it = m_partEffects[layer].find(partTid);
		if (it != m_partEffects[layer].end()) {
			std::for_each(it->second.begin(), it->second.end(), JpFxDetachFn(this));
			it->second.clear();
		}
	}
}

// 0x887cb0
void JpFxInterpreter::ClearLayerPartTids(int layer) {
	int first = 0;
	int last = 4;
	if (layer > -1 && layer < 4) {
		first = layer;
		last = layer + 1;
	}
	for (int i = first; i < last; ++i) {
		for (std::list<int>::iterator tid = m_layerPartTids[i].begin(); tid != m_layerPartTids[i].end(); ++tid) {
			std::map<int, std::list<void*> >::iterator it = m_partEffects[i].find(*tid);
			if (it != m_partEffects[i].end())
				ResetPartEffect(i, it->first);
		}
		m_layerPartTids[i].clear();
	}
}

// 0x887f80
void JpFxInterpreter::ReleasePartEffects() {
	for (std::list<RF_SHARED_PTR<sFxInfo> >::iterator it = m_paramFxInfos.begin(); it != m_paramFxInfos.end(); ++it)
		it->reset();
	m_paramFxInfos.clear();
}

// 0x888d40
int JpFxInterpreter::GetEffectType(std::string name) {
	if (name.size() == 0 || name.size() >= 0x40)
		return EFFECT_NONE;
	std::string::size_type dot = name.rfind('.');
	std::string ext(name.begin() + (dot + 1), name.end());
	int type = EFFECT_NONE;
	if (ext.size() != 0 && ext.size() >= 3) {
		if (ext.compare("seq") == 0)
			type = EFFECT_SEQUENCE;
		else if (ext == "spr")
			type = EFFECT_SPRAY;
	}
	return type;
}

// 0x888f00. 0x888eb0, inlined here and in StopSprays, detaches the effect
// of an info; an info with an id (sFxInfo::m_id) then clears m_unknown85
// (with an id and releaseInfo set the JP calls 0x887ef0 on m_param instead;
// neither caller passes that).
void JpFxInterpreter::StopLayerEffect(int effectId, int layer) {
	if ((unsigned int)layer >= 4)
		return;
	for (std::map<int, std::list<void*> >::iterator part = m_partEffects[layer].begin(); part != m_partEffects[layer].end(); ++part) {
		std::list<void*>& effects = part->second;
		for (std::list<void*>::iterator fx = effects.begin(); fx != effects.end();) {
			// The kept info, else the one of m_paramFxInfos with this effect
			// (0x884cc0, 0x883d70). A shared copy: the box's delete callback
			// (OnFxDeleted) releases the kept one.
			RF_SHARED_PTR<sFxInfo> info;
			std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator kept = m_fxInfos.find(*fx);
			if (kept != m_fxInfos.end())
				info = kept->second;
			if (info.get() == NULL) {
				for (std::list<RF_SHARED_PTR<sFxInfo> >::iterator it = m_paramFxInfos.begin(); it != m_paramFxInfos.end(); ++it) {
					if (it->get() != NULL && (*it)->m_fx == *fx) {
						info = *it;
						break;
					}
				}
			}
			if (info.get() != NULL && info->m_effectId == effectId) {
				DetachEffect(info->m_fx, info->m_type, info->m_id == 0);
				if (info->m_id != 0)
					info->m_unknown85 = false;
				fx = effects.erase(fx);
			} else {
				++fx;
			}
		}
	}
}

// 0x8890f0
void JpFxInterpreter::ReleaseEffects() {
	for (std::map<void*, RF_SHARED_PTR<sFxInfo> >::iterator it = m_fxInfos.begin(); it != m_fxInfos.end(); ++it)
		it->second.reset();
	m_fxInfos.clear();
}

// 0x889df0
void JpFxInterpreter::StopEffect(int effectId) {
	for (int layer = 0; layer < 4; ++layer)
		StopLayerEffect(effectId, layer);
}

// 0x88aa60
bool JpFxInterpreter::PlaySequence(const char* name, const WVector* position) {
	int type = GetEffectType(name);
	std::map<std::string, void*>::iterator it = m_playedEffects.find(name);
	void* previous = it != m_playedEffects.end() ? it->second : NULL;
	switch (type) {
	case EFFECT_SPRAY: {
		CFxSpray* spray = static_cast<CFxSpray*>(previous);
		if (spray != NULL && WSingleton<CFx>::Instance()->FindSpray(spray)) {
			WSingleton<CFx>::Instance()->CloseSpray(spray);
			m_playedEffects[name] = NULL;
		}
		spray = WSingleton<CFx>::Instance()->OpenSpray(name);
		if (spray == NULL)
			return false;
		spray->m_pos = *position;
		m_playedEffects[name] = spray;
		// Not written: for "wind_change1.spr", "wind_change4.spr" and
		// "wind_change9.spr" (0xd22dfc / 0xd22e10 / 0xd22e24) the JP then
		// sets the spray's rotation (0x880c50: the 0x30 bytes at +0x1160,
		// KR CFxSpray::m_matrix) to a random one built by 0x6c8080 on the
		// object 0x6cc5f0 returns (0xe78ff4), neither decompiled. No lobby
		// effect is one of them.
		return true;
	}
	case EFFECT_SEQUENCE: {
		CFxSequence* sequence = static_cast<CFxSequence*>(previous);
		if (sequence != NULL && WSingleton<CFx>::Instance()->FindSequence(sequence)) {
			WSingleton<CFx>::Instance()->CloseSequence(sequence, false);
			m_playedEffects[name] = NULL;
		}
		sequence = WSingleton<CFx>::Instance()->OpenSequence(name, true);
		if (sequence == NULL)
			return false;
		sequence->Pos() = *position;
		m_playedEffects[name] = sequence;
		return true;
	}
	}
	return false;
}

// 0x88b140
void JpFxInterpreter::ClearPartEffects(int layer) {
	int first = 0;
	int last = 4;
	if (layer > -1 && layer < 4) {
		first = layer;
		last = layer + 1;
	}
	for (int i = first; i < last; ++i) {
		for (std::map<int, std::list<void*> >::iterator it = m_partEffects[i].begin(); it != m_partEffects[i].end(); ++it)
			ResetPartEffect(i, it->first);
		m_partEffects[i].clear();
	}
}

// 0x88b1f0
void JpFxInterpreter::SetFxInfo(void* fx, sFxInfo* info) {
	if (fx != NULL && info != NULL) {
		ResetFxInfo(fx);
		m_fxInfos[fx] = RF_SHARED_PTR<sFxInfo>(info);
	}
}

// 0x88b8d0
void JpFxInterpreter::StopSprays(int layer) {
	int first = 0;
	int last = 4;
	if (layer > -1 && layer < 4) {
		first = layer;
		last = layer + 1;
	}
	for (int i = first; i < last; ++i) {
		std::map<std::string, std::list<int> >* maps[2] = { &m_namedParamsA[i], &m_namedParamsB[i] };
		for (int m = 0; m < 2; ++m) {
			for (std::map<std::string, std::list<int> >::iterator it = maps[m]->begin(); it != maps[m]->end(); ++it) {
				for (std::list<int>::iterator param = it->second.begin(); param != it->second.end(); ++param) {
					// 0x8890a0: every info of m_paramFxInfos started with this
					// param, through 0x888eb0 without releaseInfo.
					if (*param == 0)
						continue;
					for (std::list<RF_SHARED_PTR<sFxInfo> >::iterator info = m_paramFxInfos.begin(); info != m_paramFxInfos.end(); ++info) {
						RF_SHARED_PTR<sFxInfo> stopped = *info;
						if (stopped.get() == NULL || stopped->m_param != *param)
							continue;
						DetachEffect(stopped->m_fx, stopped->m_type, false);
						if (stopped->m_id != 0)
							stopped->m_unknown85 = false;
						stopped->m_fx = NULL;
					}
				}
				it->second.clear();
			}
		}
	}
}

// 0x88c420
void JpFxInterpreter::StopAllEffects(int effectId) {
	ClearPartEffects(effectId);
	ClearLayerPartTids(effectId);
	StopSprays(effectId);
	if (effectId == -1)
		m_nextId = 1;
}

// 0x88c6b0 (+ chunk 0x88c74c)
void JpFxInterpreter::InitTokens() {
	m_scriptTokens.push_back("*fx");
	m_scriptTokens.push_back("*playif");
	m_scriptTokens.push_back("*fxstop");
	m_scriptCallTokens.push_back("*fx(");
	m_scriptCallTokens.push_back("*playif(");
	m_scriptCallTokens.push_back("*fxstop(");
}

// 0x88ca30
bool JpFxInterpreter::AddPartEffect(int id, void* fx, int partTid, int layer, bool flag) {
	(void)id;
	if (flag || (unsigned int)layer >= 4)
		return false;
	std::map<int, std::list<void*> >::iterator it = m_partEffects[layer].find(partTid);
	if (it != m_partEffects[layer].end()) {
		it->second.push_back(fx);
		return true;
	}
	std::list<void*> effects;
	effects.push_back(fx);
	m_partEffects[layer].insert(std::pair<const int, std::list<void*> >(partTid, effects));
	return true;
}

// 0x88cb80
bool JpFxInterpreter::StartFx(int id, int type, void* fx, const Attacher* attacher, const char* name, int partTid, int layer, int param5, const char* token) {
	if (param5 != 0)
		return false;
	if (!AddPartEffect(id, fx, partTid, layer, false))
		return false;
	SetFxInfo(fx, new sFxInfo(m_nextId, 0, type, partTid, fx, attacher, name, false, 0, token));
	if (partTid != 0)
		m_layerPartTids[layer].push_back(partTid);
	return true;
}

// 0x88d3c0
int JpFxInterpreter::AddEffect(const char* name, const char* token, const Attacher* attacher, int type, int param5, int partTid, int param7, bool keepId) {
	if (name == NULL || attacher == NULL)
		return 0;
	if (type == EFFECT_SPRAY) {
		void* fx = LoadFx(name, attacher, EFFECT_SPRAY, param5, true);
		if (fx == NULL)
			return 0;
		StartFx(m_nextId, EFFECT_SPRAY, fx, attacher, name, partTid, param7, param5, token);
		int id = m_nextId;
		if (!keepId)
			m_nextId = id + 1;
		return id;
	}
	if (type == EFFECT_SEQUENCE) {
		void* fx = LoadFx(name, attacher, EFFECT_SEQUENCE, param5, true);
		if (fx == NULL)
			return 0;
		StartFx(m_nextId, EFFECT_SEQUENCE, fx, attacher, name, partTid, param7, param5, token);
		int id = m_nextId;
		if (!keepId)
			m_nextId = id + 1;
		return id;
	}
	return 0;
}

// The body of the scalar deleting destructor 0x88e830. Not written yet:
// the 0x88a1c0 pass over the map arrays at +0xa8 / +0xe8 (after
// ReleasePartEffects) and 0x888060 on the +0x1d0 map (after the ClearAll),
// whose element types are not traced (PADDING in the header).
// 0x88dee0
JpFxInterpreter::~JpFxInterpreter() {
	--s_instanceCount;
	StopAllEffects(-1);
	ReleaseEffects();
	ReleasePartEffects();
	if (m_fxBox != NULL)
		m_fxBox->ClearAll(false);
	else
		WSingleton<CFx>::Instance()->ClearAll(s_instanceCount != 0);
}

// 0x88e520
JpFxInterpreter::JpFxInterpreter(CFxBox* fxBox, int firstId)
	: m_nextId(firstId + 1), m_unknown158(1) {
	m_fxBox = fxBox;
	InitTokens();
	RegisterCallback(fxBox);
	if (fxBox != NULL)
		SetFxBox(fxBox);
	++s_instanceCount;
}

// Port body (JP 0x883bb0, JpFxInterpreter.h): the CFx singleton path is the
// JP one; the own-box path (m_fxBox != NULL: CFxBox::LoadSpray /
// LoadSequence, the attacher copied into the effect's protected members,
// AddSpray / AddSequence) needs CFxSpray / CFxSequence to befriend this
// class and returns NULL (G7) until they do. The lobby avatar's host has no
// box.
void* JpFxInterpreter::LoadFx(const char* name, const Attacher* attacher, int type, int param5, bool flag) {
	if ((int)strlen(name) < 5)
		return NULL;
	if (m_fxBox != NULL)
		return NULL;
	void* fx = WSingleton<CFx>::Instance()->Attach(*attacher, name, param5 != 0, NULL);
	if (fx == NULL)
		return NULL;
	if (type == EFFECT_SPRAY)
		static_cast<CFxSpray*>(fx)->SetActive(flag);
	else
		static_cast<CFxSequence*>(fx)->SetActive(flag, false);
	return fx;
}

// 0x8822c0
bool JpFxInterpreter::NextToken(const char** script, int* format, int* kind) const {
	*kind = 3;
	for (int f = 1; f >= 0; --f) {
		const std::vector<std::string>& tokens = f == 1 ? m_scriptCallTokens : m_scriptTokens;
		for (int k = 0; k < 3 && k < (int)tokens.size(); ++k) {
			const char* found = strstr(*script, tokens[k].c_str());
			if (found != NULL) {
				*format = f;
				*kind = k;
				*script = found;
				return true;
			}
		}
	}
	return false;
}

// 0x882350
bool JpFxInterpreter::ParseCondition(const char** script, char* condition, int format, int kind) const {
	char word[0x40];
	word[0] = '\0';
	const char* next;
	if (format == 0)
		next = ReadPlainWord(*script + m_scriptTokens[kind].size(), word);
	else if (format == 1)
		next = GetStrConst(*script + m_scriptCallTokens[kind].size(), word);
	else
		return false;
	if (!IsWordLength(word) || word[0] != '#')
		return false;
	*script = next;
	strcpy(condition, word + 1);
	return true;
}

// 0x88c8b0
bool JpFxInterpreter::ParseFxName(const char** script, char* name, std::vector<std::string>* tokens, int format, int kind, bool afterCondition) const {
	const char* next;
	if (format == 1) {
		if (afterCondition)
			next = GetStrConst(*script, name);
		else
			next = GetStrConst(*script + m_scriptCallTokens[kind].size(), name);
	} else if (format == 0) {
		if (afterCondition)
			next = GetStrConst(*script, name);
		else
			next = ReadPlainWord(*script + m_scriptTokens[kind].size(), name);
	} else {
		return false;
	}
	*script = next;
	// The "@" words: ` "@token"`, the '@' two characters on (the JP reads
	// next[2] unchecked).
	while (next[0] != '\0' && next[1] != '\0' && next[2] == '@') {
		char word[0x40];
		word[0] = '\0';
		next = GetStrConst(next, word);
		*script = next;
		if (IsWordLength(word))
			tokens->push_back(std::string(word));
	}
	return true;
}

// 0x883b70
bool JpFxInterpreter::HasLayerPartTid(int layer, int partTid) const {
	if (partTid == 0 || (unsigned int)layer >= 4)
		return false;
	for (std::list<int>::const_iterator tid = m_layerPartTids[layer].begin(); tid != m_layerPartTids[layer].end(); ++tid) {
		if (*tid == partTid)
			return true;
	}
	return false;
}

// 0x884b20. Not written: the JP looks up the map at +0x134 (0x24-byte
// nodes) with the key at +0x1cc and returns false when one of the 0x24-byte
// elements of the vector found there holds the info's m_name; neither
// member is traced (PADDING in the header) and nothing in the port fills
// them, so every effect is shown.
bool JpFxInterpreter::IsFxShown(const sFxInfo* info) const {
	(void)info;
	return true;
}

// 0x884d50
JpFxInterpreter::sFxInfo* JpFxInterpreter::FindParamFxInfo(const sFxInfo* info) const {
	for (std::list<RF_SHARED_PTR<sFxInfo> >::const_iterator it = m_paramFxInfos.begin(); it != m_paramFxInfos.end(); ++it) {
		if (it->get() != NULL && (*it)->IsSame(*info))
			return it->get();
	}
	return NULL;
}

// 0x887db0
JpFxInterpreter::sFxInfo* JpFxInterpreter::AddParamFxInfo(sFxInfo* info, bool* added) {
	*added = false;
	if (info == NULL)
		return NULL;
	sFxInfo* kept = FindParamFxInfo(info);
	if (kept != NULL) {
		delete info;
		return kept;
	}
	info->m_unknown84 = false;
	info->m_unknown85 = false;
	m_paramFxInfos.push_back(RF_SHARED_PTR<sFxInfo>(info));
	*added = true;
	return info;
}

// 0x88cc70
void JpFxInterpreter::AddNamedParamA(int param, const char* name, int layer) {
	m_namedParamsA[layer][name].push_back(param);
}

// 0x88ced0
void JpFxInterpreter::AddNamedParamB(int param, const char* name, int layer) {
	m_namedParamsB[layer][name].push_back(param);
}

// 0x88d230
int JpFxInterpreter::AttachEffect(const char* name, const Attacher* attacher, int type, int param5, int partTid, int layer, bool keepId) {
	if (name == NULL || attacher == NULL)
		return 0;
	if (type != EFFECT_SPRAY && type != EFFECT_SEQUENCE)
		return 0;
	void* fx = LoadFx(name, attacher, type, param5, true);
	if (fx == NULL)
		return 0;
	if (AddPartEffect(m_nextId, fx, partTid, layer, param5 != 0))
		SetFxInfo(fx, new sFxInfo(m_nextId, 0, type, partTid, fx, attacher, name, param5 != 0, 0, NULL));
	int id = m_nextId;
	if (!keepId)
		m_nextId = id + 1;
	return id;
}

// 0x88d4a0
int JpFxInterpreter::AddPlayIf(const char* condition, const char* name, const char* token, const Attacher* attacher, int type, bool flag, int partTid, int layer, bool keepId, bool keepParam) {
	if (condition == NULL || name == NULL || attacher == NULL || (unsigned int)layer >= 4)
		return 0;
	bool added = false;
	sFxInfo* info = AddParamFxInfo(new sFxInfo(m_nextId, 1, type, partTid, NULL, attacher, name, flag, m_unknown158, token), &added);
	if (info == NULL)
		return 0;
	AddNamedParamA(info->m_param, condition, layer);
	if (token != NULL && token[0] != '\0')
		AddNamedParamB(info->m_param, token, layer);
	if (!added)
		return info->m_param;
	if (!keepId)
		++m_nextId;
	int param = m_unknown158;
	if (!keepParam)
		m_unknown158 = param + 1;
	return param;
}

// 0x88d610
int JpFxInterpreter::AddTokenFx(const char* token, const char* name, const Attacher* attacher, int type, bool flag, int partTid, int layer, bool keepId, bool keepParam) {
	if (token == NULL || name == NULL || attacher == NULL || (unsigned int)layer >= 4)
		return 0;
	bool added = false;
	sFxInfo* info = AddParamFxInfo(new sFxInfo(m_nextId, 2, type, partTid, NULL, attacher, name, flag, m_unknown158, token), &added);
	if (info == NULL)
		return 0;
	AddNamedParamB(info->m_param, token, layer);
	if (!added)
		return info->m_param;
	if (!keepId)
		++m_nextId;
	int param = m_unknown158;
	if (!keepParam)
		m_unknown158 = param + 1;
	return param;
}

// 0x88d8f0
bool JpFxInterpreter::StartParamFx(sFxInfo* info, int layer) {
	if (info->m_unknown85)
		return false;
	bool shown = IsFxShown(info);
	if (info->m_type == EFFECT_SPRAY || info->m_type == EFFECT_SEQUENCE) {
		void* fx = LoadFx(info->m_name.c_str(), &info->m_attacher, info->m_type, info->m_unknown7c, shown);
		if (fx != NULL) {
			info->m_fx = fx;
			info->m_unknown85 = true;
			info->m_unknown20 = shown;
			AddPartEffect(info->m_effectId, fx, info->m_group, layer, info->m_unknown7c);
		}
	}
	return info->m_fx != NULL;
}

// 0x88dc90. Stopping is 0x888eb0 without releaseInfo, as in StopSprays.
void JpFxInterpreter::SwitchParamFx(int param, bool start, int layer) {
	if (param == 0 || (unsigned int)layer >= 4)
		return;
	for (std::list<RF_SHARED_PTR<sFxInfo> >::iterator it = m_paramFxInfos.begin(); it != m_paramFxInfos.end(); ++it) {
		sFxInfo* info = it->get();
		if (info == NULL || info->m_param != param)
			continue;
		if (start) {
			if (info->m_token.size() == 0 || m_layerTokens[layer].compare(info->m_token) == 0)
				StartParamFx(info, layer);
		} else {
			DetachEffect(info->m_fx, info->m_type, false);
			if (info->m_id != 0)
				info->m_unknown85 = false;
			info->m_fx = NULL;
		}
		info->m_unknown84 = start;
	}
}

// 0x88e210 (+ its std::for_each 0x88d9b0)
bool JpFxInterpreter::AttachToParts(int mode, const char* name, const char* condition, const std::vector<std::string>* tokens, const std::vector<int>* partTids, const Attacher* attacher, int type, int layer) {
	int result = 0;
	for (std::vector<int>::const_iterator tid = partTids->begin(); tid != partTids->end(); ++tid) {
		switch (mode) {
		case 0:
			result = AttachEffect(name, attacher, type, 0, *tid, layer, true);
			break;
		case 1:
			if (tokens->size() == 0) {
				result = AddPlayIf(condition, name, NULL, attacher, type, false, *tid, layer, true, false);
				break;
			}
			// One m_param for every token: the id advances after the last.
			for (std::vector<std::string>::const_iterator token = tokens->begin(); token != tokens->end(); ++token) {
				bool more = token + 1 != tokens->end();
				result = AddPlayIf(condition, name, token->c_str(), attacher, type, false, *tid, layer, true, more);
				if (result == 0)
					break;
			}
			break;
		case 2:
			for (std::vector<std::string>::const_iterator token = tokens->begin(); token != tokens->end(); ++token) {
				bool more = token + 1 != tokens->end();
				result = AddTokenFx(token->c_str(), name, attacher, type, false, *tid, layer, true, more);
				if (result == 0)
					break;
			}
			break;
		}
	}
	return result != 0;
}

// 0x88ecd0
int JpFxInterpreter::AttachRange(CPetFrame* frame, const float* range, bool checkParts, int layer) {
	if (frame == NULL)
		return 0;
	bool attached = false;
	WPuppet* pet = frame->GetBonePet();
	for (w_bound_box* box = pet->m_bbList.Start(); box != NULL; box = pet->m_bbList.Next()) {
		if (box->info->option == NULL || box->bone == NULL || box->bone->IsInvisible())
			continue;
		const char* script = box->info->option;
		int format = 2;
		int kind = 3;
		while (NextToken(&script, &format, &kind)) {
			char condition[0x40];
			char name[0x40];
			condition[0] = '\0';
			int mode = ParseCondition(&script, condition, format, kind) ? 1 : 0;
			std::vector<std::string> tokens;
			if (!ParseFxName(&script, name, &tokens, format, kind, mode == 1))
				continue;
			int type = GetEffectType(name);
			if (type == EFFECT_NONE)
				continue;
			if (tokens.size() != 0 && mode != 1)
				mode = 2;

			// "&<tid>" words: the first worn one (a part, or an aux part)
			// keeps the command; none of them drops it.
			std::vector<int> partTids;
			if (checkParts) {
				char word[0x40];
				script = GetStrConst(script, word);
				if (!IsWordLength(word) && mode != 1)
					continue;
				bool sawTid = false;
				bool matched = false;
				bool dropped = false;
				while (word[0] == '&') {
					sawTid = true;
					int tid = atoi(word + 1);
					bool worn = frame->GetPartList().FindPart(tid);
					if (worn)
						partTids.push_back(tid);
					if (frame->FindAuxPart(tid)) {
						partTids.push_back(tid);
						matched = true;
						break;
					}
					if (worn) {
						matched = true;
						break;
					}
					script = GetStrConst(script, word);
					if (!IsWordLength(word)) {
						dropped = true;
						break;
					}
				}
				if (dropped || (sawTid && !matched))
					continue;
			}

			Attacher attacher;
			attacher.m_fLimitA = range[0];
			attacher.m_fLimitB = range[1];
			attacher.m_pMatrix[0] = &box->bone->GetMatrix();
			attacher.m_pOffset[0] = &box->info->spherePivot;
			if (partTids.size() == 0)
				partTids.push_back(0);
			attached = AttachToParts(mode, name, condition, &tokens, &partTids, &attacher, type, layer);
		}
	}
	if (attached)
		return m_nextId++;
	return 0;
}

// 0x88f2b0. Not written (G7): two of the "&<tid>" matches, the five tids of
// the player's game state (CSharedDoc 0xe47dbc + 0x69a6 + layer * 0x31c6)
// and the club set's (player non-NULL: its club of GolfClub()'s current
// type, +0xc0 + type * 4, or its +0x4 tid); the lobby avatar passes neither
// a player nor game state.
int JpFxInterpreter::AttachFrame(CPetFrame* frame, const void* player, int layer, bool force, bool playIfOnly) {
	(void)player;
	if (frame == NULL)
		return 0;
	bool attached = false;
	Attacher attacher;
	WPuppet* pet = frame->GetBonePet();
	for (w_bound_box* box = pet->m_bbList.Start(); box != NULL; box = pet->m_bbList.Next()) {
		if (box->info->option == NULL || box->bone == NULL || box->bone->IsInvisible())
			continue;
		const char* script = box->info->option;
		int format = 2;
		int kind = 3;
		while (NextToken(&script, &format, &kind)) {
			char condition[0x40];
			char name[0x40];
			condition[0] = '\0';
			int mode = ParseCondition(&script, condition, format, kind) ? 1 : 0;
			std::vector<std::string> tokens;
			if (!ParseFxName(&script, name, &tokens, format, kind, mode == 1))
				continue;
			if (mode != 1 && playIfOnly)
				continue;
			int type = GetEffectType(name);
			if (type == EFFECT_NONE)
				continue;
			if (tokens.size() != 0 && mode != 1)
				mode = 2;

			std::vector<int> partTids;
			char word[0x40];
			script = GetStrConst(script, word);
			if (!IsWordLength(word) && mode != 1)
				continue;
			bool sawTid = false;
			bool matched = false;
			int tid = 0;
			while (word[0] == '&') {
				sawTid = true;
				tid = atoi(word + 1);
				if (frame->GetPartList().FindPart(tid)) {
					partTids.push_back(tid);
					matched = true;
				}
				if (matched)
					break;
				script = GetStrConst(script, word);
				if (!IsWordLength(word))
					break;
			}
			if (sawTid && !matched)
				continue;
			if (!force && sawTid && HasLayerPartTid(layer, tid))
				continue;

			attacher.m_pMatrix[0] = &box->bone->GetMatrix();
			attacher.m_pOffset[0] = &box->info->spherePivot;
			if (partTids.size() == 0)
				partTids.push_back(0);
			attached = AttachToParts(mode, name, condition, &tokens, &partTids, &attacher, type, layer);
		}
	}
	if (attached)
		return m_nextId++;
	return 0;
}

// 0x88fe40 (+ chunk 0x88fecd; the std::for_each 0x88e300 over the
// condition's params inlined)
bool JpFxInterpreter::BindOwner(const char* name, bool start, int layer) {
	if (name == NULL)
		return false;
	int first = 0;
	int last = 4;
	if (layer > -1 && layer < 4) {
		first = layer;
		last = layer + 1;
	}
	for (int i = first; i < last; ++i) {
		std::map<std::string, std::list<int> >::iterator it = m_namedParamsA[i].find(name);
		if (it == m_namedParamsA[i].end())
			continue;
		for (std::list<int>::iterator param = it->second.begin(); param != it->second.end(); ++param)
			SwitchParamFx(*param, start, i);
	}
	return true;
}
