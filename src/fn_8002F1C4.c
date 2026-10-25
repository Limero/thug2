// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F1C4-0x8002F298 (212B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80032A70(s32);
void fn_8002F1C4(Unk_C7387A53 *arg0) {
    void *temp_r31;
    Unk_F5317C5D *temp_r9;
    void *var_r29;
    void *var_r30;
    void *var_r9;
    void *var_r9_2;

    var_r9 = arg0->unk0x24;
    if ((s32) ((CStruct *)var_r9)->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r30 = (var_r9 != NULL) ? var_r9 - 4 : NULL;
    if (var_r30 != NULL) {
        do {
            temp_r31 = var_r30 + 4;
            var_r9_2 = ((CStruct *)temp_r31)->unk0xC;
            if ((s32) ((CStruct *)var_r9_2)->unk0x4 == -1) {
                var_r9_2 = NULL;
            }
            var_r29 = (var_r9_2 != NULL) ? var_r9_2 - 4 : NULL;
            if (fn_80032A70(var_r30) == 0) {
                *(s32 *)(*(s32 *)((char *)((char *)temp_r31) + 0x10) + 0xC) =  ((CStruct *)temp_r31)->unk0xC;
                *(s32 *)(*(s32 *)((char *)((char *)temp_r31) + 0xC) + 0x10) =  ((CStruct *)temp_r31)->unk0x10;
                ((CStruct *)temp_r31)->unk0xC = temp_r31;
                ((CStruct *)temp_r31)->unk0x10 = temp_r31;
                if (var_r30 != NULL) {
                    temp_r9 = ((CScript *)var_r30)->unk0x18;
                    ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r31 + temp_r9->unk0x8, 3);
                }
            }
            var_r30 = var_r29;
        } while (var_r30 != NULL);
    }
}
