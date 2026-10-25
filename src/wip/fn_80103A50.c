// WIP DRAFT (non-matching) — best body so far
// family=m2c range=0x80103A50-0x80103BC4 size=372B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// REWRITE 2026-10-20 v10-v12, from CLEAN full-diffs (private LEAF_TMPDIR;
// earlier 52.5% was a shared-/tmp/leaf race phantom — always export a
// private LEAF_TMPDIR when scoring with ps_diff.py, which lacks want_got's
// per-run mkdtemp). Semantic fixes vs v9 (all verified in want): alloc is
// fn_80009A44(0x40); buf allocs are fn_80009A78 (x2); copies are raw
// fn_8026AE28 (x2) called with NO prototype — want's crclr cr1eq before
// both bls is the implicit-decl marker (recipes 16/21), and got now emits
// the same crclr+mulli+bl tail ingredients (phase-shifted, see below);
// unk30 IS stored (LAST, per want 00CC) — v9 read it uninit; count/buf are
// re-read at use sites (want reloads, never reuses); head 0000-003C is now
// mostly OK and the r30/r31 homes flipped to want's side on their own.
// TRUE score v12: 17.8% (16/90, got 360B vs want 372B) — lower than v9's
// 22.5% only via scheduling luck (v9's wrong callees can never link-match).
// PARKED: the 0038-009C load cluster is a scheduling wall. Want sinks the
// count*3 chain (slwi@007C/add@0084, split around the unk6 store) and keeps
// an `mr r3,r6` count-copy idle from 0054; three reasoned variants all fail
// identically — ngccc hoists any pure count-ALU chain to the earliest slot:
// (a) c3=cnt*3 late, (b) two-variable cnt2=cnt copy early + late multiply,
// (c) c2=cnt*2 split around the unk6 store (v12: still adjacent-early).
// The mr proves TWO live count values, but no C spelling reproduces both
// the early copy AND the late sunk multiply — placement is a scheduler
// priority property, not a source-order property. Register pin on nw was
// also tried: frame collapse to 16.9%, reverted (pins on call-result webs
// are harmful here). Next lever, if any: find what C form parks a GPR copy
// for 28 insns; until then do NOT re-permute temps — the tail already has
// every ingredient in order (mulli/crclr/bl/reloads, shifted +1 word) and
// should snap into place once the cluster does.
#include "types.h"
typedef struct Rec103A50 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u16 count;
    u8 flag;
    u8 unkB;
    void *buf;
    __ps_t p10;
    __ps_t p18;
    __ps_t p20;
    __ps_t p28;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Rec103A50;
void *fn_80009A44(s32 size);
void *fn_80009A78(s32 size);
s32 fn_80102B1C(s32 arg0, s32 arg1);
void *fn_80103A50(Rec103A50 *arg0, s32 arg1, s32 arg2) {
    Rec103A50 *nw;
    __ps_t t10, t18, t20, t28;
    __ps_t *s, *d;
    s32 t0, t4, t6, cnt, c2, c3, t30, t34, t38, t3c;
    void *tbuf;
    u8 tB, tF;
    if (arg2 != 0 && arg0->unk6 == 0) {
        return 0;
    }
    nw = fn_80009A44(0x40);
    t10 = arg0->p10;
    cnt = arg0->count;
    s = (__ps_t *)((char *)arg0 + 0x10);
    d = (__ps_t *)((char *)nw + 0x10);
    tF = arg0->flag;
    t0 = arg0->unk0;
    t4 = arg0->unk4;
    t6 = arg0->unk6;
    nw->p10 = t10;
    t18 = arg0->p18;
    tB = arg0->unkB;
    nw->unk0 = t0;
    nw->unk4 = t4;
    c2 = cnt * 2;
    nw->unk6 = t6;
    c3 = c2 + cnt;
    nw->unkB = tB;
    nw->count = (u16)cnt;
    nw->flag = tF;
    nw->p18 = t18;
    t20 = s[2];
    d[2] = t20;
    t30 = arg0->unk30;
    t34 = arg0->unk34;
    t28 = s[3];
    d[3] = t28;
    t38 = arg0->unk38;
    t3c = arg0->unk3C;
    tbuf = arg0->buf;
    nw->unk34 = t34;
    nw->unk38 = t38;
    nw->unk3C = t3c;
    nw->buf = tbuf;
    nw->unk30 = t30;
    if (tF != 0) {
        nw->buf = fn_80009A78(nw->count * 8);
    } else {
        nw->buf = fn_80009A78(nw->count * 10);
    }
    if (nw->unk30 == 0) {
        return 0;
    }
    if (nw->buf == 0) {
        return 0;
    }
    fn_8026AE28(nw->buf, arg0->buf, arg0->count * 10);
    if (arg0->unk38 != 0) {
        nw->unk38 = (s32)fn_80009A78(c3);
        fn_8026AE28((void *)nw->unk38, (void *)arg0->unk38, c3);
    }
    nw->unk34 = fn_80102B1C(arg0->unk34, arg1);
    return nw;
}
