// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7C20-0x800B7CC8 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80298C1C;
extern f32 lbl_80298C20;
extern char lbl_80298C28[];
void fn_8009F53C(Unk_C8FEE62D * arg0);
void *fn_800B7C20(Unk_C8FEE62D *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    s32 var_ctr;
    char *temp_r9;

    fn_8009F53C(arg0);
    *(s32 *)((char *)arg0 + (s32)0x18) = (s32)lbl_80298C28;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    *(s32 *)((char *)arg0 + (s32)0x4) = QB_CUTSCENEUPDATE;
    temp_r9 = (char *)arg0 + 0x20;
    temp_f13 = lbl_80298C1C;
    *(f32 *)(temp_r9) = temp_f13;
    temp_f0 = lbl_80298C20;
    *(f32 *)((char *)arg0 + (s32)0x34) = temp_f13;
    *(f32 *)((char *)arg0 + (s32)0x24) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x28) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x2C) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x30) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x38) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x3C) = temp_f0;
    *(f32 *)(temp_r9 + 0x20) = temp_f0;
    *(f32 *)(temp_r9 + 0x24) = temp_f0;
    *(f32 *)(temp_r9 + 0x28) = temp_f13;
    *(f32 *)(temp_r9 + 0x2C) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x50) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x54) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x58) = temp_f0;
    *(f32 *)((char *)arg0 + (s32)0x5C) = temp_f13;
    return arg0;
}
