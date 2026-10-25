// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042C9C-0x80042D44 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
extern u8 lbl_802924C4;
u32 strlen(const char *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void fn_800427AC(s32, char *);
bool fn_80042C9C(void *arg0, s32 arg1) {
    char sp8[0x60];
    s32 temp_r3;
    s32 var_r30;
    s32 temp_r4;

    temp_r4 = *(s32 *)((char *)arg0 + 0x190);
    var_r30 = 0;
    if (temp_r4 != 0) {
        var_r30 = strlen((const char *)temp_r4);
    }
    temp_r3 = var_r30 + strlen((const char *)arg1);
    if ((temp_r3 + 1) <= 0x5F) {
        if (temp_r3 > 0) {
            sp8[0] = lbl_802924C4;
            if (*(s32 *)((char *)arg0 + 0x190) != 0) {
                strcpy(sp8, (const char *)*(s32 *)((char *)arg0 + 0x190));
            }
            strcat(sp8, (const char *)arg1);
            fn_800427AC(arg0, sp8);
            return true;
        }
    }
    return false;
}
