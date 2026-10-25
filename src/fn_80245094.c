// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80245094-0x80245128 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80244440(Unk_7044F700 * arg0, s32 arg1, s32 arg2, CStruct * arg3);

s32 fn_80245094(Unk_09BB4394 *arg0, CStruct *arg1) {
    s32 var_r30;
    CScript *var_r31;
    u32 temp_r28;
    u32 temp_r29;
    s32 temp_r3;
    u32 a;
    u32 b;
    u32 c;
    u32 d;

    var_r30 = -0x3E8;
    a = arg0->unk0x7;
    b = arg0->unk0x9;
    c = arg0->unk0x8;
    d = arg0->unk0xA;
    var_r31 = *((s32 * *)&arg0->unk0xC);
    temp_r28 = (a + b) >> 1U;
    temp_r29 = (c + d) >> 1U;
    if (var_r31 != NULL) {
        do {
            temp_r3 = fn_80244440((s32)var_r31, temp_r28, temp_r29, arg1);
            if (temp_r3 > var_r30) {
                var_r30 = temp_r3;
            }
            var_r31 = *((s32 * *)&var_r31->unk0x18);
        } while (var_r31 != NULL);
    }
    if (var_r30 != -0x3E8) {
        return var_r30;
    }
    return 0;
}
