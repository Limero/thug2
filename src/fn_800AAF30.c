// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AAF30-0x800AB058 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
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
void Script_RunScript(void *, void *, void *, void *, void *);
void CStruct_delete(void *, void *);
void AddChecksum(void *, void *, void *);
void CStruct_new(s32 arg0);
s32 CStruct_ctor();
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009F204(s32, s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_800F0AFC(CStruct *arg0);
void AddInteger(CStruct *arg0, s32 arg1, s32 arg2);
void fn_800AAF30(Obj_t *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    Vt_t *temp_r9;
    temp_r9 = arg0->unk0x8;
    ((void (*)(void *))temp_r9->unk0x4C)((char *)arg0 + temp_r9->unk0x48);
    sp8 = 0;
    if (GetChecksum_2(arg1, QB_TRIGGERSCRIPT, &sp8, 0) != 0) {
        spC = 0;
        GetStructure_2(arg1, QB_PARAMS, &spC, 0);
        fn_8009F204(arg0, sp8, spC);
    }
    if (GetInteger(arg1, QB_COLOR, &sp10, 0) != 0) {
        temp_r30 = fn_800F0AFC(arg1);
        CStruct_new(8);
        temp_r31 = CStruct_ctor();
        AddChecksum(temp_r31, QB_NAME, temp_r30);
        AddInteger(temp_r31, QB_COLOR, sp10);
        Script_RunScript(QB_SETOBJECTCOLOR, temp_r31, arg0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
}
