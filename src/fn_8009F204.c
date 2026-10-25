// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F204-0x8009F27C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_8012F044(CStruct *);
void fn_80032088(s32);
s32 fn_8012ED98(void);
s32 fn_8009F204(Unk_C8FEE62D *arg0, void *arg1, Unk_C8FEE62D *arg2) {
    if ((s32) arg0->unk0x14 != 0) {
        fn_8012F260(arg0->unk0x14, arg1, arg2, arg0);
    } else {
        fn_80032088(0xF8);
        arg0->unk0x14 = fn_8012ED98();
        fn_8012F260(arg0->unk0x14, arg1, arg2, arg0);
    }
    fn_8012F044(arg0->unk0x14);
    return arg0->unk0x14;
}
