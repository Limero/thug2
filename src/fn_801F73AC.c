// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F73AC-0x801F741C (112B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
s32 fn_801F5898(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
bool fn_801F73AC(Unk_F0C166E4 *arg0, CStruct *arg1) {
    s32 sp8;
    void *temp_r3;

    temp_r3 = fn_801F5898();
    arg0->unk0xAC00 = temp_r3;
    if (temp_r3 != NULL) {
        sp8 = 0;
        if (GetInteger(arg1, 0, &sp8, 0) != 0) {
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xAC00) + 0x2CC) = sp8;
        }
    }
    return true;
}
