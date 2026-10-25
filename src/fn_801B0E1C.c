// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0E1C-0x801B0E6C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
void fn_801B0144(s32, s32);
extern char lbl_802ABDA4[];
void *fn_801B0E1C(CStruct *arg0) {
    s32 v;

    arg0->unk0x4 = 0;
    v = Mem_NewZero(5);
    arg0->unk0x8 = v;
    fn_801B0144(v, (s32)lbl_802ABDA4);
    return arg0;
}
