// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C9808-0x800C9970 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029931C;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80037C40(s32, s32, void *, s32);
s32 fn_8003A390(CStruct *, s32);
s32 fn_8003A31C(CStruct *);
s32 fn_8003A3D4(s32, s32, s32);
s32 fn_8003A324(s32, s32);
s32 fn_80037CF4(Unk_DB0E2BAB *);
bool fn_800C9808(Unk_31DE137E *arg0, CStruct *arg1) {
    f32 sp8[4] __attribute__((aligned(16)));
    s32 sp18;
    f32 sp1C;
    s32 temp_r28;
    u32 var_r29;
    void *temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    f32 temp_f0;
    f32 temp_f13;
    register f32 *p __asm__("r5");

    GetChecksum_2(arg1, QB_BONE, &sp18, 1);
    GetFloat(arg1, QB_SCALE, &sp1C, 1);
    temp_r31 = ContainsFlag(arg1, QB_PROPAGATE);
    temp_r3 = ContainsFlag(arg1, QB_PROPAGATE_REVERSE);
    temp_f0 = sp1C;
    temp_f13 = lbl_8029931C;
    sp8[0] = temp_f0;
    __asm__("" : "+r"(p));
    p = sp8;
    p[1] = temp_f0;
    p[2] = temp_f0;
    p[3] = temp_f13;
    if (temp_r3 == 0) {
        fn_80037C40(arg0->unk0x1C, sp18, p, temp_r31 ^ 1);
    } else {
        var_r29 = 1U;
        temp_r31 = *(s32 *)(arg0->unk0x1C + 8);
        temp_r28 = fn_8003A390(temp_r31, sp18);
        for (; var_r29 < fn_8003A31C(temp_r31); var_r29++) {
            if ((fn_8003A3D4(temp_r31, var_r29, temp_r28) == 0) && ((s32)var_r29 != temp_r28)) {
                temp_r30 = arg0->unk0x1C;
                fn_80037C40(temp_r30, fn_8003A324(temp_r31, var_r29), sp8, 1);
            }
        }
        *(s32 *)(arg0->unk0x1C) |= QB_UNKNOWN_0x08000000;
        if (ContainsFlag(arg1, QB_FORCE_UPDATE) != 0) {
            fn_80037CF4(arg0->unk0x1C);
        }
    }
    return true;
}
