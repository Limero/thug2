# GX library wiring survey (as of M9.23, post-GXMisc)

THUG2's GX is a **Feb 7 2003** build (SDK lib version 0x2301, same as tww's
Sep 5 2002 — the version string is constant, the build date drifts). Docs
`dolphin-sdk.md` §8/§9 has the authoritative background. This file records the
current wiring state and the per-file findings from the survey so the next
session does not re-derive them.

## DOL layout (text)

| Object | Text range | Status |
|---|---|---|
| GXInit.o | `0x80284E20..0x802861A4` | **PARKED** (2026-08-19) — Feb-2003-only revision, no decomp has it; hand reconstruction failed, see parkings/21-gxinit.md |
| GXFifo.o | `0x802861A4..0x802869B4` | unwired — include fix only |
| GXAttr.o | `0x802869B4..0x802882CC` | ✅ wired (tww, M8.140) |
| GXMisc.o | `0x802882CC..0x80288A28` | ✅ wired (M9.23) — GXSetMisc + the GXDraw fns (see below) |
| GXDraw.o | `0x80288360..0x802889A8` | ✅ wired — GXDraw's fns (GXFlush, GXDrawDone, GXPixModeSync, GXPoke*, GXPeekZ, callbacks, __GXPEInit) are compiled from `gx/GXMisc.c` (split `0x802882CC..0x80288A28`); GXClearBoundingBox 0x38 is GXLight's tail |
| GXLight.o | `0x802898BC..0x80289AE4` | ✅ wired (M9.xx) — 4 fns byte-exact; 5 GXSetChan* fns (`0x80289AE4..0x80289E40`) parked auto-asm (see below + parkings/18-gxlight-chan-regalloc.md) |
| GXTexture.o | `0x80289E40..0x8028AEAC` | unwired — mostly matches, drift in __SetSURegs (below) |
| GXBump.o | `0x8028AEAC..0x8028B224` | unwired — drifted (below) |
| GXTev.o | `0x8028B224..0x8028BA08` | 13/16 — 3 Color-family PERMANENTLY PARKED 2026-08-19 (see parkings/19-gxtev-color-sched.md) |
| GXPixel.o | `0x8028BA08..0x8028C040` (GXSetBlendMode 0x8028BD24…) | unwired — tww sizes differ |
| GXDisplayList.o | `0x8028C040..0x8028C0B0` | ✅ wired |
| GXTransform.o | `0x8028C0B0..0x8028C860` | ✅ wired (M9.xx) |
| GXPerf.o | `0x8028C860..0x8028D324` | ✅ wired (M8.139) |
| GXStubs.o | `0x8028D324..0x8028D328` | ✅ wired |
| GXGeometry.o / GXVert.o / GXFrameBuf.o / GXSave.o / GXVerif* | `0x8028D328+` | unwired — mostly uninvestigated |
| **CORRECTED (2026-08-26):** `0x8028D328..0x8028E038` is NOT GX — it is the Dolphin SDK **OdemuExi2/DebuggerDriver** module (mwcc; port verbatim from `tww/src/OdemuExi2/DebuggerDriver.c`; thug2's revision inlines DBGEXISync into DBGEXIImm) plus zone-edge ProDG-newlib stragglers (fn_8028E008). The `Vtable0x803089D0_mN` names are dtk mislabels from the driver's 21-slot dispatch table. See AGENTS.md §6as | | |

## GXMisc.o (wired M9.23)

Retail GXMisc.o is a **single function** (GXSetMisc, 0x94 at 0x802882CC). The
other functions that tp's GXMisc.c carries (GXFlush, GXDrawDone, GXPixModeSync,
GXPoke*, GXPeekZ, callbacks, GXClearBoundingBox) live in retail's **GXDraw.o**
region (0x80288360..0x80289884) and were moved into GXDraw.c for the future
GXDraw wiring. GXSetMisc uses the tww `gx` symbol (SDA21, resolves at link);
the 3 GX_MT tokens match retail exactly (GX_MT_ABORT_WAIT_COPYOUT was added to
GXEnum.h — our header lacked it). Wiring recipe (the split step is REQUIRED or
the object silently never gets emitted):
1. trim GXMisc.c to just GXSetMisc (tww-style `#include <dolphin/gx.h>` + `gx`)
2. add `gx/GXMisc.c:` split entry in splits.txt (`.text 0x802882CC..0x80288360`)
3. `python3 configure.py …` → `rm build/G2TE52/config.json` →
   `tools/ninja build/G2TE52/config.json` (dtk re-split) → configure.py again
   (build.ninja reads config.json — a plain reconfigure without the re-split
   drops the new object)
4. build DOL; verify byte-identical

## GXLight.o (4 fns WIRED M9.xx; 5 GXSetChan* fns parked)

