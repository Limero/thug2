// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B301C-0x801B30A4 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012ED98(void);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
s32 fn_8012F044(CStruct *);
s32 fn_801B30A4(Unk_C7387A53 *);
s32 fn_80032088(s32);
s32 fn_801309EC(Unk_DB0E2BAB *);
void fn_801B301C(Unk_C7387A53 *arg0, s32 arg1, Unk_C8FEE62D *arg2) {
    if (arg1 != 0) {
        if ((s32) arg0->unk0x34 == 0) {
            fn_80032088(0xF8);
            arg0->unk0x34 = fn_8012ED98();
        }
        fn_8012F260(arg0->unk0x34, arg1, arg2, arg0->unk0xC);
        if (fn_8012F044(arg0->unk0x34) != 0) {
            fn_801309EC(arg0->unk0x34);
            return;
        }
        fn_801B30A4(arg0);
    }
}
