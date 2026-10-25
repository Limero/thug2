// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80144C34-0x80144CB0 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012ED98(void);
s32 fn_80032088(s32);
void GetChecksum_3(Unk_6A70655D *, s32);
void fn_801F0E84(void);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_801309EC(Unk_DB0E2BAB *);
void fn_80144C34(Unk_C8FEE62D *arg0, s32 arg1, Unk_C8FEE62D *arg2) {
    if ((s32) arg0->unk0x14 == 0) {
        fn_80032088(0xF8);
        arg0->unk0x14 = fn_8012ED98();
    }
    GetChecksum_3(arg0, QB_SKATERFLIPANDROTATE);
    fn_801F0E84();
    fn_8012F260(arg0->unk0x14, arg1, arg2, arg0);
    fn_801309EC(arg0->unk0x14);
}
