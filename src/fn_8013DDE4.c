// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013DDE4-0x8013DE78 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F480[];
extern s32 fn_8013E034(void *, CStruct *);
extern void fn_8013DA08(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8013DDE4(s32 arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7) {
    struct fr_s {
        volatile s32 sp8;
        char pad[12];
        s32 f4;
        s32 f8;
    } fr;
    char *mp = (char *)&fr + 8;
    s32 var_r4;

    ((Unk_4C649A8C *)mp)->unk0x4 = 0;
    ((Unk_4C649A8C *)mp)->unk0x8 = (s32)lbl_8029F480;
    var_r4 = fn_8013E034((void *)arg0, mp);
    if (var_r4 != 0) {
        fr.sp8 = arg7;
        fn_8013DA08(arg0, var_r4, arg1, arg2, arg3, arg4, arg5, arg6);
    }
    ((Unk_4C649A8C *)mp)->unk0x8 = (s32)lbl_8029F480;
}
