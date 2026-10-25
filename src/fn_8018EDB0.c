// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8018EDB0-0x8018EE80 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_801745B4(void *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801EFACC(s32);
void fn_801EFADC(s32);
void fn_8018EDB0(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_lbl;
    s32 temp_r30;
    void *temp_r31;
    CScript *temp_r9;
    CScript *temp_r9_2;

    var_lbl = *(s32 *)&lbl_80305EAC;
    arg0->unk0x70 = (s32)(arg0->unk0x70 & QB_UNKNOWN_0xFEFFFFFF);
    temp_r31 = (void *)fn_801745B4((void *)var_lbl);
    temp_r30 = GetChecksum_3((Unk_6A70655D *)temp_r31, QB_SKATERENDRUN);
    switch (arg0->unk0x28) {
    case 1:
        temp_r9 = ((Unk_9994C3F5 *)temp_r31)->unk0x8;
        ((s32 (*)(void *, void *, s32, void *))temp_r9->unk0x1C)(temp_r31 + *(s16 *)((char *)temp_r9 + 0x18), QB_ENDOFRUNDONE, 0, (void *)arg1);
        fn_801EFACC(temp_r30);
        return;
    case 0:
        temp_r9_2 = ((Unk_9994C3F5 *)temp_r31)->unk0x8;
        ((s32 (*)(void *, void *, s32, void *))temp_r9_2->unk0x1C)(temp_r31 + *(s16 *)((char *)temp_r9_2 + 0x18), QB_GOAL_ENDOFRUNDONE, 0, (void *)arg1);
        fn_801EFADC(temp_r30);
        return;
    }
}
