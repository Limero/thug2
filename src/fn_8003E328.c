// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E328-0x8003E554 (556B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
void GetArray(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801293FC(void *, s32);
s32 GetFacePointsStruct(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r29;
    s32 var_r29_2;
    register s32 var_r3 __asm__("r3");
    sp8 = 0;
    spC = 0;
    sp10 = 0;
    sp14 = 0;
    GetArray(arg1, QB_LEFT_EYE, &sp8, 0);
    var_r3 = 0;
    if (sp8 != 0) {
        arg0->unk0x0 = fn_801293FC(sp8, 0);
        arg0->unk0x4 = fn_801293FC(sp8, 1);
        GetArray(arg1, QB_RIGHT_EYE, &spC, 0);
        var_r3 = 0;
        if (spC != 0) {
            arg0->unk0x8 = fn_801293FC(spC, 0);
            arg0->unk0xC = fn_801293FC(spC, 1);
            GetArray(arg1, QB_NOSE, &sp10, 0);
            var_r3 = 0;
            if (sp10 != 0) {
                arg0->unk0x10 = fn_801293FC(sp10, 0);
                arg0->unk0x14 = fn_801293FC(sp10, 1);
                GetArray(arg1, QB_LIPS, &sp14, 0);
                var_r3 = 0;
                if (sp14 != 0) {
                    var_r29 = 0;
                    arg0->unk0x18 = fn_801293FC(sp14, 0);
                    arg0->unk0x1C = fn_801293FC(sp14, 1);
                    arg0->unk0x20 = GetFloat(arg1, QB_H, (char *)arg0 + 0x24, 0);
                    if ((GetFloat(arg1, QB_S, (char *)arg0 + 0x28, 0) != 0) && ((s32) arg0->unk0x20 != 0)) {
                        var_r29 = 1;
                    }
                    arg0->unk0x20 = var_r29;
                    var_r29 = 0;
                    if ((GetFloat(arg1, QB_V, (char *)arg0 + 0x2C, 0) != 0) && ((s32) arg0->unk0x20 != 0)) {
                        var_r29 = 1;
                    }
                    arg0->unk0x20 = var_r29;
                    arg0->unk0x30 = 0;
                    arg0->unk0x34 = 0;
                    GetInteger(arg1, QB_WIDTH, (char *)arg0 + 0x30, 0);
                    GetInteger(arg1, QB_HEIGHT, (char *)arg0 + 0x34, 0);
                    var_r3 = 1;
                }
            }
        }
    }
    return var_r3;
}
