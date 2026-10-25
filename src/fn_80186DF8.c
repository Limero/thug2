// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186DF8-0x80186EF0 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80305EAC[];

s32 fn_801745B4(s32);
s32 fn_801403CC(void *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_80185170(s32, s32, s32);

void fn_80186DF8(s32 arg0) {
    s32 buf[514];
    s32 *src;
    s32 *var_r9;
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r29;
    register s32 *temp_r30 __asm__("r30");
    s32 var_r11;
    s32 count;
    register s32 a0 __asm__("r28");

    temp_r29 = *(s32 *)((char *)fn_801403CC((s32)(temp_r30 = (s32 *)fn_801745B4(*(s32 *)&lbl_80305EAC))) + 0x24);
    a0 = arg0;
    src = (s32 *)((char *)GetChecksum_3((s32)temp_r30, QB_TRICK) + 0x1404);
    var_r9 = buf;
    var_r11 = 0x7F8;
    do {
        var_r11 -= 0x18;
        ((Unk_DB0E2BAB *)var_r9)->unk0x0 = ((Unk_DB0E2BAB *)src)->unk0x0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x4 = ((Unk_DB0E2BAB *)src)->unk0x4;
        ((Unk_DB0E2BAB *)var_r9)->unk0x8 = ((Unk_DB0E2BAB *)src)->unk0x8;
        ((Unk_DB0E2BAB *)var_r9)->unk0xC = ((Unk_DB0E2BAB *)src)->unk0xC;
        ((Unk_DB0E2BAB *)var_r9)->unk0x10 = ((Unk_DB0E2BAB *)src)->unk0x10;
        temp_r0 = ((Unk_DB0E2BAB *)src)->unk0x14;
        src += 6;
        ((Unk_DB0E2BAB *)var_r9)->unk0x14 = temp_r0;
        var_r9 += 6;
    } while (var_r11 != 0);
    ((Unk_DB0E2BAB *)var_r9)->unk0x0 = ((Unk_DB0E2BAB *)src)->unk0x0;
    ((Unk_DB0E2BAB *)var_r9)->unk0x4 = ((Unk_DB0E2BAB *)src)->unk0x4;
    ((Unk_DB0E2BAB *)var_r9)->unk0x8 = ((Unk_DB0E2BAB *)src)->unk0x8;
    ((Unk_DB0E2BAB *)var_r9)->unk0xC = ((Unk_DB0E2BAB *)src)->unk0xC;
    count = buf[513];
    if (count > 0x200) {
        count = 0x200;
    }
    if (count > 0) {
        s32 i = count;
        temp_r30 = &buf[1];
        do {
            temp_r4 = *temp_r30;
            temp_r30 += 1;
            fn_80185170(a0, temp_r4, temp_r29);
            i -= 1;
        } while (i != 0);
    }
}
