// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80150164-0x801503F4 (656B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_802A7C90[];
extern s32 lbl_80301A38;
s32 fn_800F0F84(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800A3778(s32, s32, void *);
s32 fn_801AC3E8(s32, s32, s32, s32);
s32 fn_80128A90(CStruct *, void *);
s32 fn_800B1168(s32, s32);
s32 fn_800B07B4(s32, s32);
s32 fn_8005B11C(s32);
void *fn_80054EE8(void);
void fn_80150134(CScript *, s32 *);
s32 fn_80055E74(Unk_FFAD6788 *, s32);
s32 fn_80057D90(Unk_C8FEE62D *, s32);
s32 fn_80055114(s32, s32);
s32 ContainsFlag(CStruct *, s32);

bool fn_80150164(s32 arg0, Unk_FFAD6788 *arg1) {
    s32 sp18;
    struct { s32 a; s32 b; } sp10;
    s32 sp8;
    s32 temp_r0;
    s32 var_found;
    s32 temp_r28;
    s32 temp_r30;
    s32 var_r31;
    register s32 temp_r9 __asm__("r9");
    CStruct *var_r3;

    temp_r28 = *(s32 *)((char *)*(s32 *)&lbl_80305EAC + (s32)0x28);
    temp_r30 = fn_800F0F84(arg0, 1);
    if (temp_r30 == 0) {
        return false;
    }
    sp8 = 0;
    GetChecksum_2(temp_r30, QB_CLASS, &sp8, 0);
    switch ((u32)sp8) {
    case QB_PEDESTRIAN:
    case QB_PED:
    case QB_SKATER:
    case QB_PARTICLEOBJECT:
    case QB_VEHICLE:
    case QB_LEVELOBJECT:
    case QB_GAMEOBJECT:
        sp10.b = arg1->unk0xBC;
        sp10.a = arg0;
        fn_800A3778(lbl_80301A38, (s32)fn_80150134, &sp10);
        break;
    case QB_LEVELLIGHT:
        fn_8005B11C(arg0);
        break;
    case QB_CLIMBINGNODE:
    case QB_RAILNODE:
        fn_801AC3E8(temp_r28, arg0, 0, fn_80128A90(temp_r30, (s32)lbl_802A7C90));
        break;
    case QB_PROXIMNODE:
        fn_800B1168(arg0, 0);
        break;
    case QB_EMITTEROBJECT:
        fn_800B07B4(arg0, 0);
        break;
    case QB_LEVELGEOMETRY:
        sp18 = 0;
        if (GetChecksum_2(temp_r30, QB_NAME, &sp18, 0) != 0) {
            var_r3 = fn_80054EE8();
            if (var_r3 != NULL) {
                do {
                    temp_r9 = *((void * *)&var_r3->unk0xC);
                    temp_r0 = ((CStruct *)temp_r9)->unk0x4;
                    var_r31 = (s32)temp_r9;
                    __asm__("" : "+r"(temp_r9));
                    if (temp_r0 == -1) {
                        var_r31 = 0;
                    }
                    var_found = fn_80055E74(var_r3->unk0x4, sp18);
                    if (var_found == 0) {
                        var_r3 = (void *)var_r31;
                        continue;
                    }
                    fn_80057D90(var_found, 0);
                    if (ContainsFlag(temp_r30, QB_OCCLUDER) != 0) {
                        fn_80055114(sp18, 0);
                    }
                    goto L_final;
                } while (var_r3 != NULL);
            }
        L_final:
            fn_80055114(sp18, 0);
        }
        break;
    default:
        return false;
    }
    return true;
}
