// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AACC0-0x800AAE80 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x8];
    void *unk0x8;
} Obj_t;
typedef struct {
    char pad0x0[0x48];
    s16 unk0x48;
    char pad0x4A[0x2];
    s32 unk0x4C;
} Vt_t;
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_8009FB20(void *, void *);
void *Mem_NewZero(s32 size);
void fn_800B61F4(void *);
void fn_8009F204(void *, void *, void *);
extern char lbl_80301A38[];
void AddChecksum(void *, s32, s32);
s32 fn_801259C8(s32, s32);
void *fn_800A1AE8(s32, CStruct *, Unk_C7387A53 *, s32);
void Script_RunScript(void *, void *, void *, void *, void *);
s32 GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_800F0AFC(CStruct *arg0);
void AddInteger(void *, s32, s32);
void CStruct_new(s32 arg0);
s32 CStruct_ctor();
void CStruct_delete(void *, s32);
void *GetChecksum_3(void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void *fn_800D034C(void *);
void *fn_800DB9D4(void *);
void *fn_800AACC0(CStruct *arg0, s32 arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    void *temp_r3;
    void *temp_r29;
    Vt_t *temp_r9;
    temp_r30 = *(s32 *)&lbl_80301A38;
    temp_r29 = fn_800A1AE8(temp_r30, fn_801259C8(QB_GAMEOBJ_COMPOSITE_STRUCTURE, 0), arg0, 0);
    fn_8009FB20(temp_r29, fn_800D034C(Mem_NewZero(0x98)));
    Script_RunScript(QB_GAMEOBJ_ADD_COMPONENTS, arg0, temp_r29, 0, 0);
    fn_8009FB20(temp_r29, fn_800DB9D4(Mem_NewZero(0x58)));
    temp_r9 = ((Obj_t *)temp_r29)->unk0x8;
    ((void (*)(void *))temp_r9->unk0x4C)((char *)temp_r29 + temp_r9->unk0x48);
    if (GetInteger(arg0, QB_COLOR, &sp8, 0) != 0) {
        temp_r30_2 = fn_800F0AFC(arg0);
        CStruct_new(8);
        temp_r31 = CStruct_ctor();
        AddChecksum(temp_r31, QB_NAME, temp_r30_2);
        AddInteger(temp_r31, QB_COLOR, sp8);
        Script_RunScript(QB_SETOBJECTCOLOR, temp_r31, temp_r29, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    temp_r3 = GetChecksum_3(temp_r29, QB_MODEL);
    if (temp_r3 != 0) {
        fn_800B61F4(temp_r3);
    }
    spC = 0;
    if (GetChecksum_2(arg0, QB_TRIGGERSCRIPT, &spC, 0) != 0) {
        sp10 = 0;
        GetStructure_2(arg0, QB_PARAMS, &sp10, 0);
        fn_8009F204(temp_r29, spC, sp10);
    }
    return temp_r29;
}
