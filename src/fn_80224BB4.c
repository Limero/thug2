// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224BB4-0x80224CE8 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A8030[];
s32 NextNewPlayerInfo(s32 arg0);
void fn_8022A510(void * arg0, s32 arg1);
s32 fn_8021D578(s32 arg0, CStruct * arg1);
s32 fn_8021D5AC(void * arg0, CStruct * arg1);
s32 fn_8021D358(s32 arg0, s32 arg1);
bool fn_80224BB4(Unk_DB0E2BAB *arg0) {
    s32 sp8[4];
    register s32 *t __asm__("r11");
    s32 *o;
    s32 temp_r3;
    s32 temp_r31;
    Unk_A1F83658 *var_r3;
    s32 a30;
    register s32 a3 __asm__("r3");

    temp_r31 = arg0->unk0x18;
    a30 = arg0->unk0x0;
    temp_r3 = NextNewPlayerInfo(temp_r31);
    if (temp_r3 != 0) {
        fn_8022A510(temp_r3, 0);
    } else {
        t = sp8;
        t[1] = temp_r3;
        t[2] = (s32)lbl_802A8030;
        a3 = temp_r31;
        __asm__ __volatile__("" : "+r"(a3));
        o = t;
        var_r3 = fn_8021D578(a3, t);
        for (; var_r3 != 0; var_r3 = fn_8021D5AC(temp_r31, sp8)) {
            if (*((u32 *)&var_r3->unk0x20) & 0x80) {
                *((u32 *)&var_r3->unk0x20) &= QB_UNKNOWN_0xFFFFFF7F;
                break;
            }
        }
        o[2] = (s32)lbl_802A8030;
    }
    temp_r3 = fn_8021D358(temp_r31, (u16)(s8)*(u8 *)a30);
    if (temp_r3 != 0) {
        fn_8022A510(temp_r3, 1);
    } else {
        t = sp8;
        t[1] = temp_r3;
        t[2] = (s32)lbl_802A8030;
        a3 = temp_r31;
        __asm__ __volatile__("" : "+r"(a3));
        o = t;
        var_r3 = fn_8021D578(a3, t);
        for (; var_r3 != 0; var_r3 = fn_8021D5AC(temp_r31, sp8)) {
            if (*((u8 *)&var_r3->unk0x11) == *(u8 *)a30) {
                *((u32 *)&var_r3->unk0x20) |= 0x80;
                break;
            }
        }
        o[2] = (s32)lbl_802A8030;
    }
    return true;
}
