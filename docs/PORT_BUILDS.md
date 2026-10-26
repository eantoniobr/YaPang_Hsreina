# YaPang in the offline port builds

YaPang's `src/` is compiled twice: by cl 13.10 for the matching score
(projectg, `scripts/build.ts`), and by modern compilers for the playable
offline port (ProjectG-Offline, which has YaPang as a submodule). The
Windows build of the JP game in offline mode uses GCC 15 (CLion's MinGW,
x64, `-fpermissive`), configured in `cmake-build-sdlgpu-jp-release`; macOS
uses clang. A change that matches under cl 13.10 can still break those
builds. Check the points below before committing a unit.

## 1. Write source both compilers accept

The 2003 C++ library takes `int` where today's library wants its own types.
Use the standard type; cl 13.10 gives the same code.

| Construct | Write | Not | Example |
|---|---|---|---|
| Stream open mode | `std::ios::openmode mode = std::ios::app;` | `int mode = ...` (GCC's `fstream` has no `int` constructor) | `CGStarMode::SavePartsInfoCharacter` |
| A library algorithm the original calls | `#include <numeric>` and `std::accumulate(...)` | a hand-written loop, or a body-less `namespace std` declaration | `FrTradeBuyDlg::OnOkBnUp` |
| File streams | `#include <fstream>` | a guard macro around the code | `CGStarMode::SavePartsInfo*` |

For the JP code (`src/jp`, `src/client/Refresh`), which the Windows build
compiles with GCC on LLP64:

| Construct | Write | Not | Example |
|---|---|---|---|
| A key or value of KR `unsigned long` data (CSharedDoc's maps, type ids) | `DWORD`, with `<windows.h>` included by the header that uses it | `uint32_t` (another type than `unsigned long` on Windows) or `unsigned long` (64-bit in the macOS port, where `src/jp` is not mirrored) | `JpSharedDoc_GetLobbyUserMap` in `JpLobbyGlue.h`, ProjectG-Offline's `ProjectG/refresh/game/JpLobbyGlue.cpp` |
| `_alloca` outside MSVC | `<malloc.h>` under `__MINGW32__`, `<alloca.h>` elsewhere | `<alloca.h>` alone (MinGW has none) | `RFBrush.cpp`, `RFStringUtil.cpp` |

A change to a `src/jp` declaration that the glue in ProjectG-Offline's
`ProjectG/refresh/game` (and projectg's `port/refresh/game`) defines must be
made in both glue copies too. `npm run build:jp` there warns when the two
glue copies differ.

Fixes that make the port build go into YaPang as commits. An edit left
uncommitted in ProjectG-Offline's `YaPang/` checkout is lost at the next
checkout or pull of the submodule. The MinGW fixes above were lost once
that way, and the JP build broke.

## 2. Headers the 2003 kit lacks come from projectg's externs

The original kit in projectg's `externs/vs-2003/Vc7/include` had no
`<numeric>` and no `<fstream>`. Both are now there and written for this
project; the port builds use their own library's headers instead:

- `<numeric>`: written in the 2003 headers' layout. The `std::accumulate`
  instantiation in TradeDlg matches the original at 100%.
- `<fstream>`: the VS 2010 header brought back to the 2003 library. It has
  no C++0x members, no wide file names and no `_Lock`/`_Unlock` virtuals,
  with the `char`/`wchar_t` classes imported from msvcp71. msvcp71's
  `basic_filebuf` is 4 bytes larger than the VS 2010 member list
  (`basic_fstream` is 0x9C bytes, `_Myfile` at +0x64, from G_StarMode's
  frame), so a commented `_Pad` member stands for the unknown one. Do not
  read or write `_Pad`.

A unit that needs another missing standard header gets it the same way, in
projectg's `externs/`. It never gets a stand-in declaration in `src/`.

## 3. Units the port patches by text

ProjectG-Offline's `ProjectG/CMakeLists.txt` compiles a few units from a
copy with exact text replaced (`pg_patch_unit`). When the text to replace
is no longer in the YaPang source, the configure stops with
`pg_patched_copy(...): the text to replace is no longer in ...`. Editing
these spots in YaPang means updating the matching `pg_patch_unit` call in
ProjectG-Offline in the same change:

| Unit | Text the port replaces |
|---|---|
| `shared/luasystem/LuaScriptManager` | the body of `lua_script_manger::GetInstance()` |
| `client/Wangreal/source/wpuppet` | the `WPuppet::LoadPET_Mesh` signature line, the `FindFakeBodyBone` call, the `else { WBone* bone = root->FindBone(...)` normal branch, the `bones = new WBone*[...]` loop head, and the `LoadPET(fp, alphatest, ...)` call |
| `client/Wangreal/source/wxtnlbuffer` | `#include <string.h>` and the `dwFVF = m_xpVideo->xDetermineFVF(...)` line |
| `client/ProjectG/GolfRule` | the `CGolfRule::InitRadioPredictShotButton` signature and its `InitRadioPredictShotButton(&m_predict` calls |
| `client/ProjectG/Polysoup` | the `PlaceHoleCup()` block followed by `xUpdateTnLBuffers(true)` |
| `client/Fresh/source/FrCmdTarget` (browser build only) | the `FrFuncBI` / `FrFuncVI` cases of the message-map call |

A unit with a file in ProjectG-Offline's `ProjectG/overrides/<unit>.cpp` is
replaced as a whole there: a YaPang change to it never reaches the port
until the override is updated.

## 4. Flags that only the matching build uses

`shared/thirties/gaMath` is compiled with `/Oy /G6` (projectg
`scripts/lib/msvc.ts`, evidence in `docs/COMPILER.md`), not the game's
`/G7`. The port ignores cl flags; nothing to carry over.

## Checking a change in the Windows JP build

With CLion's `mingw/bin`, `cmake/win/x64/bin` and `ninja/win/x64` on
`PATH`, compile only the objects of the units you changed, from
ProjectG-Offline:

```bash
cd cmake-build-sdlgpu-jp-release
ninja ProjectG/CMakeFiles/ProjectG.dir/__/YaPang/src/client/ProjectG/G_StarMode.cpp.obj
```

A patched unit's object is under `__/patched/...` instead. The ninja run
also re-runs the configure when a source changed, which checks the
`pg_patch_unit` texts.

## Changes of 2026-10-26 the port depends on

These commits are in projectg's yapang and in ProjectG-Offline's YaPang
(branch `projectg-s31`). All 7 files compile in the Windows JP build:

| Unit | Change | Port impact |
|---|---|---|
| TradeDlg | `OnOkBnUp` sums through `std::accumulate`; `#include <numeric>` | none |
| G_StarMode | `SavePartsInfoCharacterMap` / `SavePartsInfoCharacter` written and compiled (no guard); `<fstream>`, `commonutil.h`, `ItemManager()` | now compiled by the port; the open mode must stay `std::ios::openmode` |
| GolfRule | `BallSpeedFactor` constructor: `BAR_START`, `GOLFDOC()` loaded once | patched unit: the `pg_patch_unit` texts are untouched |
| hatManager | `BABO_STR::WStrStr_JP` inner-loop compare with `goto same/next` | compiled with the JP headers there too |
| ChangeRoomInfoDlg | constructor switches on a local game type | none |
| fontinfo | `CExtraHoleInfo::UpdateLeader` reads its own distance first | none |
| wview | `MakeCameraMatrix` takes `UNIT_POS_X` through a const reference | none |
