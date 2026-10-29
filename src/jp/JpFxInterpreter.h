// The JP 983 effect interpreter: JP RTTI name "FxInterpreter"
// (.?AVFxInterpreter@@ 0xe25080, COL 0xd7a3a8, vtable 0xd34928, 2 slots),
// 0x1e0 bytes, code about 0x879000-0x890000. It is a JP rewrite of the KR
// FxInterpreter (yapang fxinterpreter.h, 0x14 bytes), which the JP port
// also compiles, hence the Jp prefix. The lobby avatar (IDummyPlayer +0xd0)
// owns one built with (NULL, 0).
// From the JP exe's bodies (node scripts/disasm.ts --jp 0x<va>).
#ifndef PG_JP_JPFXINTERPRETER_H
#define PG_JP_JPFXINTERPRETER_H

#include <stdint.h>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "defines.h"
#include "padding.h"
#include "fx.h"
#include "RefreshSharedPtr.h"

class CFxBox;
class CPetFrame;
class WVector;

// A CFxKeeper (fxbox.h): RegisterCallback registers it on its box, which
// calls slot 1 (OnFxDeleted here, EmptyFx in KR) for each effect it deletes.
class JpFxInterpreter : public CFxKeeper {
	LAYOUT_CHECK_FRIEND;
public:
	// What an effect is (AddEffect's type; FindSpray matches type 2,
	// FindSequence type 1), as in the KR FxInterpreter::eEffectType.
	enum eEffectType {
		EFFECT_NONE = 0,
		EFFECT_SEQUENCE = 1,                   // ".seq"
		EFFECT_SPRAY = 2                       // ".spr"
	};

	// JP RTTI .?AUsFxInfo@FxInterpreter@@ (vtable 0xd34910, 1 slot), 0x88
	// bytes: what started an effect. m_fxInfos maps each running effect to
	// its own; FindSpray / FindSequence build one for the query and compare.
	struct sFxInfo {
		// 0x8847e0
		sFxInfo(int id, int type, int group, const Attacher* attacher, const char* name, int param, const char* token);
		// 0x8846e0: StartFx's (m_nextId, 0, type, part tid, the effect,
		// attacher, name, false, 0, token).
		sFxInfo(int effectId, int id, int type, int group, void* fx, const Attacher* attacher, const char* name, bool flag, int param, const char* token);
		virtual ~sFxInfo();                    // slot 0 (its scalar deleting destructor is lib)
		// 0x8848e0
		bool IsSame(const sFxInfo& other) const;

		std::string m_name;                    // 0x4, the effect file
		bool m_unknown20;                      // 0x20, 1 from the ctor
		int m_effectId;                        // 0x24, StartFx: the id AddEffect returns; 0 from ctor 0x8847e0
		int m_group;                           // 0x28, compared; role not traced
		int m_id;                              // 0x2c, compared (AddEffect's id)
		int m_type;                            // 0x30, eEffectType
		void* m_fx;                            // 0x34, StartFx: the effect; NULL from ctor 0x8847e0
		std::string m_token;                   // 0x38
		Attacher m_attacher;                   // 0x54, a copy of the caller's
		bool m_unknown7c;                      // 0x7c, 0 from the ctors, compared
		int m_param;                           // 0x80
		bool m_unknown84;                      // 0x84, 0 from the ctor
		bool m_unknown85;                      // 0x85, 1 from the ctor
		PADDING(0x86, 0x88);
	};

	// 0x88e520: fxBox NULL = the effects go to the CFx singleton.
	JpFxInterpreter(CFxBox* fxBox, int firstId);
	virtual ~JpFxInterpreter();                // slot 0 (its scalar deleting destructor is lib)
	// [1] 0x884e10: the box deleted an effect: drops the info kept for it.
	virtual void OnFxDeleted(void* fx);
	// The port's CFxKeeper slot 1 (JP: OnFxDeleted itself); calls OnFxDeleted.
	virtual void EmptyFx(void* fx);

