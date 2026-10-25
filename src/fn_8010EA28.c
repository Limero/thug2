// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EA28-0x8010EC14 (492B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 fn_801288C4(CStruct *, s32);
extern s32 fn_80127358(CStruct *, Unk_C7387A53 *);
extern s32 fn_8012543C(s32);
extern void fn_8012DE30(Unk_5D1D68CC *);
extern s32 fn_80125568(s32);
extern void fn_801252BC(Unk_5D1D68CC *);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_80125480(s32);
extern void fn_8003E7CC(s32);
extern s32 CStruct_new(s32);
extern s32 fn_80128F94(void);
extern s32 CStruct_ctor(s32);
extern void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);

struct sc_act_out {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC_pad;
};

struct sc_act_bf {
    u32 hi9 : 9;
    u32 typ : 7;
    u32 lo16 : 16;
};

bool ScriptChange(CStruct *pParams, CScript *pScript) {
    struct sc_act_out loc;
    s32 sp18;
    Unk_4D85B2BF *var_r29;
    register s32 *temp_r3 __asm__("r9");
    Unk_1D62F22E *temp_r3_2;
    Unk_1D62F22E *temp_r3_3;
    s32 temp_r30;
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r5;

    sp18 = 0;
    GetChecksum_2(pParams, QB_GLOBALNAME, &sp18, 0);
    if (sp18 != 0) {
        var_r29 = (s32 *)fn_801288C4(pParams, QB_NEWVALUE);
        if (var_r29 == NULL) {
            return false;
        }
    } else {
        var_r29 = (s32 *)fn_80127358(pParams, 0);
        if (var_r29 == NULL) {
            return false;
        }
        sp18 = var_r29->unk0x4;
    }
    temp_r3 = (s32 *)fn_8012543C(sp18);
    if (temp_r3 == NULL) {
        return false;
    }
    temp_r0 = ((Unk_1D62F22E *)temp_r3)->unk0x2;
    if (temp_r0 == 7) {
        return false;
    }
    if (temp_r0 == 8) {
        return false;
    }
    if (temp_r0 == 9) {
        return false;
    }
    __asm__ volatile("" ::: "r3");
    temp_r30 = ((Unk_1D62F22E *)temp_r3)->unk0x8;
    fn_8012DE30(temp_r3);
    temp_r3_2 = (s32 *)fn_80125568(sp18);
    temp_r3_2->unk0x8 = temp_r30;
    fn_801252BC(&loc);
    ((struct sc_act_bf *)&loc.unk0)->typ = var_r29->unk0x0 & 0x7F;
    loc.unk8 = var_r29->unk0x8;
    if (((loc.unk0 & 0x7F0000) == 0xD0000) && (ContainsFlag(pParams, QB_RESOLVE) != 0)) {
        temp_r3_3 = (s32 *)fn_80125480(loc.unk8);
        if (temp_r3_3 != NULL) {
            ((struct sc_act_bf *)&loc.unk0)->typ = temp_r3_3->unk0x2;
            loc.unk8 = temp_r3_3->unk0xC;
        }
    }
    temp_r0 = (*(u16 *)&loc.unk0) & 0x7F;
    switch (temp_r0) {
    case 2:
        temp_r3_2->unk0x2 = temp_r0;
        *((f32 *)&temp_r3_2->unk0xC) = *(f32 *)&loc.unk8;
        break;
    case 13:
    case 1:
        temp_r3_2->unk0x2 = temp_r0;
        temp_r3_2->unk0xC = loc.unk8;
        break;
    case 12:
        temp_r3_2->unk0x2 = temp_r0;
        fn_8003E7CC(0xC);
        temp_r4 = fn_80128F94();
        temp_r3_2->unk0xC = temp_r4;
        fn_80126E28(temp_r4, loc.unk8);
        break;
    case 10:
        temp_r3_2->unk0x2 = temp_r0;
        temp_r5 = CStruct_ctor(CStruct_new(8));
        temp_r3_2->unk0xC = temp_r5;
        fn_80126FF4(temp_r5, loc.unk8);
        break;
    }
    loc.unk8 = 0;
    return true;
}
