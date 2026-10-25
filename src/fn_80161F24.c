// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161F24-0x80161FDC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005CC88(CStruct *, CStruct *);
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
s32 fn_8005CFC0(Unk_9994C3F5 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 GetText(CStruct *, void *, void *, void *);
extern Unk_9994C3F5 * lbl_80366474;

bool ScriptUnloadTexture(s32 arg0) {
    register void *z4 __asm__("r4");
    register void *z5 __asm__("r5");
    register void *z6 __asm__("r6");
    register s32 a0 __asm__("r30");
    s32 var_r31;
    s32 spC;
    s32 sp8;
    s32 var_r3;

    a0 = arg0;
    z4 = 0;
    z5 = &sp8;
    z6 = 0;
    __asm__ volatile("li %0,0" : "=r"(var_r31) : "r"(z4), "r"(z5), "r"(z6));
    if (GetText(a0, z4, z5, z6) != 0) {
        var_r3 = fn_8005CFC0(lbl_80366474, sp8);
        goto block_4;
    }
    if (GetChecksum_2(a0, 0, &spC, 0) != 0) {
        var_r3 = fn_8005CF80(lbl_80366474, spC);
block_4:
        var_r31 = var_r3;
    }
    if (var_r31 != 0) {
        fn_8005CC88(lbl_80366474, var_r31);
    } else {
        ContainsFlag(a0, QB_DONT_ASSERT);
    }
    return true;
}
