// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020ADE4-0x8020AF18 (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF388[];
extern char lbl_802AF390[];
extern char lbl_802AF394[];
extern s32 Script_GetInteger(s32, s32);
extern f32 fn_8012570C(s32, s32);
extern s32 fn_800145AC(void);
f32 fn_8020ADE4(void *arg0) {
    volatile double _dummy;
    volatile double _dummy2;
    register char *pg __asm__("r10");
    register f32 var_f31 __asm__("fr31");
    register f32 fv __asm__("fr1");
    register f32 temp_f1;
    register s32 var_r26 __asm__("r26");
    register s32 var_r27 __asm__("r27");
    register s32 var_r29 __asm__("r29");
    register s32 lim __asm__("r25");
    register s32 off __asm__("r31");
    register s32 t __asm__("r30");
    register void *arg_home __asm__("r28");
    union {
        struct {
            u32 hi;
            u32 lo;
        } w;
        f64 d;
    } conv;

    arg_home = arg0;
    var_r26 = 0;
    var_r27 = 0;
    {
        s32 temp_lim;

        temp_lim = Script_GetInteger(QB_BASHPERIOD, 1);
        __asm__ volatile("" : "+r"(temp_lim));
        var_r29 = ((Unk_90685748 *)arg_home)->unk0x99E;
        __asm__ volatile("mr %0,%1" : "=r"(lim) : "r"(temp_lim));
    }
    goto L_head;
L_check:
    {
        register char *b1 __asm__("r11");
        b1 = (char *)arg_home + 0x40;
        if ((u32)(*(s32 *)(b1 + off) - 1) <= 1U) {
            register char *b2 __asm__("r9");
            b2 = (char *)arg_home + 0x44;
            if (*(s32 *)(b2 + off) != QB_TRIANGLE) {
                register char *b3 __asm__("r9");
                b3 = (char *)arg_home + 0x50;
                *(s32 *)(b3 + off) = -1;
                var_r26 += 1;
            }
        }
    }
    var_r29 -= 1;
    if (var_r29 < 0) {
        var_r29 += 0x64;
    }
    var_r27 += 1;
L_head:
    if (var_r27 < (s32)((Unk_90685748 *)arg_home)->unk0x99C) {
        register char *b4 __asm__("r9");
        b4 = (char *)arg_home + 0x3C;
        off = var_r29 * 0x18;
        t = *(s32 *)(b4 + off);
        if ((u32)(fn_800145AC() - t) < (u32)lim) {
            goto L_check;
        }
    }
    fv = fn_8012570C(QB_BASHSPEEDUPFACTOR, 1);
    __asm__ volatile(
        "xoris 0,26,0x8000\n\t"
        "stw 0,%4\n\t"
        "lis 11,0x4330\n\t"
        "lis %1,%5@ha\n\t"
        "lis 3,-0x2db6\n\t"
        "stw 11,%6\n\t"
        "ori 3,3,0xbfa3\n\t"
        "lfd 13,%5@l(%1)\n\t"
        "li 4,1\n\t"
        "lfd 0,%7\n\t"
        "fsub 0,0,13\n\t"
        "frsp 0,0\n\t"
        "fmuls 31,0,1\n\t"
        "bl fn_8012570C"
        : "+&f"(fv), "=&r"(pg), "=&f"(var_f31)
        : "r"(var_r26), "m"(conv.w.lo), "s"(lbl_802AF388),
          "m"(conv.w.hi), "m"(conv.d)
        : "r0", "r3", "r4", "r11", "lr", "fr0", "fr13");
    temp_f1 = fv / *(f32 *)lbl_802AF390;
    if (var_f31 > temp_f1) {
        var_f31 = temp_f1;
    }
    return var_f31 + *(f32 *)lbl_802AF394;
}
