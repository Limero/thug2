// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB4D8-0x800CB5B0 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x18];
    s16 unk0x18;
    char pad0x1A[0x2];
    s32 unk0x1C;
    s16 unk0x20;
    char pad0x22[0x2];
    s32 unk0x24;
} Unk_CB4D8_vt;
s32 ContainsFlag(CStruct *, void *);
void AddChecksum(CStruct *, void *, void *);
s32 fn_80128E34(CStruct *, void *, void *, void *);
void *fn_800CBF00(Unk_C7387A53 *, s32, s32);
bool fn_800CB4D8(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;
    void *temp_r3;
    register CStruct *temp_r9 __asm__("r9");
    Unk_CB4D8_vt *temp_r9_2;
    Unk_CB4D8_vt *temp_r9_3;
    register Unk_31DE137E *var_r30 __asm__("r30");

    sp8 = 0;
    temp_r9 = arg0->unk0x38;
    {
        s32 t = (s32) temp_r9->unk0x4;

        var_r30 = temp_r9;
        if (t == -1) {
            var_r30 = NULL;
        }
    }
    fn_80128E34(arg2, QB_SUBSETID, &sp8, 0);
    AddChecksum(arg2, QB_REFERENCECHECKSUM, var_r30->unk0x60);
    temp_r3 = fn_800CBF00(arg0, sp8, ContainsFlag(arg2, QB_HEAD));
    temp_r9_2 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
    ((s32 (*)(void *, void *))temp_r9_2->unk0x24)(temp_r3 + temp_r9_2->unk0x20, arg2);
    temp_r9_3 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
    ((s32 (*)(void *))temp_r9_3->unk0x1C)(temp_r3 + temp_r9_3->unk0x18);
    return true;
}
