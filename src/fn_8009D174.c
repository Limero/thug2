// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D174-0x8009D208 (148B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8000A288(s32, s32);
void fn_8009D174(CStruct *arg0, s32 arg1) {
    void *temp_r11;
    Unk_4E705049 *temp_r9;
    void *var_r31;

    temp_r11 = arg0->unk0x4;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
    }
    if ((s32)((char *)arg0 + 8) != 0) {
        var_r31 = (char *)arg0 + 0x258;
        if ((s32)((char *)arg0 + 8) != (s32)var_r31) {
            do {
                var_r31 -= 0x94;
                fn_8000A288(var_r31 + 4, 2);
            } while ((s32)((char *)arg0 + 8) != (s32)var_r31);
        }
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
