// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80216DC8-0x80216E24 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern s32 fn_802201B4(Unk_FFAD6788 *);
extern s32 fn_8021C9B8(CScript *);
extern void fn_8021CB74(CScript *, CScript *);
extern void fn_802201AC(Unk_FFAD6788 *, s32);
void fn_80216DC8(void) {
    s32 temp_r31 = lbl_80305F9C;
    if (fn_802201B4(temp_r31) == 1) {
        fn_8021CB74(temp_r31, fn_8021C9B8(temp_r31));
        fn_802201AC(temp_r31, 0);
    }
}
