// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6D60-0x800B6E00 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
void fn_800B6D60(CScript *arg0, CStruct *arg1) {
    s32 var_r0;

    if (ContainsFlag(arg1, QB_NODYNAMICUPDATE) != 0) {
        arg0->unk0x1C |= 1;
    } else {
        arg0->unk0x1C &= ~1;
    }
    arg0->unk0x20 = 0U;
    arg0->unk0x24 = 0;
    if (GetInteger(arg1, QB_INTERLACE_UPDATE_FRAMES, (char *)arg0 + 0x20, 0) != 0) {
        arg0->unk0x24 = (s32)(((u32)arg0 % (u32)arg0->unk0x20) + 1);
    }
}
