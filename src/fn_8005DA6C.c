// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DA6C-0x8005DAD8 (108B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_8036645C[];
extern s32 lbl_80366474;
extern s32 lbl_80366478;
extern char lbl_8029392C[];
extern char lbl_80293934[];
s32 fn_8005D4F4(s32);
void fn_8005D9F0(Unk_DB0E2BAB *, s32);
void fn_8005DA6C(u16 arg0, u16 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        fn_8005D9F0((s32)lbl_8036645C, 4);
        lbl_80366474 = fn_8005D4F4(lbl_8029392C);
        lbl_80366478 = fn_8005D4F4(lbl_80293934);
    }
}