	// 0x88aa60: opens a ".seq" or ".spr" file on the CFx singleton at a
	// world position (not attached), closing the one this name opened
	// before; false when it is neither or could not be opened. The lobby
	// avatar attach 0x566390 plays "avatar_d.seq", the caddie attach
	// 0x560a60 "Talk_Room.seq".
	bool PlaySequence(const char* name, const WVector* position);
	// 0x889df0: stops the effect in each of the four layers.
	void StopEffect(int effectId);
	// 0x88c420: resets the parts' effects of one layer (0..3), or of every
	// layer with -1 (then the ids restart at 1); StopSprays takes the same
	// layer argument.
	void StopAllEffects(int effectId);
	// 0x88ecd0: runs the "*fx" / "*playif" / "*fxstop" commands of the bone
	// pet's bounding-box scripts (w_bound_box_info::option), attaching each
	// effect to its box's bone with range as the attacher's two limits. With
	// checkParts, "&<tid>" words after the effect name keep a command to the
	// frame's parts / aux parts with that tid (the first one worn). Returns
	// the effect id (m_nextId, then advanced) when the last command attached
	// something, 0 otherwise. The lobby avatar passes (FLT_MAX, FLT_MAX), 1, 0.
	int AttachRange(CPetFrame* frame, const float* range, bool checkParts, int layer);
	// 0x88f2b0: the same with a default attacher, the "&<tid>" words always
	// read, and layer also the player index of the tid checks. A "&<tid>"
	// matches a part / aux part of the frame, one of the five tids of the
	// player's game state (CSharedDoc 0xe47dbc + 0x69a6 + layer * 0x31c6) or
	// the club set's (player) club tid; without force, a matched tid StartFx
	// already bound in the layer skips the command. playIfOnly skips every
	// command but "*playif(#cond ...)". The lobby avatar passes (NULL, 0,
	// flag, false).
	int AttachFrame(CPetFrame* frame, const void* player, int layer, bool force, bool playIfOnly);
	// 0x88fe40 (+ chunk 0x88fecd): starts (start) or stops the "*playif"
	// effects registered under the condition name in a layer (-1: every
	// layer); false only for a NULL name. The lobby avatar sends
	// "대천사" and "요정날개" (start, layer 0).
	bool BindOwner(const char* name, bool start, int layer);
	// 0x885570: the running spray (name, token, attacher) bound to part tid
	// in a layer; NULL without one.
	void* FindSpray(std::string name, const char* token, const Attacher* attacher, int partTid, int layer, int param);
	// 0x8856c0: the same for sequences.
	void* FindSequence(std::string name, const char* token, const Attacher* attacher, int partTid, int layer, int param);
	// 0x88d3c0: starts an effect; its id, 0 when it could not be loaded.
	// keepId does not advance the next id.
	int AddEffect(const char* name, const char* token, const Attacher* attacher, int type, int param5, int partTid, int param7, bool keepId);
	// 0x887c10: detaches the effects bound to part tid in a layer.
	void ResetPartEffect(int layer, int partTid);

private:
	friend struct JpFxDetachFn;

	// 0x88c6b0: adds the script tokens ("*playif" ...) to m_scriptTokens and
	// m_scriptCallTokens.
	void InitTokens();
	// 0x880d40: registers this keeper (callback 0x880c10, slot 1) on the box
	// (or on the CFx singleton).
	void RegisterCallback(CFxBox* fxBox);
	// 0x87f2d0: keeps the box and sets its resource manager, camera and
	// frame time.
	void SetFxBox(CFxBox* fxBox);
	// 0x888d40: EFFECT_SEQUENCE for a ".seq" name, EFFECT_SPRAY for ".spr",
	// EFFECT_NONE otherwise (empty or 0x40+ characters too).
	static int GetEffectType(std::string name);
	// 0x884c80: drops the info kept for an effect (its entry stays).
	void ResetFxInfo(void* fx);
	// 0x88b1f0: keeps the info of an effect (owned from then on).
	void SetFxInfo(void* fx, sFxInfo* info);
	// 0x88ca30: binds an effect to part tid in a layer; false for a layer
	// past 3 or with flag set (id is not read).
	bool AddPartEffect(int id, void* fx, int partTid, int layer, bool flag);
	// 0x884ac0: info against stored (the query by value).
	bool IsSameFx(sFxInfo query, const sFxInfo* stored) const;
	// 0x885840: deletes one effect from its box (type: its eEffectType,
	// EFFECT_NONE = look it up), then drops its info when releaseInfo is set.
	void DetachEffect(void* fx, int type, bool releaseInfo);
	// 0x888f00: detaches the effects of one layer started with effectId.
	void StopLayerEffect(int effectId, int layer);
	// 0x88b140: ResetPartEffect on every part of a layer (-1: of every
	// layer), then empties its map.
	void ClearPartEffects(int layer);
	// 0x887cb0: the same for the part tids StartFx bound in a layer, then
	// empties its list.
	void ClearLayerPartTids(int layer);
	// 0x88b8d0: the third pass of StopAllEffects: stops the infos of every
	// value of m_namedParamsA / B in a layer (-1: every layer), then empties
	// those lists.
	void StopSprays(int layer);
	// 0x8890f0: drops every kept info and empties m_fxInfos.
	void ReleaseEffects();
	// 0x887f80: releases every info of m_paramFxInfos (std::for_each
	// 0x8851f0), then empties it.
	void ReleasePartEffects();
	// 0x883bb0: loads the effect file (name, attacher, type, param5, 1).
	// Not decompiled.
	void* LoadFx(const char* name, const Attacher* attacher, int type, int param5, bool flag);
	// 0x88cb80: binds a loaded effect to part tid in a layer and keeps what
	// started it; does nothing (false) when param5 is set, which every
	// lobby AddEffect passes.
	bool StartFx(int id, int type, void* fx, const Attacher* attacher, const char* name, int partTid, int layer, int param5, const char* token);

