// WIP DRAFT — PARKED at 25.40% (94/126 words differ), object SIZE-EXACT 504 B.
// family=m2c range=0x800EBA28-0x800EBC20 size=504B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ------------------------------------------------------------------
// WHY PARKED (2026-10-04 session; measured with want_got.py)
// ------------------------------------------------------------------
// Official verdict: DIFF 25.40% (test_wip_drafts.py --addr 0x800EBA28, which
// needs >50% for NEAR). Object is the EXACT 504 B / 126 words, the frame is
// exact (stwu -0x1b8, stfd f31 0x1b0, stmw r24 0x190, stw r0 0x1bc), the
// epilogue is exact, all 11 call sites are in retail's blocks, every frame
// offset is retail's, the loop shape and the four psq pair-copy store orders
// are byte-identical. The residual is the usual M5.0o/M5.0r class:
// (a) BLOCK ORDER of the loop's error path — retail lays it out
//     [body][fail][good][return][continue]; ngccc picks
//     [body][good][continue][return][fail] (moves ~20 words, ~16 pts);
// (b) GPR COLOURING — 3 of the 8 callee-saved registers land on retail's
//     number (r24=&s2, r25=&s1, r26=dst); the remaining five are permuted
//     (ngccc [&s1.head, i, src, &s2.head, r] vs retail
//      [i, &s1.head, &s2.head, r, src]) and one extra `mr r9,src` copy;
// (c) a handful of intra-block schedule positions (psq_l/psq_st interleave,
//     f10 vs f13 lane-temp colouring).
// Measured negative results (all size-exact, none beat 25.40%):
//   flags: -fno-schedule-insns2 is load-bearing (22.2% without), and
//     -fno-rerun-cse-after-loop too; -fno-gcse/-fno-expensive-optimizations
//     /-fno-thread-jumps/-fno-delayed-branch/-fno-caller-saves/
//     -fno-sched-interblock/-fno-strength-reduce are all neutral or worse.
//   dropping the `src`/`dst`/`p1`/`h1`/`h2` pointer locals: 0-12% (they are
//     what forces the 8-register save and the 504 B length);
//   `ret` as a separate variable for the fn_80108104 result: 24.0%/500 B
//     (retail keeps it in a second callee-saved GPR, but that costs the
//     object a word);
//   nested `if (r != 0) { if (...) {...} }`, `&&`-chained tests, the
//     `goto`-between-tests form, `break` + exit-after-loop, and `p2` as a
//     variable for &s2: all 15-25%, none better.
//   docs/parkings/06-paired-single-ops.md (M5.0o/M5.0r) is the class ref;
//   this is NOT an emission wall — every opcode here is emittable.
//
// ------------------------------------------------------------------
// SEMANTIC MODEL (this part IS solved; reuse it on the sibling at 0x800EBC20)
// ------------------------------------------------------------------
// Two 0xC0-byte node structs on the frame: `s1` at r1+0x08, `s2` at r1+0xc8.
// Layout (deduced from fn_8010794C/fn_80107B20/fn_801080D4 and every field
// touched here): a doubly-linked-list HEAD POINTER at +0xA8  (== frame 0xb0
// and 0x170 — `Unk_C7387A53.unk0xA8`, the only field those callees use),
// four __ps_t pairs at +0x00..+0x1F, an f32 accumulator at +0x04 and another
// at +0x14 (they OVERLAP the pairs' upper words, hence the Pair union), and a
// callee-written vec4 at +0x88/+0x90 that is copied out on success.
// arg0 (r3) is DEAD. arg1 = source `__ps_t *`, arg2 = destination `__ps_t *`.
// 0x8029ACE8 / 0x8029ACEC are added to the two accumulators before the loop;
// 0x8029ACF0 is added to s2's +0x14 accumulator per good iteration and
// subtracted from s1's +0x04 one on every loop-continuation. The loop runs at
// most 9 times; the return value is fn_80108104(&s1) (== s1->head).
// The three list-teardown sites (loop-exhausted / error / success-return)
// share the `s1->head` teardown by tail-merging in retail; `&s1.head` and
// `&s2.head` are held in callee-saved GPRs and passed as RemoveRefLink's
// 2nd argument, while the load/store of the head itself is r1-relative.
#include "types.h"
#include "structs.h"
// FLAG: -fno-schedule-insns2
// FLAG: -fno-rerun-cse-after-loop
// extra_cflags: -mps-float
extern f32 lbl_8029ACE8;
extern f32 lbl_8029ACEC;
extern f32 lbl_8029ACF0;
typedef union {
    __ps_t p;
    struct { f32 lo, hi; } f;
} Pair;
typedef struct {
    Pair v[4];
    u8 pad88[0x68];
    Pair out[2];
    u8 pad98[0x10];
    CStruct *head;
    u8 padAC[0x14];
} Node;
void fn_8010794C(Node *);
CStruct *fn_80107B20(Node *, s32, s32);
CStruct *fn_801080D4(Node *);
CStruct *fn_80108104(Node *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
CStruct *fn_800EBA28(void *arg0, __ps_t *arg1, __ps_t *arg2) {
    Node s1;
    Node s2;
    s32 i;
    CStruct *r;
    CStruct **h1 = &s1.head;
    CStruct **h2 = &s2.head;
    Node *p1 = &s1;
    f32 c3;
    __ps_t *src = arg1;
    __ps_t *dst = arg2;

    fn_8010794C(&s1);
    s1.v[0].p = src[0];
    s1.v[2].p = src[0];
    s1.v[3].p = src[1];
    s1.v[1].p = src[1];
    s1.v[0].f.hi += lbl_8029ACE8;
    s1.v[2].f.hi += lbl_8029ACEC;
    fn_8010794C(&s2);

    i = 0;
    do {
        i++;
        if (i == 10) {
            if (s2.head != 0) {
                CObject_RemoveRefLink(s2.head, h2);
                s2.head = 0;
            }
            r = 0;
            if (s1.head != 0) {
                CObject_RemoveRefLink(s1.head, h1);
                s1.head = r;
            }
            return 0;
        }
        r = fn_80107B20(&s1, 1, 0);
        if (r == 0)
            goto fail;
        r = fn_801080D4(&s1);
        if (r == 0)
            goto fail;
        c3 = lbl_8029ACF0;
        s2.v[2].p = s1.out[0].p;
        s2.v[0].p = src[0];
        s2.v[3].p = s1.out[1].p;
        s2.v[1].p = src[1];
        s2.v[2].f.hi += c3;
        r = fn_80107B20(&s2, 1, 0);
        if (r != 0) {
            s1.v[0].p = s1.out[0].p;
            s1.v[1].p = s1.out[1].p;
            s1.v[0].f.hi -= c3;
            continue;
        }
        dst[1] = s1.out[1].p;
        dst[0] = s1.out[0].p;
        r = fn_80108104(p1);
        if (s2.head != 0) {
            CObject_RemoveRefLink(s2.head, h2);
            s2.head = r;
        }
        if (s1.head != 0) {
            CObject_RemoveRefLink(s1.head, h1);
            s1.head = r;
        }
        return r;
    fail:
        if (s2.head != 0) {
            CObject_RemoveRefLink(s2.head, h2);
            s2.head = r;
        }
        if (s1.head != 0) {
            CObject_RemoveRefLink(s1.head, h1);
            s1.head = r;
        }
        return 0;
    } while (1);
}
