// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001A9D4-0x8001AB78 (420B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2 -fno-branch-count-reg
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -fno-schedule-insns2 -fno-branch-count-reg
void dvd_read_safe(s32, s32, s32, s32);
void DCFlushRange(s32, s32);
s32 dvd_file_read_anywhere(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buffer[0x808];
    s32 *buf;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r31;
    s32 var_r9;
    s32 var_r11;
    s32 ctr;
    s32 temp_r0;
    s32 baddr;

    if ((arg1 & 0x1F) || (arg3 & 3) || ((s32) (arg1 & QB_UNKNOWN_0xFF000000) == QB_UNKNOWN_0x7E000000)) {
        baddr = (s32)&buffer[0];
        buf = (s32 *)((baddr + 0x1F) & QB_UNKNOWN_0xFFFFFFE0);
        var_r28 = arg2;
        var_r27 = arg1;
        var_r26 = arg3;
        var_r31 = arg3 & 3;
        if (var_r31 != 0) {
            dvd_read_safe(arg0, (s32)buf, var_r31, arg3);
            memcpy(arg1, buf, var_r31);
            DCFlushRange(arg1, var_r31);
            var_r27 = arg1 + var_r31;
            var_r26 = arg3 + var_r31;
            var_r28 = arg2 - var_r31;
        }
        goto loop_8;
body_8:
        {
            dvd_read_safe(arg0, (s32)buf, 0x2000, var_r26);
            var_r28 -= 0x2000;
            var_r26 += 0x2000;
            var_r11 = var_r27;
            var_r9 = (s32)buf;
            ctr = 0x1FF8;
            do {
                ctr -= 0x18;
                ((Unk_DB0E2BAB *)var_r11)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x0;
                ((Unk_DB0E2BAB *)var_r11)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x4;
                ((Unk_DB0E2BAB *)var_r11)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x8;
                ((Unk_DB0E2BAB *)var_r11)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0xC;
                ((Unk_DB0E2BAB *)var_r11)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x10;
                ((Unk_DB0E2BAB *)var_r11)->unk0x14 = ((Unk_DB0E2BAB *)var_r9)->unk0x14;
                var_r9 += 0x18;
                var_r11 += 0x18;
            } while (ctr != 0);
            temp_r0 = var_r27;
            ((Unk_DB0E2BAB *)var_r11)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x0;
            ((Unk_DB0E2BAB *)var_r11)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x4;
            DCFlushRange(temp_r0, 0x2000);
            var_r27 += 0x2000;
        }
loop_8:
        if (var_r28 > 0x2000) goto body_8;
        if (var_r28 > 0) {
            dvd_read_safe(arg0, (s32)buf, (var_r28 + 0x1F) & QB_UNKNOWN_0xFFFFFFE0, var_r26);
            memcpy(var_r27, buf, var_r28);
            DCFlushRange(var_r27, var_r28);
        }
    } else {
        dvd_read_safe(arg0, arg1, arg2, arg3);
    }
    return arg2;
}
