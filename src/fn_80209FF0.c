// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209FF0-0x8020A0F4 (260B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern s32 fn_80209E50(Unk_BBA0A5F0 * arg0, s32 arg1, s32 arg2);

void fn_80209FF0(Unk_CF8B1206 *arg0) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r28;
    s32 var_r29;
    char *var_r30;

    if ((s32) arg0->unk0x130C != 0) {
        temp_r29 = arg0->unk0x1310;
        if (temp_r29 == 0) {
            temp_r30 = arg0->unk0x1318;
            temp_r3 = fn_800145AC();
            if ((u32) (temp_r3 - temp_r30) > arg0->unk0x1314) {
                arg0->unk0x130C = temp_r29;
                return;
            }
        }
        if ((s32) arg0->unk0x1370 != 0) {
            if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x20) + 0x80) != 0) {
                arg0->unk0xA68 = 1;
                temp_r3 = fn_80209E50(arg0, arg0->unk0x1370, arg0->unk0x1374);
                if (temp_r3 == 0) {
                    arg0->unk0xA68 = temp_r3;
                }
                if ((s32) arg0->unk0x130C == 0) {
                    return;
                }
            } else {
                arg0->unk0xA68 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x20) + 0x80);
            }
        }
        var_r29 = 0;
        if (var_r29 < (s32) arg0->unk0x131C) {
            var_r28 = 0;
            var_r30 = (char *)arg0 + (s32)0x1348;
            do {
                if (fn_80209E50(arg0, *(s32 *)((char *)var_r30 - (s32)0x28), ((CStruct *)var_r30)->unk0x0) != 0) {
                    arg0->unk0xA68 = var_r28;
                }
                if ((s32) arg0->unk0x130C == 0) {
                    return;
                }
                var_r29 += 1;
                var_r30 += 4;
            } while (var_r29 < (s32) arg0->unk0x131C);
        }
    }
}
