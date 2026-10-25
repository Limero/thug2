// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F567C-0x800F56CC (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800133B4(Unk_DB0E2BAB *);
void fn_80013788(void *);
void fn_800F37CC(Unk_C7387A53 *);
void fn_800F567C(Unk_C7387A53 *arg0) {
    if ((s32) arg0->unk0x5C != 0) {
        fn_800133B4(arg0->unk0x5C);
        fn_80013788(arg0->unk0x5C);
        arg0->unk0x5C = 0;
    }
    fn_800F37CC(arg0);
}
