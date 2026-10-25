// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FB114-0x800FB184 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
void fn_801029B8(Unk_A6515021 *, s32);
extern char lbl_8029C868[];
void fn_800FB114(CStruct *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029C868;
    if (((s32) arg0->unk0x8 != 0) && ((s32) (arg0->unk0x4 & QB_UNKNOWN_0xC0000000) == 0x80000000)) {
        fn_801029B8(arg0->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
