// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A014-0x8011A0A0 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct N_11A014 {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    struct N_11A014 *unk0x10;
} N_11A014;

extern s32 lbl_80302C40;
void fn_80119F10(void *arg0, N_11A014 *arg1, s32 arg2);

void fn_8011A014(void *arg0, s32 arg1, s32 arg2)
{
    N_11A014 *n = *(N_11A014 **)&lbl_80302C40;

    while (n != 0) {
        N_11A014 *cur = n;
        n = cur->unk0x10;
        if (cur->unk0xC == arg1 && (arg2 == 0 || cur->unk0x4 == arg2)) {
            fn_80119F10(arg0, cur, 1);
        }
    }
}