Retail GXLight.o = 0x802898BC..0x80289E40 (9 functions): GXInitLightSpot 0x190,
GXInitLightPos 0x10, GXInitLightColor 0xC, GXLoadLightObjImm 0x7C (all four
**wired byte-exact** from the in-tree GXLight.c in M9.xx), then 5 GXSetChan*
fns at `0x80289AE4..0x80289E40` (0xF4, 0xF4, 0x44, 0xCC, 0x64) still parked
as auto-asm. GXClearBoundingBox 0x38 at 0x80289884 is the tail of GXDraw.o
(i.e. of GXMisc.c's split). The 5 chan fns were renamed to GXSetChanAmbColor/
GXSetChanMatColor/GXSetChanCtrl/GXSetNumChans etc. but remain unmatched:
GXSetChanAmbColor/GXSetChanMatColor are 0xE8 in tww vs retail fn_ 0xF4/0xF4
(regalloc coin-flip — see parkings/18-gxlight-chan-regalloc.md); GXSetChanCtrl
0xCC and GXSetNumChans 0x44 are covered by gx/GXChan.c (wired M9.xx);
fn_80289DDC 0x64 has no tww counterpart. Wired GXLight.c needs the .sdata2
split extended to 0x2C (11 floats incl. -2.0f) and force_active for
GXInitLightSpot (no linker-visible callers).

## GXTexture.o (next best target)

Compiling **tww's** `GXTexture.c` (Sep-2002) gives, per retail `0x80289E40..0x8028AEAC`:

- **Match (register-normalized, reloc-aware):** GXGetTexBufferSize (2 false
  diffs = lis/addi reloc), GXInitTexObj, GXInitTexObjCI, GXInitTexObjLOD,
  GXGetTexObjFmt, GXLoadTexObjPreLoaded, GXLoadTexObj, GXInitTlutRegion,
  GXInvalidateTexAll, GXSetTexRegionCallback, GXSetTlutRegionCallback,
  GXInitTexCacheRegion, __GXSetSUTexRegs (7 false diffs = SDA21 lwz forms),
  __GXSetTmemConfig.
- **Dead-stripped in THUG2 (remove from tww source):** GXGetTexObjWidth,
  GXGetTexObjHeight, GXGetTexObjWrapS, GXGetTexObjWrapT, GXGetTexObjTlut.
  THUG2's order is `…LOD, GXGetTexObjFmt, GXLoadTexObjPreLoaded…` (Fmt before
  PreLoaded, no getters).
- **DRIFT (Feb-2003, needs hand-writing from retail):**
  - `GXSetTexCoordScaleManually` + `__SetSURegs` = retail `0x8028A9AC..0x8028AAF0`
    (0x144). **RESOLVED (M9.24): these are the bfbb/EA lineage, not mystery**
    drift. bfbb's GXTexture.c has real bodies that match retail's byte pattern
    exactly (verified by disassembly): GXSetTexCoordScaleManually sets
    tcsManEnab@0x4DC bitfield, then suTs0@0xB8/suTs1@0xD8 low-16 scale fields
    + stb 0x61/`stw` FIFO writes + bpSentNot@0x2=0; __SetSURegs reads
    tImage0@0x45C bits 0-9/10-19 + tMode0@0x47C bits 0-1/2-3 into
    suTs0/suTs1 bits 0-15/16. tww's versions use MSB-side bit positions
    (`GX_GET_REG(...,22,31)`) so they DON'T match — port bfbb's two functions
    (rewrite `__GXData->`→`gx->`; the `gx` struct layout in GXInit.h already
    has tcsManEnab@0x4DC/suTs0@0xB8/suTs1@0xD8/bpSentNot@0x2 verified).
    bfbb's whole file won't compile against our headers (uses GX_TF_A8 etc.
    enum values we lack), so port just these two functions into tww's file.
  - `GXInitTlutObj` retail is 0x48 (tww compiles 0x4C — 4-byte diff, check the
    tail-call/store form).
- **Sections:** tww object .text 0xFE0 (minus getters 0x30 ≈ retail 0x106C
  minus 0x88 drift), .data 0x224 (pure switch jump tables), **.sdata 0x3E**
  (the GXTexMode0Ids/…/GX2HWFiltConv ID tables live in .sdata, NOT .data!),
  .sdata2 0x28 (float consts: 16.0f, 2^52, -4.0f, 4.0f, 3.99f, 32.0f, 10.0f).
- **Retail data anchors:** ID tables at `0x803002A0` (62 bytes; a second
  identical copy sits at `0x80311270` — not yet explained, check which one the
  code references), jump tables at `0x803106A0+` (GXGetTexBufferSize switch,
  __GetImageTileCount switch at 0x803107A0, GXInitTexObj switch at 0x80310894),
  GXTev tevopTable at `0x803108D0` (so GXTexture data must end before that).
  .sdata/.sdata2 addresses for GXTexture are NOT yet mapped (check GXAttr's
  .sdata `0x803CAA00` region; .sdata2 floats live near GXTransform's
  `0x803CC1D0`).

### RESOLVED (source, M9.24): all 20 GXTexture functions now byte-match

