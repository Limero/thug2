// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A9E4-0x8003AAB0 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
CStruct *CStruct_new(s32);
CStruct *CStruct_ctor(CStruct *);
void CStruct_delete(CStruct *, s32);
CStruct *fn_8003AE20(Unk_31DE137E *);
s32 fn_8003EDD0(CStruct *);
s32 fn_80129C08(CStruct *, s8 *, s32, s32, s32 (*)());
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 fn_8003A9E4(Unk_31DE137E *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    register s32 a0 __asm__("r28");
    register s32 a1 __asm__("r29");
    register s32 a3 __asm__("r27");
    s32 temp_r30;
    CStruct *temp_r31;
    s8 var_r0;
    u8 *var_r29;

    a0 = (s32)arg0;
    a1 = (s32)arg1;
    a3 = arg3;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80126FF4((Unk_80577C09 *)temp_r31, (CStruct *)((char *)a0 + 0x58));
    temp_r30 = fn_80129C08(temp_r31, (s8 *)a1, arg2, 1, 0);
    if (temp_r31 != NULL) {
        CStruct_delete(temp_r31, 3);
    }
    __asm__("" : "+r"(temp_r30));
    var_r29 = (u8 *)a1 + temp_r30;
    if ((a3 == 0) && (((fn_8003AE20((Unk_31DE137E *)a0) != NULL) &&
         (fn_8003EDD0(fn_8003AE20((Unk_31DE137E *)a0)) != 0)) ||
         (*(s32 *)((char *)a0 + 0x64) != 0))) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    *var_r29 = var_r0;
    return temp_r30 + 1;
}
