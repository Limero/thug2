// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135AFC-0x80135C80 (388B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D4E4[];
extern u32 lbl_8039D4E8;
extern char lbl_8039D4EC[];
extern char lbl_8039D4F0[];
extern u8 lbl_8039D4F4;
extern char lbl_8039D940[];
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
void AUDSimpleAudioReset(void);
void writeChannelData(u16 *, s32, void *, s32, u32);

typedef struct { u32 unk00; u32 unk04; u32 unk08; u32 unk0C; } AxArr;

// audioDecode @ 0x80135AFC
s32 audioDecode(s32 arg0, void *arg1, u32 arg2) {
    s32 var_r26;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r5;
    u32 temp_r11;
    u32 step;
    u32 var_r31;
    char *ax;
    AxArr *arr;

    var_r26 = OSDisableInterrupts();
    ax = &lbl_8039D940;
    arr = (AxArr *)(ax + 0xF4);
    if (arr[((Unk_74BF3C95 *)ax)->unk0xE8].unk00 < ((Unk_4284167D *)ax)->unk0xD8) {
        AUDSimpleAudioReset();
    }
    step = lbl_8039D4F4 * 2;
    temp_r3 = *(u32 *)&lbl_8039D4EC;
    temp_r11 = *(u32 *)&lbl_8039D4F0;
    if (temp_r3 >= temp_r11) {
        if ((u32)(lbl_8039D4E8 - (temp_r3 - temp_r11)) < arg2) {
            goto block_8;
        }
        var_r31 = lbl_8039D4E8 - temp_r3;
        if (var_r31 >= arg2) {
            writeChannelData(*(u32 *)&lbl_8039D4E4 + temp_r3 * step, arg0, arg1, 0U, arg2);
        } else {
            writeChannelData(*(u32 *)&lbl_8039D4E4 + temp_r3 * step, arg0, arg1, 0U, var_r31);
            writeChannelData(*(u32 *)&lbl_8039D4E4, arg0, arg1, var_r31, arg2 - var_r31);
        }
    } else {
        if (temp_r11 - temp_r3 < arg2) {
block_8:
            OSRestoreInterrupts(var_r26);
            return 0U;
        }
        writeChannelData(*(u32 *)&lbl_8039D4E4 + temp_r3 * step, arg0, arg1, 0U, arg2);
    }
    temp_r5 = lbl_8039D4E8;
    temp_r0 = *(u32 *)&lbl_8039D4EC + arg2;
    *(u32 *)&lbl_8039D4EC = temp_r0;
    if (temp_r0 >= temp_r5) {
        *(u32 *)&lbl_8039D4EC = temp_r0 - temp_r5;
    }
    OSRestoreInterrupts(var_r26);
    return 1U;
}
