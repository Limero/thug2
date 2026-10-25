// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010C5DC-0x8010C6C0 (228B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8010BB8C(s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 fn_8010C4C8(CStruct *);

s32 fn_8010C5DC(CStruct *arg0, s32 arg1, f32 farg1) {
    volatile s32 sp8;
    void *volatile spC;
    f32 sp10;
    u32 var_r30;
    s32 temp_r31;

    temp_r31 = fn_8010BB8C(arg1);
    if (GetStructure_2(arg0, temp_r31, &sp8, 0) != 0) {
        return sp8;
    }
    GetArray(arg0, temp_r31, &spC, 1);
    for (var_r30 = 0; var_r30 < *((u32 *)&((CStruct *)spC)->unk0x4); var_r30++) {
        temp_r31 = fn_80129528(spC, var_r30);
        if (GetFloat(temp_r31, QB_USEUPTO, &sp10, 0) == 0) {
            return fn_8010C4C8(temp_r31);
        }
        if (farg1 <= sp10) {
            return fn_8010C4C8(temp_r31);
        }
    }
    return 0;
}
