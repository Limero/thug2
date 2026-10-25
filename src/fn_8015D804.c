// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D804-0x8015DA34 (560B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern void* lbl_80301A38;
extern void* lbl_802FFE98;
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80174AB8(void * arg0, s32 arg1);
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 fn_800A3528(Unk_C7387A53 * arg0);
extern s32 fn_80141FA4(Unk_5FCDF30E * arg0);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8005572C(void);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
extern void fn_80143258(s32 arg0, s32 arg1);
extern void fn_80206EA4(Unk_59E38960 * arg0, void * arg1);
extern void fn_801436E0(Unk_F8E9878F * arg0, s32 arg1);
extern void fn_800B33EC(CScript * arg0, Unk_C8FEE62D * arg1, s32 arg2, s32 arg3);
typedef struct { char _pad[0x1E4]; s32 _arr[64]; } S1_8015D804;
typedef struct { char _pad[0x1A4]; s32 _arr[64]; } S2_8015D804;
bool ScriptRefreshSkaterModel(CStruct *pParams, CScript *pScript) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    Unk_C7387A53 *temp_r31;
    s32 temp_r28;
    char *temp_r26;

    spC = 0;
    sp10 = 0;
    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    spC = sp8;
    sp10 = sp8;
    GetInteger(pParams, QB_PROFILE, &spC, 0);
    GetInteger(pParams, QB_SKATER, &sp10, 0);
    temp_r31 = fn_801746A4(lbl_80305EAC, sp10);
    if (temp_r31->unk0x2E8 == 0) {
        s32 obj = fn_800A398C(lbl_80301A38, QB_BAILBOARD);
        if (obj != NULL) {
            void *vt = *((void * *)&((Unk_9994C3F5 *)obj)->unk0x8);
            ((s32 (*)(void *))(s32)*((void * *)&((Unk_C6B642AC *)vt)->unk0x3C))(
                (char *)obj + ((Unk_C6B642AC *)vt)->unk0x38);
            fn_800A3528(lbl_80301A38);
        }
    }
    temp_r28 = fn_80174AB8(lbl_80305EAC, spC);
    temp_r26 = (char *)temp_r28 + 4;
    {
        s32 g = lbl_802FFE98;
        fn_8000F2F8(g, ((S1_8015D804 *)(s32)g)->_arr[fn_80141FA4(temp_r31)]);
    }
    fn_8005572C();
    {
        register s32 model __asm__("r30");
        void *vt2;
        void *m7;
        void *this2;
        model = GetChecksum_3(temp_r31, QB_MODEL);
        vt2 = *((void * *)&((CScript *)model)->unk0x18);
        m7 = (char *)vt2 + 0x70;
        this2 = (char *)model + *(s16 *)m7;
        ((s32 (*)(void *, void *, s32, s32, s32))(s32)*((void * *)&((CStruct *)m7)->unk0x4))(
            this2, (void *)temp_r26, 0, fn_80141FA4(temp_r31), 0);
    }
    fn_8000F320(lbl_802FFE98);
    {
        s32 g = lbl_802FFE98;
        fn_8000F2F8(g, ((S2_8015D804 *)(s32)g)->_arr[fn_80141FA4(temp_r31)]);
    }
    fn_80143258(temp_r31, temp_r28);
    fn_80206EA4(GetChecksum_3(temp_r31, QB_TRICK), temp_r28);
    fn_801436E0(temp_r31, temp_r28);
    fn_8000F320(lbl_802FFE98);
    if (GetChecksum_2(pParams, QB_NO_BOARD, &sp14, 0) != 0) {
        s32 model2 = GetChecksum_3(temp_r31, QB_MODEL);
        void *vt3;
        fn_800B33EC(model2, QB_BOARD, 1, 1);
        vt3 = *((void * *)&((CScript *)model2)->unk0x18);
        ((s32 (*)(void *))(s32)*((void * *)&((Unk_89391A04 *)vt3)->unk0x14))(
            (char *)model2 + ((Unk_89391A04 *)vt3)->unk0x10);
    }
    return true;
}
