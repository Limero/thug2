// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003EA2C-0x8003EB5C (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"

void memcpy();
s32 strlen(const char *);

s32 fn_8003EA2C(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r30;
    s32 var_r10;
    s32 var_r7;
    void *var_r9;
    void *var_r11;
    void *var_r10_2;
    void *var_r8;
    void *d;
    char *s;
    register s32 len __asm__("r5");

    d = arg1;
    var_r9 = arg0 + 0x40;
    var_r11 = d;
    var_r10 = 0x4410;
    do {
        var_r10 -= 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x0;
        ((Unk_DB0E2BAB *)var_r11)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x4;
        ((Unk_DB0E2BAB *)var_r11)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x8;
        ((Unk_DB0E2BAB *)var_r11)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0xC;
        ((Unk_DB0E2BAB *)var_r11)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x10;
        temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x14;
        var_r9 += 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x14 = temp_r0;
        var_r11 += 0x18;
    } while (var_r10 != 0);
    d = d + 0x4420;
    var_r8 = d;
    temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x0;
    ((Unk_DB0E2BAB *)var_r11)->unk0x0 = temp_r0;
    var_r10_2 = arg0 + 8;
    temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x4;
    var_r7 = 0x30;
    ((Unk_DB0E2BAB *)var_r11)->unk0x4 = temp_r0;
    s = (char *) (arg0 + 0x4460);
    ((Unk_DB0E2BAB *)var_r11)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x8;
    ((Unk_DB0E2BAB *)var_r11)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0xC;
    do {
        var_r7 -= 0x18;
        ((Unk_DB0E2BAB *)var_r8)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x0;
        ((Unk_DB0E2BAB *)var_r8)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x4;
        ((Unk_DB0E2BAB *)var_r8)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x8;
        ((Unk_DB0E2BAB *)var_r8)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0xC;
        ((Unk_DB0E2BAB *)var_r8)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x10;
        temp_r0_2 = ((Unk_DB0E2BAB *)var_r10_2)->unk0x14;
        var_r10_2 += 0x18;
        ((Unk_DB0E2BAB *)var_r8)->unk0x14 = temp_r0_2;
        var_r8 += 0x18;
    } while (var_r7 != 0);
    ((Unk_DB0E2BAB *)var_r8)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x0;
    d = d + 0x38;
    ((Unk_DB0E2BAB *)var_r8)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r10_2)->unk0x4;
    temp_r30 = strlen(s) + 0x4459;
    len = strlen(s) + 1;
    memcpy(d, s, len);
    strlen(s);
    return temp_r30;
}
