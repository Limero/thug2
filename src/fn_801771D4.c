// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801771D4-0x80177234 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80032088(s32);
s32 fn_8012ED98(void);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_801771D4(Unk_F8CDD391 *arg0, s32 arg1, Unk_C8FEE62D *arg2) {
    if ((s32) arg0->unk0x428 == 0) {
        fn_80032088(0xF8);
        arg0->unk0x428 = fn_8012ED98();
    }
    fn_8012F260(arg0->unk0x428, arg1, arg2, 0);
}