	// The script commands of AttachRange / AttachFrame. A command is a token
	// (kind: 0 "*fx", 1 "*playif", 2 "*fxstop"; format 0 = m_scriptTokens,
	// space-separated words, 1 = m_scriptCallTokens, quoted words), an
	// optional "#<condition>" word, the effect file name, "@..." words
	// (m_paramFxInfos tokens), then, for AttachRange / AttachFrame, "&<tid>"
	// words. Modes of AttachToParts: 0 a plain effect, 1 a "*playif" under a
	// condition (started later by BindOwner), 2 effects under "@" tokens.
	// 0x8822c0: the next token in *script (call format first, then kind
	// order); moves *script to it.
	bool NextToken(const char** script, int* format, int* kind) const;
	// 0x882350: the "#<condition>" word after the token at *script, without
	// its '#' (63 characters at most); *script moves past it only when found.
	bool ParseCondition(const char** script, char* condition, int format, int kind) const;
	// 0x88c8b0: the effect name after the token (afterCondition: at *script)
	// and the "@" words that follow it, appended to tokens; *script moves
	// past them. false for an unknown format.
	bool ParseFxName(const char** script, char* name, std::vector<std::string>* tokens, int format, int kind, bool afterCondition) const;
	// 0x88e210 (its std::for_each 0x88d9b0 inlined): runs one command for
	// each part tid; whether the last one started something.
	bool AttachToParts(int mode, const char* name, const char* condition, const std::vector<std::string>* tokens, const std::vector<int>* partTids, const Attacher* attacher, int type, int layer);
	// 0x88d230: AddEffect without a token: loads the effect, binds it to
	// part tid in a layer and keeps its info; the effect id (keepId: the next
	// id is not advanced), 0 when it could not be loaded.
	int AttachEffect(const char* name, const Attacher* attacher, int type, int param5, int partTid, int layer, bool keepId);
	// 0x88d4a0: registers a "*playif" effect under a condition (and its
	// token, if any) without loading it; its m_param (a m_unknown158 id, the
	// next one unless keepParam), 0 for bad arguments.
	int AddPlayIf(const char* condition, const char* name, const char* token, const Attacher* attacher, int type, bool flag, int partTid, int layer, bool keepId, bool keepParam);
	// 0x88d610: the same for an effect under a "@" token only (m_id 2).
	int AddTokenFx(const char* token, const char* name, const Attacher* attacher, int type, bool flag, int partTid, int layer, bool keepId, bool keepParam);
	// 0x887db0: keeps info in m_paramFxInfos (added set) unless the same is
	// there already, in which case info is deleted and the kept one returned.
	sFxInfo* AddParamFxInfo(sFxInfo* info, bool* added);
	// 0x884d50: the info of m_paramFxInfos the same as info (IsSame), NULL
	// without one.
	sFxInfo* FindParamFxInfo(const sFxInfo* info) const;
	// 0x88cc70 / 0x88ced0: adds param under name in m_namedParamsA /
	// m_namedParamsB of a layer.
	void AddNamedParamA(int param, const char* name, int layer);
	void AddNamedParamB(int param, const char* name, int layer);
	// 0x883b70: whether StartFx bound part tid in a layer (0..4: the JP
	// tests layer > 4).
	bool HasLayerPartTid(int layer, int partTid) const;
	// 0x88dc90 (the std::for_each functor 0x88e300 of BindOwner): starts or
	// stops the infos of m_paramFxInfos with this m_param in a layer.
	void SwitchParamFx(int param, bool start, int layer);
	// 0x88d8f0: loads the effect of a registered (not running) info and
	// binds it to its part tid; whether it runs.
	bool StartParamFx(sFxInfo* info, int layer);
	// 0x884b20: false when the info's effect name is listed under the
	// current key (+0x1cc) of the map at +0x134; the port has neither, so
	// true.
	bool IsFxShown(const sFxInfo* info) const;

