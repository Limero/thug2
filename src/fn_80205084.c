// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80205084-0x80205248 (452B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// doc-56: without these declarations ngccc emits `crclr cr1eq` before every
// call. All five shapes confirmed from the want's r3/r4/r5/r6 usage.
// Signatures copied verbatim from the already-matched sources so the arg
// types match exactly (a `void*` where the real callee takes `s32*` is a
// hard type error, not a warning).
s32 GetStructure(s32, s32);                                  // fn_80125954.c
s32 GetStructure_2(CStruct *, s32, void *, s32);               // fn_801284EC.c
s32 GetChecksum_2(CStruct *, s32, void *, s32);                // fn_801286D0.c
s32 GetArray(CStruct *, s32, void *, s32);                     // fn_801285A4.c
s32 GetFloat(CStruct *, s32, void *, s32);                     // fn_801282E0.c
s32 fn_80129528(s32, s32);

void fn_80205084(Unk_C8FEE62D *arg0) {
    void *sp8;
    s32 temp_r0;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r4;
    s32 var_r25;
    void *temp_r5;
    void *temp_r29;
    void *var_r26;
    void *var_r27;
    void *var_r28;
    void *var_r29;

    var_r25 = 0;
    // The want's register usage gives the exact shapes; m2c had dropped the
    // first callee's RESULT from the 2nd call's arg0 and passed 3 args to a
    // 4-arg callee. Reading r3/r4/r5/r6 off each `bl` is the reliable way to
    // recover these (see the callee table in the header).
    temp_r5 = GetStructure(QB_PLAYERVEHICLESOUNDS, 1);
    GetStructure_2((CStruct *)temp_r5, arg0->unk0xC4, (char *)arg0 + 0x28, 1);
    GetChecksum_2((CStruct *)arg0->unk0x28, QB_ENGINESOUND, (char *)arg0 + 0x3C, 0);
    GetChecksum_2((CStruct *)arg0->unk0x28, QB_TIRESOUND, (char *)arg0 + 0x40, 0);
    GetArray((CStruct *)arg0->unk0x28, QB_GEARS, &sp8, 1);
    temp_r0 = ((CStruct *)sp8)->unk0x4;
    arg0->unk0x44 = temp_r0;
    // The want seeds the four destination cursors in DESCENDING offset order
    // (r26=+0x54 first ... r29=+0x48 last). Hoisting those four assignments
    // out of the `if` body instead (so the loop becomes a plain `for`) was
    // tried and REGRESSED to 13.0% — keep them inside the guarded block.
    if (var_r25 < temp_r0) {
        var_r26 = (char *)arg0 + 0x54;
        var_r27 = (char *)arg0 + 0x50;
        var_r28 = (char *)arg0 + 0x4C;
        var_r29 = (char *)arg0 + 0x48;
        do {
            temp_r4 = var_r25;
            var_r25 += 1;
            temp_r30 = fn_80129528((s32)sp8, temp_r4);
            GetFloat((CStruct *)temp_r30, QB_UPSHIFTPOINT, var_r29, 1);
            var_r29 += 0x10;
            GetFloat((CStruct *)temp_r30, QB_DOWNSHIFTPOINT, var_r28, 1);
            var_r28 += 0x10;
            GetFloat((CStruct *)temp_r30, QB_BOTTOMRPM, var_r27, 1);
            var_r27 += 0x10;
            GetFloat((CStruct *)temp_r30, QB_TOPRPM, var_r26, 1);
            var_r26 += 0x10;
        } while (var_r25 < (s32) arg0->unk0x44);
    }
    temp_r29 = (char *)arg0 + 0x38;
    GetStructure_2((CStruct *)arg0->unk0x28, QB_COLLIDESOUND, temp_r29, 1);
    if ((s32) arg0->unk0x2C != 0) {
        temp_r30_2 = GetStructure(QB_PLAYERVEHICLESOUNDGLOBALPARAMETERS, 1);
        GetChecksum_2((CStruct *)temp_r30_2, QB_CAGENGINESOUND, (char *)arg0 + 0x3C, 1);
        GetChecksum_2((CStruct *)temp_r30_2, QB_CAGTIRESOUND, (char *)arg0 + 0x40, 1);
        GetStructure_2((CStruct *)temp_r30_2, QB_CAGCOLLIDESOUND, temp_r29, 1);
    }
}
