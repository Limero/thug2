// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DAEAC-0x800DAEFC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80301B30;
extern char lbl_8039F9B0[];
void fn_80125D54(s32, s32, s32);
void *Mem_NewZero(s32);
void *fn_800DB728(void *);
void fn_800DAEAC(void) {
    fn_80125D54(QB_SUSPEND, (s32)lbl_8039F9B0, 0x10);
    lbl_80301B30 = (s32)fn_800DB728(Mem_NewZero(8));
}
