// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A68D0-0x801A6984 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802AB870[];
extern char lbl_802AB888[];
extern void CStruct_delete(CStruct * arg0, s32 arg1);
void fn_801A68D0(Unk_1BB97F07 *arg0, s32 arg1) {
    s32 *var_r31;
    s32 temp_r3;
    u32 var_r30;
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x6E8 = (s32)lbl_802AB888;
    var_r30 = 0U;
    var_r31 = (s32 *)((char *)arg0 + 0x63C);
    do {
        temp_r3 = ((CStruct *)var_r31)->unk0x0;
        var_r31 += 1;
        if (temp_r3 != 0) {
            temp_r9 = (s32 *)(temp_r3 + 4);
            temp_r9->unk0x14 = (s32)lbl_802AB870;
            *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
            *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
            temp_r9->unk0xC = (s32)temp_r9;
            temp_r9->unk0x10 = (s32)temp_r9;
            Mem_Free((void *)temp_r3);
        }
        var_r30 += 1;
    } while (var_r30 <= 20U);
    if (arg0->unk0x6E4 != 0) {
        CStruct_delete(arg0->unk0x6E4, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
