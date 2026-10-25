// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2234-0x800A229C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009FB7C(Unk_6A70655D *, CStruct *, CStruct *);
s32 fn_800A2954(s32);
void fn_800A2234(Unk_9994C3F5 *arg0, CStruct *arg1, CStruct *arg2) {
    if (fn_800A2954(0) != 0) {
        fn_8009FB7C(arg0, arg1, arg2);
        arg0->unk0x118 = (s32) (arg0->unk0x118 + fn_800A29DC());
        return;
    }
    fn_800A28A4();
}
