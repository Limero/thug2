// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070A7C-0x80070AE8 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802950B0[];
void *fn_80070A7C(Unk_DB0E2BAB *arg0, s32 arg1) {
    arg0->unk0x20 = (s32)lbl_802950B0;
    arg0->unk0x8 = QB_BLEND;
    arg0->unk0x1C = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x0 = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0xC = arg1;
    if (arg1 == 1) {
        fn_80070D20();
    }
    return arg0;
}
