// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033904-0x80033AF4 (496B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_8006FB50(s32, s32);
s32 fn_8006FB8C(s32, s32);
s32 fn_8002D2A0(void);
s32 fn_8002D718(s32);
void fn_8002AFB0(void *, s32);
void fn_8002DEAC(s32, s32, f32, f32, f32, f32, s32);
s32 fn_80026C44(s32, s32);
s32 fn_8005527C(s32);
s32 fn_8005525C(void);
s32 fn_80026BF8(s32);
s32 fn_80033904(Unk_DB0E2BAB *arg0, s32 arg1, CStruct *arg2) {
    u32 swv1;
    s32 sp20;
    f32 sp1C;
    f32 sp18;
    s32 sp14;
    f32 sp10;
    f32 spC;
    s32 sp8;
    void *temp_r30;
    register s32 t8 __asm__("r4");
    s32 t24;
    register CStruct *a2 __asm__("r31");

    a2 = arg2;
    switch (swv1 = arg1) {
    case QB_INVALIDATECACHE:
        arg0->unk0x1C = fn_8006FB50(arg0->unk0x20, 0);
    default:
        return 2;
    case QB_PRECACHE:
        temp_r30 = (void *)arg0->unk0x1C;
        fn_8002AFB0(temp_r30, fn_8002D718(fn_8002D2A0()));
        return 1;
    case QB_PLAYSEQUENCE:
        GetChecksum_2(a2, QB_ANIMNAME, &sp8, 1);
        GetFloat(a2, QB_STARTTIME, &spC, 1);
        GetFloat(a2, QB_ENDTIME, &sp10, 1);
        GetInteger(a2, QB_LOOPTYPE, &sp14, 1);
        GetFloat(a2, QB_BLENDPERIOD, &sp18, 1);
        { s32 a6; s32 a4; register s32 hi __asm__("r4");
        hi = QB_SPEED & ~0xFFFF;
        /* order wedge (non-volatile, operands from C): W6 wants li r6 BEFORE
         * ori r4 (W1-W5 want the reverse); plain C sinks the ori first. */
        __asm__("li %0,1\n\tori %1,%3,%4"
                : "=r"(a6), "=r"(a4) : "r"(a2), "r"(hi),
                  "i"(QB_SPEED & 0xFFFF));
        GetFloat(a2, a4, &sp1C, a6); }
        fn_8002DEAC(arg0->unk0x4 + 4, sp8, spC, sp10, sp18, sp1C, sp14);
        t24 = arg0->unk0x24;
        t8 = sp8;
        break;
    case QB_REPLACEANIM:
        GetChecksum_2(a2, QB_ANIM, &sp20, 1);
        if (arg0->unk0x1C != 0) {
            fn_80026C44(arg0->unk0x1C, arg0->unk0x28);
        }
        if (arg0->unk0x20 != 0) {
            fn_8005527C(arg0->unk0x20);
            arg0->unk0x20 = 0;
        }
        arg0->unk0x20 = fn_8005525C();
        fn_8006FB50(arg0->unk0x20, 0);
        t24 = arg0->unk0x24;
        t8 = sp20;
        break;
    }
    arg0->unk0x1C = fn_8006FB8C(arg0->unk0x20, t24 + t8);
    arg0->unk0x28 = fn_80026BF8(arg0->unk0x1C);
    return 1;
}
// family=m2c range=0x80033904-0x80033AF4 size=496B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
