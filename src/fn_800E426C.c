// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E426C-0x800E4314 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80065220(s32, s32);
extern f32 lbl_8029A7A8;

typedef struct E426CNode {
    char pad0x0[0x78];
    f32 unk0x78;
    char pad0x7C[0x148 - 0x7C];
    s32 unk0x148;
} E426CNode;

typedef struct E426CArg0 {
    char pad0x0[0x1C];
    E426CNode *unk0x1C;
} E426CArg0;

s32 fn_800E426C(E426CArg0 *arg0, u32 arg1) {
    s32 var_r11;
    s32 var_r3;
    E426CNode *temp_r3;
    E426CNode *temp_r0;

    switch (arg1) {
    case QB_ISEMITTING:
        temp_r3 = arg0->unk0x1C;
        var_r11 = 0;
        if (temp_r3->unk0x148 != 0 || temp_r3->unk0x78 > lbl_8029A7A8) {
            var_r11 = 1;
        }
        var_r3 = 1;
        if (var_r11 == 0) {
            var_r3 = 0;
        }
        return var_r3;
    case QB_APPLYENVBRIGHTNESS:
        temp_r0 = arg0->unk0x1C;
        var_r3 = 0;
        if (temp_r0 != NULL) {
            var_r3 = fn_80065220((s32) temp_r0, QB_APPLYENVBRIGHTNESS);
        }
        return var_r3;
    default:
        var_r3 = 2;
        return var_r3;
    }
}
