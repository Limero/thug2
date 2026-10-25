// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5F38-0x800A6048 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
s32 fn_8013152C(s32);
void fn_8012EFCC(CScript *, s32);
void fn_800A5F38(Unk_727B8CF2 *arg0, Unk_FFAD6788 *arg1, s32 arg2) {
    char *var_r30;
    char *bp;
    char *b;
    char *bA;
    char *bB;
    char *bA2;
    char *bB2;
    char *bC;
    register char *pp __asm__("r30");
    s32 temp_r0;
    s32 a;
    s32 iq2;
    s32 a2;
    s32 var_r29;
    s32 var_r31;
    CScript *temp_r11;

    var_r29 = -1;
    var_r31 = 0;
    if ((s32) arg0->unk0xB03C == 0) {
        var_r29 = 0;
    } else {
loop_2:
        var_r31 += 1;
        if (var_r31 <= 0x27) {
            bp = (char *)arg0 + 0xB03C;
            if (*(s32 *)(bp + var_r31 * 0xC) == 0) {
                var_r29 = var_r31;
            } else {
                goto loop_2;
            }
        }
    }
    if (var_r29 < 0) {
        pp = (char *)arg0 + 0xB038;
        var_r30 = pp;
        var_r31 = 0;
        for (; var_r31 <= 0x27; var_r30 += 0xC, var_r31++) {
            if (fn_8013152C(*(s32 *)var_r30) == 0) {
                var_r29 = var_r31;
                break;
            }
        }
    }
    if (var_r29 >= 0) {
        temp_r0 = var_r29 * 0xC;
        a = (s32)arg0 + 0x10000;
        b = (char *)(a - 0x4FC8);
        *(s32 *)(b + temp_r0) = arg1->unk0xB0;
        a2 = a;

        iq2 = temp_r0;
        temp_r11 = (CScript *)(s32)arg1->unk0xBC;
        if (temp_r11 != NULL) {
            bA = (char *)(a2 - 0x4FC0);
            *(s32 *)(bA + iq2) = temp_r11->unk0x18;
        } else {
            bB = (char *)(a2 - 0x4FC0);
            *(s32 *)(bB + iq2) = temp_r11;
        }
        bC = (char *)(a2 - 0x4FC4);
        *(s32 *)(bC + iq2) = arg2;
        fn_8012EFCC((CScript *)arg1, 0);
    }
}
