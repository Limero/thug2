// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003ABD8-0x8003AE20 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8003AB44(s32 arg0, s32 arg1);
void CModelAppearance_set_part(void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(void *, void *);
s32 fn_8003A5B8(s32, s32);
void fn_8003A730(s32, s32, s32);
void fn_80126FF4(s32, s32);
s32 fn_8003ABA0(s32, s32);
s32 fn_8009EE2C(Unk_FFAD6788 *, s32, s32, CStruct *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8003ABD8(Unk_9994C3F5 *arg0, s32 arg1, CStruct *arg2, CScript *arg3) {
    u32 swv1;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 var_r3;

    switch (swv1 = arg1) {                                 
    case 0xA23400C:
        GetChecksum_2(arg2, QB_PART, &sp8, 1);
        fn_8003A5B8(arg0, sp8);
        return 1;
    case QB_SETPART:
        GetChecksum_2(arg2, QB_PART, &spC, 1);
        GetChecksum_2(arg2, QB_DESC_ID, &sp10, 1);
        CModelAppearance_set_part(arg0, spC, sp10, arg2);
        return 1;
    case QB_GETPART:
        GetChecksum_2(arg2, QB_PART, &sp14, 1);
        arg1 = fn_8003ABA0(arg0, sp14);
        if (arg1 != 0) {
            fn_80126FF4(arg3->unk0x18, arg1);
            return 1;
        }
block_20:
        return 0;
    case QB_SETCHECKSUM:
        GetChecksum_2(arg2, QB_FIELD, &sp18, 1);
        GetChecksum_2(arg2, QB_VALUE, &sp1C, 1);
        fn_8003A730(arg0, sp18, sp1C);
        return 1;
    case QB_GOTPART:
        GetChecksum_2(arg2, QB_PART, &sp20, 1);
        return fn_8003AB44(arg0, sp20) != 0;
    case QB_PARTGOTFLAG:
        GetChecksum_2(arg2, QB_PART, &sp24, 1);
        GetChecksum_2(arg2, QB_FLAG, &sp28, 1);
        temp_r3 = fn_8003AB44(arg0, sp24);
        if (temp_r3 != 0) {
            return ContainsFlag(temp_r3, sp28);
        }
        return 0;
    default:
        var_r3 = fn_8009EE2C(arg0, arg1, arg2, arg3);
        
        return var_r3;
    }
}
