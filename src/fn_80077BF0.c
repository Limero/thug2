// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077BF0-0x80077C48 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005BF2C(Unk_9994C3F5 *, s32);
void fn_8009B5F4(Unk_F5317C5D *, s32);
extern char lbl_80295990[];
void fn_80077BF0(CStruct *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x8 = (s32)lbl_80295990;
    v = arg0->unk0xC;
    if (v != 0) {
        fn_8009B5F4(v, 3);
    }
    fn_8005BF2C(arg0, arg1);
}
