// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80228568-0x80228720 (440B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EC0;
extern s32 fn_8013E364(s32, Unk_C7387A53 *);
extern s32 fn_8021B6C8(Unk_C7387A53 *);
extern s32 fn_80219D34(void *);
extern s32 fn_8021B574(void *);
extern s32 fn_802198F4(void *);
extern s32 fn_8013F764(s32);
extern s32 fn_80219724(void *);
extern s32 fn_802196B0(void *);
extern s32 fn_80198F7C(s32);
extern s32 fn_80220484(Unk_C7387A53 *);
extern void *fn_80219F9C(void *);

s32 fn_80228568(Unk_9994C3F5 *arg0, s32 *arg1, void *Q_arg2, s32 Q_arg3, s32 Q_arg4, s32 Q_arg5) {
    register void *pp_arg2 __asm__("r27");
    register s32 pp_arg4 __asm__("r24");
    register s32  pp_arg3 __asm__("r26");
    register s32  pp_arg5 __asm__("r25");
    s32 code;
    s32 b;
    s32 t;
    s32 u;
    void *p;
    register s32 rv __asm__("r3");

    pp_arg2 = Q_arg2;
    pp_arg4 = Q_arg4;
    pp_arg5 = Q_arg5;
    pp_arg3 = Q_arg3;
    if (fn_8013E364(arg0->unk0x8, pp_arg3) != 0) {
        code = 4;
        goto store;
    }
    b = *((s8 *)&((Unk_A8B25094 *)pp_arg2)->unk0x4);
    if (b != 0) {
        if (fn_8021B6C8(arg0) >= fn_80219D34(arg0)) {
            code = 5;
            goto store;
        }
        goto c_check;
    }
    if (fn_8021B574(arg0) >= fn_802198F4(arg0)) {
        *arg1 = b;
        __asm__ __volatile__("");
        return 0;
    }
c_check:
    if ((pp_arg5 != 0) && (*(s32 *)pp_arg2 != 0x4000B)) {
        code = 2;
        goto store;
    }
    if (fn_8013F764(pp_arg3) != 0) {
        t = fn_80219724(arg0);
        u = fn_802196B0(arg0);
        if (u == 2) {
            if (((Unk_A8B25094 *)pp_arg2)->unk0x11 > t) {
                goto d_check;
            }
            code = 6;
            goto store;
        }
        if (u != 1) {
            goto d_check;
        }
        if (((Unk_A8B25094 *)pp_arg2)->unk0x11 >= t) {
            code = 7;
            goto store;
        }
    }
d_check:
    if (((*((u32 *)&((Unk_A8B25094 *)pp_arg2)->unk0x4) & QB_UNKNOWN_0xFFFF0000) == 0) &&
        (fn_80198F7C(lbl_80305EC0) != QB_NETLOBBY) &&
        (fn_80220484(arg0) == 0)) {
        code = 3;
        goto store;
    }
    p = NULL;
    if (pp_arg4 == 0) {
        goto ret1;
    }
    p = fn_80219F9C(arg0);
    if (*(u8 *)p == 0) {
        goto ret1;
    }
    if (strcmp(p, (char *)pp_arg2 + 6) == 0) {
        goto ret1;
    }
    code = 1;
store:
    __asm__ volatile("li %0,0" : "=r"(rv));
    *arg1 = code;
    return rv;
ret1:
    return 1;
}
