// WIP DRAFT (non-matching) — hand-rebuilt from want disasm
// family=m2c range=0x80192854-0x80192AC8 size=628B
// PARKED 2026-09-21: flag sweep exhausted — DEFAULT flags are already the best
// (63.7%); -fno-schedule-insns2 62.4%, -fno-schedule-insns 63.7%,
// -fno-sched-spec -fno-sched-interblock 63.7%, -fno-gcse 13.4%,
// -fno-expensive-optimizations / -fno-thread-jumps / -fno-strength-reduce
// 63.7%.  Residual is the multi-web regalloc of the QB getter/forwarding
// network (doc-15/28 class), not a flag question.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 41.4% while git revision 1d5f3d3e4 scores 63.7%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 15 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
extern s32 lbl_80305EC0;
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
register s32 vb __asm__("r31");
s32 fn_80198F7C(s32);
s32 fn_80199968(void);
s32 fn_8018E24C(void *);
s32 fn_8018CC18(void *);
s32 fn_8021B574(s32);
s32 fn_8021FE28(s32);
s32 fn_8009CF2C(s32);
void *fn_8021D454(s32, void *, s32);
s32 GetChecksum_3(void *, s32);
s32 fn_801EFA84(void);
void fn_801EF978(s32, s32);
void *fn_8021D4E8(s32, void *, s32);
s32 fn_80220484(s32);
s32 fn_80192854(void *arg0) {
    s32 sp8[4];
    s32 var_r26;
    s32 var_r3;
    void *p;
    s32 *pv;
    s32 *psp;
    register s32 a0 __asm__("r29");
    register s32 mgr __asm__("r28");
    s32 lblv;

    var_r26 = 0;
    a0 = arg0;
    vb = (fn_80198F7C(lbl_80305EC0) ^ 0x10F84276) == 0;
    if ((fn_80198F7C(lbl_80305EC0) == 0xFC13B531) || (fn_80198F7C(lbl_80305EC0) == 0x846504FC)) {
        var_r26 = 1;
        if (fn_8018E24C(a0) != 0xD4F04E7F) {
            vb = 1;
        }
    }
    if (fn_80198F7C(lbl_80305EC0) == 0xEC200EAA) {
        if ((fn_80199968() != 0) && (fn_8018CC18(a0) != 0)) {
            vb = 1;
        } else {
            vb = 0;
        }
        return vb;
    }
    if (vb != 0) {
        return (*(s32 *)((char *)a0 + 0x54) > 0) ? 0 : 1;
    }
    mgr = lbl_80305F9C;
    lblv = (s32)lbl_802A83F8;
    pv = &sp8[0];
    pv[1] = vb;
    pv[2] = lblv;
    __asm__("" : "+r"(pv));
    psp = pv;
    if (fn_8021B574(mgr) == 0) {
        psp[2] = lblv;
        return 1;
    }
    if (((*(s32 *)((char *)a0 + 0x70) & 0x80000) != 0) ||
        ((fn_8021FE28(mgr) == 0) && (fn_8009CF2C(mgr) != 0) && (var_r26 == 0))) {
        psp[2] = lblv;
        return 0;
    }
    if (*(s32 *)((char *)a0 + 0x28) == 2) {
        var_r3 = (*(s32 *)((char *)a0 + 0x54) > 0) ? 0 : 1;
    } else if ((fn_8018CC18(a0) != 0) && (*(s32 *)((char *)a0 + 0x54) <= 0)) {
        var_r3 = 1;
    } else {
        p = fn_8021D454(mgr, &sp8[0], 0);
        while (p != NULL) {
            lblv = *(s32 *)((char *)p + 0x18);
            vb = GetChecksum_3((void *)lblv, 0xB1D5A3E1);
            if ((fn_801EFA84() == 0) && (*(s32 *)((char *)lblv + 0x354) == 0) &&
                (*(s32 *)((char *)a0 + 0x28) != 2) && (*(s32 *)((char *)a0 + 0x54) <= 0)) {
                *(s32 *)((char *)a0 + 0x70) |= 0x01000000;
                fn_801EF978(vb, 0);
            }
            p = fn_8021D4E8(mgr, &sp8[0], 0);
        }
        var_r3 = fn_80220484(mgr);
    }
    psp[2] = (s32)lbl_802A83F8;
    return var_r3;
}
