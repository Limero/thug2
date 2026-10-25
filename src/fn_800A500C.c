// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A500C-0x800A50C0 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800A4C28(Unk_451C91CE *, void *, s32, s32, s32, s32, s32);
void fn_800A514C(Unk_C7387A53 *, CScript *);
void fn_800A6910(CStruct *, s32 *);
void fn_800A500C(Unk_9994C3F5 *arg0, CScript *arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    s32 v0;
    s32 *var_r11;
    s32 var_ctr;
    void *var_r3;

    v0 = arg0->unk0x8;
    sp8 = arg1->unk0x18;
    fn_800A6910(v0, &sp8);
    if (arg3 != 0) {
        var_ctr = 0x28;
        var_r3 = (char *)arg0 + 0x20;
        var_r11 = (char *)arg0 + 0xB040;
        do {
            s32 target = arg1->unk0x18;
            if ((s32) *((s32 *)var_r11) == target) {
                *((s32 *)var_r11) = arg2;
            }
            var_r11 = (s32 *)((char *)var_r11 + 0xC);
            var_ctr -= 1;
        } while (var_ctr != 0);
    } else {
        fn_800A514C(arg0, arg1);
        var_r3 = (char *)arg0 + 0x20;
    }
    fn_800A4C28(var_r3, 0, arg1->unk0x18, QB_SYSTEM, 0, 0, 5);
}
