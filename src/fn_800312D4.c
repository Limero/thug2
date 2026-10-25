// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800312D4-0x80031390 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80291A04;
f32 fn_800329A8(void *);
s32 fn_800C9780(void *);
void fn_800328BC(void *, s32);
void fn_800312D4(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 *arg3) {
    volatile double _dummy;
    s32 var_r4;
    void *var_r9;
    void *var_r31;
    f32 temp_f31;

    var_r4 = arg1;
    var_r9 = arg0->unk0x24;
    __asm__("" : "+r"(var_r9));
    goto loop_3;
body_3:
    var_r4 -= 1;
    if (var_r4 == -1) {
        goto out_3;
    }
    var_r9 = ((CStruct *)var_r9)->unk0xC;
loop_3:
    if ((s32) ((CStruct *)var_r9)->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        goto body_3;
    }
    __asm__("li %0,0" : "=r"(var_r9));
out_3:
    var_r31 = (var_r9 != NULL) ? var_r9 - 4 : NULL;
    temp_f31 = fn_800329A8(var_r31);
    if (temp_f31 <= lbl_80291A04) {
        *arg3 = lbl_80291A04;
    } else {
        fn_800C9780(arg0->unk0x80);
        fn_800328BC(var_r31, arg2);
        *arg3 = temp_f31;
    }
}