	// 0xe7d5c4: live instances (the destructor clears the CFx effects only
	// with the last one gone).
	static int s_instanceCount;

	// 0x4: CFxKeeper::m_pFxManager, set by the box's AddFxKeeper.
	std::vector<std::string> m_scriptTokens;   // 0x8, InitTokens: "*fx", "*playif", "*fxstop"
	std::vector<std::string> m_scriptCallTokens; // 0x18, InitTokens: "*fx(", "*playif(", "*fxstop("
	std::map<int, std::list<void*> > m_partEffects[4]; // 0x28, by layer: part tid -> its effects
	std::list<int> m_layerPartTids[4];         // 0x68, by layer: the part tids StartFx bound (ctor 0x5b51c0)
	std::map<void*, RF_SHARED_PTR<sFxInfo> > m_fxInfos; // 0x98, effect -> what started it
	// 0xa8, 0xe8: by layer, a name -> the sFxInfo::m_param values started
	// under it (ctor 0x88c520, cleared by 0x88a1c0 in the destructor);
	// StopSprays stops the infos of m_paramFxInfos with each value. A is
	// keyed by the "*playif" condition (AddPlayIf; BindOwner starts / stops
	// its params), B by the "@" token (AddPlayIf, AddTokenFx).
	std::map<std::string, std::list<int> > m_namedParamsA[4]; // 0xa8
	std::map<std::string, std::list<int> > m_namedParamsB[4]; // 0xe8
	// 0x128: infos looked up by effect (sFxInfo::m_fx) or by m_param, the
	// fallback of StopLayerEffect's m_fxInfos lookup; the effects
	// AddPlayIf / AddTokenFx register (loaded later by StartParamFx).
	std::list<RF_SHARED_PTR<sFxInfo> > m_paramFxInfos;
	// 0x134 map (0x24 nodes), 0x144 list (0x10 nodes).
	PADDING(0x134, 0x150);
	CFxBox* m_fxBox;                           // 0x150, NULL = the CFx singleton
	int m_nextId;                              // 0x154, firstId + 1; AddEffect's ids
	int m_unknown158;                          // 0x158, 1 from the ctor; AddPlayIf's m_param ids
	// 0x15c (ctor 0x41a3b0), by layer: the "@" token whose registered
	// effects SwitchParamFx starts (an info without a token always starts).
	// Set elsewhere (not traced); empty in the port.
	std::string m_layerTokens[4];
	PADDING(0x1cc, 0x1d0);
	// 0x1d0: what PlaySequence last opened under each file name (a
	// CFxSequence* or a CFxSpray*; NULL once closed).
	std::map<std::string, void*> m_playedEffects;
	PADDING(0x1dc, 0x1e0);
};

CHECK_SIZE(JpFxInterpreter, 0x1e0);
BEGIN_LAYOUT_CHECK(JpFxInterpreter)
	CHECK_FIELD(JpFxInterpreter, m_scriptTokens, 0x8);
	CHECK_FIELD(JpFxInterpreter, m_scriptCallTokens, 0x18);
	CHECK_FIELD(JpFxInterpreter, m_partEffects, 0x28);
	CHECK_FIELD(JpFxInterpreter, m_layerPartTids, 0x68);
	CHECK_FIELD(JpFxInterpreter, m_fxInfos, 0x98);
	CHECK_FIELD(JpFxInterpreter, m_namedParamsA, 0xa8);
	CHECK_FIELD(JpFxInterpreter, m_namedParamsB, 0xe8);
	CHECK_FIELD(JpFxInterpreter, m_paramFxInfos, 0x128);
	CHECK_FIELD(JpFxInterpreter, m_fxBox, 0x150);
	CHECK_FIELD(JpFxInterpreter, m_nextId, 0x154);
	CHECK_FIELD(JpFxInterpreter, m_layerTokens, 0x15c);
	CHECK_FIELD(JpFxInterpreter, m_playedEffects, 0x1d0);
END_LAYOUT_CHECK
CHECK_SIZE(JpFxInterpreter::sFxInfo, 0x88);
CHECK_FIELD(JpFxInterpreter::sFxInfo, m_group, 0x28);
CHECK_FIELD(JpFxInterpreter::sFxInfo, m_token, 0x38);
CHECK_FIELD(JpFxInterpreter::sFxInfo, m_attacher, 0x54);
CHECK_FIELD(JpFxInterpreter::sFxInfo, m_param, 0x80);

#endif // PG_JP_JPFXINTERPRETER_H
