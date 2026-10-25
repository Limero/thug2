// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C51A4-0x801C52EC (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct VT_8009 {
    char pad0x0[0x40];
    s16 unk0x40;
    char pad0x42[0x2];
    s32 unk0x44;
} VT_8009;

s32 GetChecksum_3(s32, s32);
void fn_801C51A4(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r11;
    void *temp_r11;
    void *temp_r3;
    void *temp_r3_2;
    void *temp_r3_3;
    void *temp_r3_4;
    VT_8009 *temp_r9;
    VT_8009 *temp_r9_2;
    VT_8009 *temp_r9_3;
    VT_8009 *temp_r9_4;
    VT_8009 *temp_r9_5;

    arg0->unk0x1C = arg1;
    if (arg1 == 0) {
        var_r11 = 1;
        if (!(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x114) & 2)) {
            var_r11 = 0;
        }
        if (var_r11 == 0) {
            goto block_4;
        }
    } else {
block_4:
        temp_r0 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x38) + 0x20);
        switch (temp_r0) {                          
        case 0:
            temp_r11 = arg0->unk0x34;
            temp_r9 = *(VT_8009 **)((char *)temp_r11 + 0x18);
            ((s32 (*)(void *, void *))temp_r9->unk0x44)((char *)temp_r11 + temp_r9->unk0x40, arg1);
            temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKATERROTATE);
            temp_r9_2 = *(VT_8009 **)((char *)temp_r3 + 0x18);
            ((s32 (*)(void *, void *))temp_r9_2->unk0x44)((char *)temp_r3 + temp_r9_2->unk0x40, arg1);
            temp_r3_2 = GetChecksum_3(arg0->unk0xC, QB_SKATERADJUSTPHYSICS);
            temp_r9_3 = *(VT_8009 **)((char *)temp_r3_2 + 0x18);
            ((s32 (*)(void *, void *))temp_r9_3->unk0x44)((char *)temp_r3_2 + temp_r9_3->unk0x40, arg1);
            temp_r3_3 = GetChecksum_3(arg0->unk0xC, QB_SKATERFINALIZEPHYSICS);
            temp_r9_4 = *(VT_8009 **)((char *)temp_r3_3 + 0x18);
            ((s32 (*)(void *, void *))temp_r9_4->unk0x44)((char *)temp_r3_3 + temp_r9_4->unk0x40, arg1);
            return;
        case 1:
            temp_r3_4 = GetChecksum_3(arg0->unk0xC, QB_WALK);
            temp_r9_5 = *(VT_8009 **)((char *)temp_r3_4 + 0x18);
            ((s32 (*)(void *, void *))temp_r9_5->unk0x44)((char *)temp_r3_4 + temp_r9_5->unk0x40, arg1);
            return;
        }
    }
}