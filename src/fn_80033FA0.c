// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033FA0-0x80034010 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80291D20[];
extern void fn_8005527C(s32);
extern void fn_80033560(Unk_C8FEE62D *, s32);
void fn_80033FA0(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80291D20;
    if ((s32) arg0->unk0x30 != 0) {
        fn_8005527C(arg0->unk0x30);
        arg0->unk0x30 = 0;
    }
    if ((s32) arg0->unk0x34 != 0) {
        arg0->unk0x34 = 0;
    }
    fn_80033560(arg0, arg1);
}
