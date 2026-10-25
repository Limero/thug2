// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020AF18-0x8020AFFC (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF398[];
extern s32 Script_GetInteger(s32, s32);
extern s32 fn_800145AC(void);
f32 fn_8020AF18(void *arg0) {
    u32 phantom[2];
    register char *pg __asm__("r10");
    f64 fm;
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

    __asm__("" : : "m"(phantom[0]));
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
            if (*(s32 *)(b2 + off) == QB_TRIANGLE) {
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
    __asm__ volatile("xoris 0,%2,0x8000\n\tstw 0,%5\n\tlis 11,%3\n\tlis %0,%4@ha\n\tstw 11,%6\n\tlfd %1,%4@l(%0)"
        : "=&r"(pg), "=&f"(fm)
        : "r"(var_r26), "n"(0x4330), "s"(lbl_802AF398), "m"(conv.w.lo), "m"(conv.w.hi)
        : "r0", "r11");
    return (f32)(conv.d - fm);
}
