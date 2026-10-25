// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014B40-0x80014B94 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80013144(void);
void fn_8001B5B8(Unk_A07EDCEF *);
extern char lbl_80290A70[];
void *fn_80014B40(Unk_C7387A53 *arg0) {
    fn_80013144();
    arg0->unk0x3C = (s32)lbl_80290A70;
    fn_8001B5B8((s32)arg0 + (s32)0x8C);
    arg0->unk0x80 = 0;
    arg0->unk0x84 = 0;
    arg0->unk0x88 = 0;
    return arg0;
}