tww's GXTexture.c was used as the base and hand-ported to Feb-2003. Verified
function-by-function against retail `0x80289E40..0x8028AEAC` (all 20 match
modulo SDA21/branch relocations which resolve at link). The concrete fixes:

1. **GXInitTexObjFilter** (`fn_8028A4B4`, NEW — tww lacks it):
   ```c
   SET_REG_FIELD(internal->texture_filter, 1, 4, mag_filt == GX_LINEAR ? 1 : 0);
   SET_REG_FIELD(internal->texture_filter, 3, 5, GX2HWFiltConv[min_filt]);
   ```
   Must use `SET_REG_FIELD` (single RMW), NOT `&=`+`|=` (which emitted 4 stores).
2. **GXSetTexCoordScaleManually** + **__SetSURegs**: ported from bfbb/EA lineage
   (rewrite `__GXData->`→`gx->`); use `GX_BP_LOAD_REG` (== GX_WRITE_RAS_REG, both
   `stb 0x61; stw`) for the FIFO writes. tww's MSB-side `GX_GET_REG(...,22,31)`
   bit positions DON'T match — bfbb's LSB-side `GET_REG_FIELD`/`SET_REG_FIELD` do.
3. **GXInitTlutObj** + **GXInitTexObj**: `(u32)x >> 5` → `((u32)x & 0x3FFFFFFF) >> 5`
   (retail emits `rlwinm r0,rN,27,7,31`, not `srwi`).
4. **GXLoadTlut**: `reg = ret->unk0 & 0x3FF;` (explicit mask) before
   `SET_REG_FIELD(internal->format, 10, 0, reg)` — the mask forces retail's
   `clrlwi`+`rlwimi` instead of tww's `clrrwi`+`or`.
5. **GXTlutObj.numEntries u32→u16** (GXStruct.h): retail stores via `sth`; the
   struct stays 12 bytes (padded), so GXLoadTlut's 3-word copy is unaffected.
   Layout-neutral — DOL stays byte-identical (verified).

### BLOCKER (data, TODO): section placement differs from tww's object

- tww's object emits the ID tables (GXTexMode0Ids/…/GX2HWFiltConv, 62 bytes) in
  **.sdata**, but retail has them in **.data** at `0x803002A0`
  (`lbl_803002A0/.data`, confirmed by byte search + symbols.txt). Need a
  `#pragma section ".data"` (or equivalent) around those 8 `u8[]` declarations
  so the linker places them in .data, not .sdata.
- .data jump tables = `0x803106A0..0x803108D0` (before GXTev tevopTable).
- .sdata2 float consts (16.0f/2^52/-4.0f/4.0f/3.99f/32.0f/10.0f, 0x28) still
  need their retail anchor (3.99f found at `0x80312460`; r13 offsets in
  GXInitTexObjLOD are -0x6160/-0x6168/…, reconcile with _SDA_BASE_).

## GXBump.o (drifted)

`0x8028AEAC..0x8028B224`: GXSetTevIndirect (0x218 — tww's is only 0x9C, so
the Feb-2003 build has a much bigger version), fn_8028B0C4 (0x28 =
GXSetNumIndStages-ish, sets genMode 0x204 + ori 6 at 0x4F4), fn_8028B0EC
(0x48 = GXSetTevDirect, wraps GXSetTevIndirect with zero args),
fn_8028B134 (0xCC, switch over genMode 0x204 = GXSetIndTexMtx?), and
`__GXFlushTextureState` at `0x8028B200` (0x24, matches tww). bfbb's GXBump.c
uses EA macros (`GX_LOAD_BP_REG`) that our headers lack; needs either the EA
headers or hand-writing.

## Quick include fixes needed (GXInit / GXFifo / GXMisc / GXLight)

tww sources use split headers; our tree has monolithic ones. When copying:

- `#include "dolphin/os/OS.h"` → `#include "dolphin/os.h"`
- `#include "dolphin/vi/vi.h"` → `#include "dolphin/vi.h"` (exists)
- `#include "dolphin/base/PPCArch.h"` → exists at `dolphin/base/PPCArch.h` ✓
- GXLight: `#include "math.h"` — our tree has NO math.h anywhere (MSL dirs
  only carry fdlibm.h). GXLight uses sin/cos (GXInitLightSpot). Check how the
  game compiles math (look for a project-local math header or mwcc builtin)
  before wiring GXLight.
- GXMisc hit a type error on `__OSLastInterruptTime` in OSInterrupt.h when
  compiled from tww's include style — recheck once includes are fixed.

## Methodology (for reuse)

Per-file survey: copy tww source → compile with the project's exact GX cflags
(`/tmp/gxcc.sh` = build.ninja flags for GXTransform) → disassemble object →
register-normalized per-function compare vs retail bytes from `tools/gen_leaves`
(SDA21 `lwz rX,0(0)` = `lwz rX,-0x6218(r13)` and branch targets are false
diffs; normalize `r\d+`→`R`, branch → mnemonic only).
