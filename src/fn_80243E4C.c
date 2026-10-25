// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243E4C-0x80243EF0 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802B0544;
extern f32 lbl_802B12D8;
f32 fn_802434B0(s32, s32);
void fn_802413C0(Unk_C7387A53 *, f32);

void fn_80243E4C(s32 arg0, Unk_C7387A53 *arg1) {
    f32 var_f0 = lbl_802B12D8;
    s32 entry;
    s32 i;

    __asm__("" : "+f"(var_f0));
    i = 0;
    goto cond;
second:
    if (((CStruct *)entry)->unk0x10 != arg1) {
        goto inc;
    }
    var_f0 = fn_802434B0(entry + 0x9C, 1);
    goto shared;
inc:
    i++;
cond:
    if (i > 0x1F) {
        goto shared;
    }
    {
        s32 idx = i * 4;
        char *p = (char *)arg0 + 4;
        entry = *(s32 *)(p + idx);
        if (entry == 0) {
            goto inc;
        }
        if (((CStruct *)entry)->unk0xC != arg1) {
            goto second;
        }
    }
    var_f0 = fn_802434B0(entry + 0x9C, 0);
shared:
    fn_802413C0(arg1, var_f0 / lbl_802B0544);
}
