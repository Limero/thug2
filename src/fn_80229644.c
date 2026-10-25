// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229644-0x802296A0 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern s32 fn_8022986C(CScript * arg0);
extern s32 fn_8021C9B0(CScript * arg0);
extern void fn_8021CB74(CScript * arg0, CScript * arg1);
void fn_80229644(CScript *arg0, s32 arg1) {
    s32 mgr;
    s32 temp_r3;

    mgr = lbl_80305F9C;
    arg0->unk0x18 = arg1;
    if ((fn_8022986C(arg0) == 0) && ((temp_r3 = fn_8021C9B0((void *)mgr)) == (s32)arg0)) {
        fn_8021CB74((void *)mgr, (void *)temp_r3);
    }
}
