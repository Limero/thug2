// WIP DRAFT (non-matching) — rebuilt from disasm 2026-08-25
// family=m2c range=0x80244E48-0x80245094 size=588B
// extra_cflags: -mps-float
// FLAG: -fno-rerun-cse-after-loop
// PARKED ~44% aligned (psq-aware difflib; masked score understates due to
// frame cascade). Semantically faithful rebuild; resume notes:
// - m2c's offsets were WRONG. True layout: bec_ret@r1+0x10, lbl value@r1+0x14,
//   out struct@0x18, rc[4]@0x28, cvt union@0x50/54.
// - want keeps TWO base-pointer webs born in prologue (&fr=r1+8 homed r24 with
//   first store through birth scratch r11; &fr+0xC homed r23, store through
//   scratch r10 AFTER the BEC call). No C shape found that reproduces
//   scratch-birth + home-copy without asm; asm addi/mr wedges DO create the
//   webs (current form) but colors/interleave still differ.
// - want folds const loads as symbol@ha/l displacements (lfd f31,0x1350(r9));
//   constants sit INSIDE lbl_802C0F0F (no labels): dbl@+0x441, flt@+0x449,
//   flt@+0x44D. Packed-struct member access was probed: GCC computes base in a
//   reg (addi) and loads 0(rX) — does NOT fold packed member offsets.
// - fn_801FB248 is chained-arg (r3 = fn_801FC0E0's return); fn_80233428 takes
//   chained arg0; fn_80230BEC(0) 1-arg; fn_802442A8 is 5-ARG (m2c dropped one).
// - frame: want 0x90/stmw r23@0x5c; got 0xa0/stmw r24@0x70 (+0x10 hidden temps,
//   +1 saved reg). Killing those two gaps should cascade most body words into
//   alignment (body structure otherwise matches: walk/sum/fail-shared/act/
//   render-loop shapes all present).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8029FBE8[];
extern char lbl_802C0F0F[];
extern char lbl_803A30E0[];
extern s32 fn_80230BEC(s32 mode);
extern s32 fn_80233428(s32 a, s32 w, s32 h);
extern s32 fn_8024420C(Unk_7044F700 * list, s32 cx, s32 cy, CStruct * arg1);
extern s32 fn_801F9890(Unk_C7387A53 * node);
extern s32 fn_801FC0E0(void);
extern s32 fn_801FBE18(void);
extern void fn_80230C54(void);
extern void fn_802442A8(Unk_6E48A312 * list, s32 cx, s32 val, s32 cy, Unk_C7387A53 * arg1);
extern void fn_80245318(void *out, Unk_F96D0DC8 * arg0);
extern char *fn_80233764(s32 a);
extern void *fn_801FB248(Unk_C7387A53 * a);
extern void fn_801F9DC8(Unk_C7387A53 * obj, Unk_C7387A53 * node);
extern void fn_801F9E38(Unk_C7387A53 * obj, void *a2, void *a3, f32 v);
extern void fn_801F96B4(Unk_C7387A53 * obj, s32 a2, s32 a3, f32 v);
extern void fn_801F9734(Unk_C7387A53 * obj, s32 a2, s32 a3, f32 v);

struct e48_fr {
    s32 _08;
    s32 _0C;
    s32 bec_ret;
    s32 lbl;
    char out[16];
    f32 rc[4];
    char p38[24];
    union { u32 w[2]; volatile f64 d; } cvt;
    char p58[4];
};

s32 fn_80244E48(Unk_09BB4394 *arg0, CStruct *arg1) {
    struct e48_fr fr;
    CScript *list;
    CStruct *node;
    void *obj;
    u32 cx;
    u32 cy;
    s32 sum;
    s32 *plbl;
    s32 *pbec;
    s32 *plbl_t;
    s32 *pbec_t;

    {
        s32 lblv = (s32)lbl_8029FBE8;
        s32 bec;

        __asm__ volatile("addi %0,1,8" : "=r"(plbl_t));
        __asm__ volatile("mr %0, %1" : "=r"(plbl) : "r"(plbl_t));
        plbl_t[3] = lblv;
        bec = fn_80230BEC(0);
        __asm__ volatile("addi %0,1,0xc" : "=r"(pbec_t));
        __asm__ volatile("mr %0, %1" : "=r"(pbec) : "r"(pbec_t));
        pbec_t[1] = bec;
        if (fn_80233428(bec,
                        arg0->unk0x9 - arg0->unk0x7 + 1,
                        arg0->unk0xA - arg0->unk0x8 + 1) == 0) {
            plbl[3] = lblv;
            goto failcall;
        }
    }
    list = arg0->unk0xC;
    cx = ((u32)arg0->unk0x7 + (u32)arg0->unk0x9) >> 1;
    cy = ((u32)arg0->unk0x8 + (u32)arg0->unk0xA) >> 1;
    while (list != NULL) {
        if (fn_8024420C(list, cx, cy, arg1) == 0) {
            goto failfull;
        }
        list = *((void * *)&list->unk0x18);
    }
    sum = 0;
    for (node = arg0->unk0x10; node != NULL; node = *((void * *)&node->unk0x4)) {
        sum += fn_801F9890(node);
    }
    fn_801FC0E0();
    if (sum <= fn_801FBE18()) {
        goto ok;
    }
failfull:
    fr.lbl = (s32)lbl_8029FBE8;
failcall:
    fn_80230C54();
    return 0;
ok:
    {
        f64 dblc = *(f64 *)(lbl_802C0F0F + 0x441);
        f32 fltc = *(f32 *)(lbl_802C0F0F + 0x449);
        char *rcbase;
        char *pout = &fr.out[0];

        list = arg0->unk0xC;
        while (list != NULL) {
            fn_802442A8(list, cx, arg1->unk0x68, cy, arg1);
            list = *((void * *)&list->unk0x18);
        }
        fn_80245318(pout, arg0);
        rcbase = fn_80233764(pbec[1]);
        *(__ps_t *)&fr.rc[0] = *(__ps_t *)&rcbase[0];
        node = arg0->unk0x10;
        *(__ps_t *)&fr.rc[2] = *(__ps_t *)&rcbase[1];
        if (node != NULL) {
            do {
                obj = fn_801FB248(fn_801FC0E0());
                fn_801F9DC8(obj, node);
                fr.cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
                fr.cvt.w[1] = *((u32 *)&arg1->unk0x3C) ^ 0x80000000;
                fn_801F9E38(obj, pout, &fr.rc[0], (f32)(fr.cvt.d - dblc) * fltc);
                fn_801F96B4(obj, (s32)lbl_803A30E0, (s32)lbl_803A30E0, *(f32 *)(lbl_802C0F0F + 0x44D));
                fn_801F9734(obj, (s32)lbl_803A30E0, (s32)lbl_803A30E0, *(f32 *)(lbl_802C0F0F + 0x44D));
                node = *((void * *)&node->unk0x4);
            } while (node != NULL);
        }
    }
    fr.lbl = (s32)lbl_8029FBE8;
    fn_80230C54();
    return 1;
}
