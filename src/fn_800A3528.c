// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3528-0x800A35D4 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A3528(Unk_C7387A53 *arg0) {
    s32 temp_r0;
    CStruct *temp_r10;
    void *temp_r11;
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    Unk_F5317C5D *temp_r9_3;
    void *var_r31;

    temp_r9 = *(CStruct **)&arg0->unk0x3C;
    temp_r0 = temp_r9->unk0x4;
    var_r31 = temp_r9;
    if (temp_r0 == -1) {
        var_r31 = NULL;
    }
    while (var_r31 != NULL) {
        temp_r10 = var_r31;
        temp_r9_2 = *(CStruct **)&temp_r10->unk0xC;
        temp_r0 = temp_r9_2->unk0x4;
        var_r31 = temp_r9_2;
        if (temp_r0 == -1) {
            var_r31 = NULL;
        }
        *(s32 *)(*(s32 *)((char *)((char *)temp_r10) + 0x10) + 0xC) =  temp_r10->unk0xC;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r10) + 0xC) + 0x10) =  temp_r10->unk0x10;
        *(CStruct **)&temp_r10->unk0x10 = temp_r10;
        temp_r11 = *(void **)&temp_r10->unk0x4;
        *(CStruct **)&temp_r10->unk0xC = temp_r10;
        if (temp_r11 != NULL) {
            temp_r9_3 = *(Unk_F5317C5D **)&((Unk_9994C3F5 *)temp_r11)->unk0x8;
            ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(temp_r11 + temp_r9_3->unk0x8, 3);
        }
    }
}
