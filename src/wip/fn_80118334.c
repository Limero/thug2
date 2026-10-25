// WIP DRAFT (concrete attempt;)
// family=m2c range=0x80118334-0x80118420 size=236B
// PARKED: display-free-mem candidate scored 12.5%; target heap-pointer and iteration helper ABI differ.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CStruct_delete(CStruct *, s32);
s32 fn_8000FA70(Unk_1BA9BD24 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
void CStruct_dtor(CStruct *);
s32 fn_8000FA54(Unk_C8FEE62D *);
s32 CStruct_ctor(s32);
bool ScriptDisplayFreeMem(void) {
    s32 temp_r28;
    s32 temp_r31;
    Unk_9994C3F5 *temp_r30;
    Unk_C7387A53 *var_r29;

    temp_r28 = *(s32 *)0x802FFE98;

temp_r31 = CStruct_ctor(CStruct_new(8, 0x80300000));
    var_r29 = fn_8000FA54(temp_r28);
    if (var_r29 != NULL) {
        do {
            temp_r30 = var_r29->unk0x34;
            CStruct_dtor(temp_r31);
            AddChecksum(temp_r31, QB_ID, Script_GenerateCRC(var_r29->unk0x44));
            AddInteger(temp_r31, QB_FREE_MEM, MemAvailable(temp_r30));
            AddInteger(temp_r31, QB_MIN_FREE_MEM, temp_r30->unk0x8);
            Script_RunScript(QB_UPDATEDISPLAYFREEMEMORY, temp_r31, 0, 0, 0);
            var_r29 = fn_8000FA70(temp_r28, var_r29);
        } while (var_r29 != NULL);
    }
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
