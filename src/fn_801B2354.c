// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2354-0x801B23F8 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct { s32 unk0; void *unk4; } unk_801B2354_s;
void fn_801B2354(CScript *arg0, Unk_F5317C5D *arg1, s32 arg2, s32 arg3) {
    s32 (*var_r9)(char *, s32, s32);
    unk_801B2354_s temp_entry;
    s16 temp_r10;
    s16 temp_r4;
    s32 var_r0;
    Unk_E71E4713 *temp_r9;
    s32 temp_r11;

    temp_r10 = arg1->unk0xA;
    if (temp_r10 != 0) {
        if (temp_r10 >= 0) {
            temp_r11 = *(s32 *)((char *)arg0 + *((s16 *)&arg1->unk0xC));
            temp_entry = ((unk_801B2354_s *)((char *)((temp_r10 * 8) + temp_r11)))[-1];
            var_r9 = (s32 (*)(char *, s32, s32))temp_entry.unk4;
        } else {
            var_r9 = (s32 (*)(char *, s32, s32)) arg1->unk0xC;
        }
        temp_r4 = arg1->unk0x8;
        if (temp_r10 >= 0) {
            var_r0 = (temp_entry.unk0 >> 0x10) + temp_r4;
        } else {
            var_r0 = temp_r4;
        }
        var_r9((char *)arg0 + var_r0, arg2, arg3);
        return;
    }
    temp_r9 = arg0->unk0x18;
    ((s32 (*)(void *, void *))(temp_r9->unk0x64))((char *)arg0 + temp_r9->unk0x60, *(s32 *)arg1);
}
