// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EE918-0x800EEAE0 (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_80129528(CStruct *, s32);

void fn_800EE918(CScript *arg0) {
    CStruct *cag_ptr;
    CStruct *loop_ptr;
    void *sp8;
    f32 *var_r29;
    f32 *var_r28;
    f32 *var_r27;
    f32 *var_r26;
    s32 temp_r0;
    s32 var_r25;

    var_r25 = 0;
    GetStructure_2((CStruct *)GetStructure(QB_PLAYERVEHICLESOUNDS, 1), *(s32 *)(*(s32 *)((char *)arg0 + 0xB8) + 0x1328), (s32 *)((char *)arg0 + 0x1C), 1);
    GetChecksum_2((CStruct *)arg0->unk0x1C, QB_ENGINESOUND, (s32 *)((char *)arg0 + 0x30), 0);
    GetChecksum_2((CStruct *)arg0->unk0x1C, QB_TIRESOUND, (s32 *)((char *)arg0 + 0x34), 0);
    GetArray((CStruct *)arg0->unk0x1C, QB_GEARS, (s32 *)&sp8, 1);
    temp_r0 = ((CStruct *)sp8)->unk0x4;
    arg0->unk0x38 = temp_r0;
    if (var_r25 < temp_r0) {
        var_r26 = (f32 *)((char *)arg0 + 0x48);
        var_r27 = (f32 *)((char *)arg0 + 0x44);
        var_r28 = (f32 *)((char *)arg0 + 0x40);
        var_r29 = (f32 *)((char *)arg0 + 0x3C);
        do {
            loop_ptr = (CStruct *)fn_80129528((CStruct *)sp8, var_r25);
            var_r25 += 1;
            GetFloat(loop_ptr, QB_UPSHIFTPOINT, var_r29, 1);
            var_r29 += 4;
            GetFloat(loop_ptr, QB_DOWNSHIFTPOINT, var_r28, 1);
            var_r28 += 4;
            GetFloat(loop_ptr, QB_BOTTOMRPM, var_r27, 1);
            var_r27 += 4;
            GetFloat(loop_ptr, QB_TOPRPM, var_r26, 1);
            var_r26 += 4;
        } while (var_r25 < arg0->unk0x38);
    }
    var_r29 = (f32 *)((char *)arg0 + 0x2C);
    GetStructure_2((CStruct *)arg0->unk0x1C, QB_COLLIDESOUND, (s32 *)var_r29, 1);
    if (arg0->unk0x20 != 0) {
        cag_ptr = (CStruct *)GetStructure(QB_PLAYERVEHICLESOUNDGLOBALPARAMETERS, 1);
        GetChecksum_2(cag_ptr, QB_CAGENGINESOUND, (s32 *)((char *)arg0 + 0x30), 1);
        GetChecksum_2(cag_ptr, QB_CAGTIRESOUND, (s32 *)((char *)arg0 + 0x34), 1);
        GetStructure_2(cag_ptr, QB_CAGCOLLIDESOUND, (s32 *)var_r29, 1);
    }
}
