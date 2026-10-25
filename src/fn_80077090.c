// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077090-0x800770F8 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80099AE4(s32, s32);
void fn_8007DEBC(Unk_FFAD6788 *);
s32 fn_8007DF14(Unk_9D99273B *);
bool fn_80077090(Unk_9D99273B *arg0, s32 arg1) {
    CStruct *temp_r3;

    fn_8007DEBC(arg0);
    if (arg1 == 0) {
        temp_r3 = fn_8007DF14(arg0);
        temp_r3->unk0x4 = (s32) (temp_r3->unk0x4 | 0x800);
    }
    fn_80099AE4(fn_8007DF14(arg0), arg1);
    arg0->unk0x288 = 0;
    return true;
}
