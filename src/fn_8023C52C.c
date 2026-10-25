// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C52C-0x8023C598 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
void fn_802371CC(Unk_673C6403 *, Unk_4A174A22 *, s32);
void fn_8023C64C(Unk_31DE137E *);
void fn_8023C52C(CStruct *arg0, s32 arg1) {
    Unk_9994C3F5 *temp_r9;

    temp_r9 = arg0->unk0x48;
    if (temp_r9 != NULL) {
        temp_r9->unk0x8 = (s32) (temp_r9->unk0x8 & QB_UNKNOWN_0xFFFFFDFF);
        fn_802371CC(arg0->unk0x0, arg0->unk0x48, 0);
    }
    fn_8023C64C(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
