// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012170-0x800121D8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

s32 fn_80012270(s32);
s32 fn_80011F94(void *, s32, s32, s32);
extern char lbl_80290830[];
extern s32 *lbl_802FFF08[];

// PoolManager_SSetupPool @ 0x80012170
void PoolManager_SSetupPool(s32 arg0, s32 arg1) {
    s32 *dst;
    s32 temp_r29;

    if (arg0 == 0) {
        dst = lbl_802FFF08[arg0];
        temp_r29 = (s32) Mem_Alloc2(0x5C);
        dst = fn_80011F94((void *) temp_r29, fn_80012270(0), arg1, (s32) lbl_80290830);
        lbl_802FFF08[arg0] = dst;
    }
}
