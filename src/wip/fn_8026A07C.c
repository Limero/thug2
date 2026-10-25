// WIP DRAFT — PARKED (structural rebuild complete; allocator wall)
// family=hand range=0x8026A07C-0x8026AA08 size=2444B
//
// IDENTITY (high confidence): BSD/MSL qsort(void *base, size_t n, size_t es,
// int (*cmp)()) — the Bentley/McIlroy implementation shipped in Metrowerks
// MSL C and vendored by countless games. Retail here is PRODG(GCC)-compiled
// (NOT mwcc like its neighbors): stwu-first prologue, mtlr-before-pop
// epilogue, stmw r17 span, and a `crclr cr1eq` before every comparator blrl
// = the UNPROTOTOTYPED fn-ptr idiom (recipe 21). The m2c draft was a
// statics-DCE husk at 3.4% (§6j-4); this file replaces it with a faithful
// reconstruction from disasm.
//
// ALGORITHM MAP (want, all offsets verified in disasm):
//   0x009C mode select: swaptype = ((base|es)&3) ? 2 : (es==4 ? 0 : 1)
//         r26=base r22=n r29=es r23=cmp r18=swaptype; re-run per tail-loop
//   0x00C4 if n <= 6 -> insertion sort over [a, a+n*es):
//         for pm=a+es .. end: for q=pm; q>a && cmp(q-es,q)>0; q-=es) swap
//         (0x0108 shared swap dispatch: type0 single-lwz pair / type1 word
//         loop count es>>2 via addic./bgt / type2 byte loop count es)
//   0x01C4 quicksort: pm = a+(n/2)*es
//     n>40: NINTHER m1=med3(a,a+d,a+2d) m2=med3(pm-d,pm,pm+d)
//           m3=med3(pn-2d,pn-d,pn), d=(n/8)*es; pm=med3(m1,m2,m3)
//     else pm=med3(a, pm, pn)   [med3 = BSD libkern form]
//   0x04C8 swapone(a, pm): pivot to front (type0 single lwz pair fast path)
//         r20=n*es r21=a+es cached
//   0x0564 partition: pa=pb=a+es pc=pd=a+(n-1)*es
//         while pb<=pc && cmp(pb,a)<=0 { if ==0 {swapped=1; swap(pa,pb);
//               pa+=es} pb+=es }
//         while pb<=pc && cmp(pc,a)>=0 { if ==0 {swapped=1; swap(pc,pd);
//               pd-=es} pc-=es }
//         if pb>pc break; swap(pb,pc); swapped=1; pb+=es; pc-=es;
//         (r19 = swapped flag; mfcr/mtcrf caches the swaptype compare across
//          every blrl — want keeps cr0(cr7) compare results in saved regs:
//          mfcr r25/r27/r22/r24 + slwi 28 + mtcrf 0x80 sites x6)
//   0x07C4 if !swapped -> insertion sort over WHOLE range (same loops as
//         small-n path) and return (0x07CC-0x08B0)
//   0x08B4 vecswap ends: min(pa-a, pb-pa) bytes from a/pb-r;
//         min(pd-pc, pn-pd-es) from pb/pn-r (two copy loops w/ word/byte arms)
//   0x09CC recurse smaller half: if (pb-pa) > es -> bl self (r/a/es/cmp)
//         tail-loop larger: a = pn-(pd-pc); n=(pd-pc)/es; b 0x009C
//   epilogue 0x09F4: lwz r0,0x4c(r1); mtlr; lmw r17,0xc(r1); addi r1,0x48
//
// REGISTER HOMES (want): r26=base r22=n r29=es r23=cmp(never moved, stays in
// arg reg!) r18=swaptype r19=swap_cnt r30/r31/r24/r25/r21/r27/r28 = walker
// webs per phase; 15 callee-saved regs total -> `stmw r17,0xc(r1)` frame
// 0x48.
//
// WHY PARKED (allocator wall — do NOT grind blind):
// - Reconstruction below is semantically faithful (BSD source shape) but
//   ngccc homes only ~4 webs into callee-saved regs (stmw r28, frame 0x18)
//   vs want's 15 (stmw r17, frame 0x48). The cascade starts at the first
//   med3 call: want holds cmp in r23 (arg reg kept live whole function) while
//   ngccc copies it to a different home and rematerializes walkers.
// - Levers NOT yet exhausted (retry hints for next session):
//   1. Declaration/first-appearance order of locals to steer param homes
//      (§76-184) — target order: base->r26 first used, then n->r22, es->r29,
//      cmp->r23. Note want KEEPS cmp in its incoming register r23: try using
//      cmp before anything else and keeping a live use in every block.
//   2. Keep `n` and both vecswap min() computations in named locals so they
//      claim saved slots (want materializes r20=n*es early).
//   3. Full-web pinning scales to big functions when partial pins collapse
//      (§6an-216, 11 pins on fn_8022EA0C) — pin the partition walkers
//      (pa/pb/pc/pd) to want's homes as s32 aliases (§76-178 pointer-pin
//      trap: pin s32, cast at deref).
//   4. Comparator MUST stay unprototyped `int (*cmp)()` old-style so every
//      call site keeps want's `crclr cr1eq` (recipe 21).
//   5. If-conversion polarity: the insertion-sort inner test must stay
//      branchy (`bgt` into the shared swap dispatch) — one shared dispatch
//      block per site is what want shows; do not let GCC fold swaps inline.
// - Best measured state: this body compiles clean under ngccc -O2 -G0,
//   1896B vs 2444B want (~0.3% masked word match — length mismatch makes %
//   meaningless; the value is the structural map above).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 0.5% ([5]rev->0.5%).
#include "types.h"

typedef int (*cmp_t)();

static __inline__ void swapfunc(char *a, char *b, u32 n, s32 swaptype) {
    if (swaptype <= 1) {
        s32 i = (s32)(n >> 2);
        u32 *pi = (u32 *)a;
        u32 *pj = (u32 *)b;
        do {
            u32 t = *pi;
            *pi++ = *pj;
            *pj++ = t;
        } while (--i > 0);
    } else {
        s32 i = (s32)n;
        u8 *pi = (u8 *)a;
        u8 *pj = (u8 *)b;
        do {
            u8 t = *pi;
            *pi++ = *pj;
            *pj++ = t;
        } while (--i > 0);
    }
}

static __inline__ void swapone(char *a, char *b, u32 es, s32 swaptype) {
    if (swaptype == 0) {
        u32 t = *(u32 *)a;
        *(u32 *)a = *(u32 *)b;
        *(u32 *)b = t;
    } else {
        swapfunc(a, b, es, swaptype);
    }
}

static __inline__ char *med3(char *a, char *b, char *c, cmp_t cmp) {
    if (cmp(a, b) < 0) {
        if (cmp(b, c) < 0)
            return b;
        return cmp(a, c) < 0 ? a : c;
    }
    if (cmp(b, c) > 0)
        return b;
    return cmp(a, c) > 0 ? a : c;
}

void fn_8026A07C(void *va, u32 n, u32 es, cmp_t cmp) {
    char *a = (char *)va;
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    s32 r;
    s32 swaptype;
    s32 swap_cnt;

loop:
    if (((u32)a & 3) != 0)
        swaptype = 2;
    else if ((es & 3) != 0)
        swaptype = 2;
    else if (es == 4)
        swaptype = 0;
    else
        swaptype = 1;
    swap_cnt = 0;
    if (n < 7) {
        for (pm = a + es; pm < a + n * es; pm += es)
            for (pl = pm; pl > a && cmp(pl - es, pl) > 0; pl -= es)
                swapfunc(pl, pl - es, es, swaptype);
        return;
    }
    pm = a + (n / 2) * es;
    if (n > 7) {
        pl = a;
        pn = a + (n - 1) * es;
        if (n > 40) {
            u32 d = (n / 8) * es;
            char *m1 = med3(pl, pl + d, pl + 2 * d, cmp);
            char *m2 = med3(pm - d, pm, pm + d, cmp);
            char *m3 = med3(pn - 2 * d, pn - d, pn, cmp);
            pm = med3(m1, m2, m3, cmp);
        } else {
            pm = med3(pl, pm, pn, cmp);
        }
    }
    swapone(a, pm, es, swaptype);
    pa = pb = a + es;
    pc = pd = a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (r = cmp(pb, a)) <= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swapone(pa, pb, es, swaptype);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (r = cmp(pc, a)) >= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swapone(pc, pd, es, swaptype);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc)
            break;
        swapfunc(pb, pc, es, swaptype);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) {
        for (pm = a + es; pm < a + n * es; pm += es)
            for (pl = pm; pl > a && cmp(pl - es, pl) > 0; pl -= es)
                swapfunc(pl, pl - es, es, swaptype);
        return;
    }
    r = (s32)(pa - a) < (s32)(pb - pa) ? (s32)(pa - a) : (s32)(pb - pa);
    pn = a + n * es;
    if (r > 0)
        swapfunc(a, pb - r, r, swaptype);
    r = (s32)(pd - pc) < (s32)(pn - pd - (s32)es) ? (s32)(pd - pc)
                                                  : (s32)(pn - pd - (s32)es);
    if (r > 0)
        swapfunc(pb, pn - r, r, swaptype);
    r = (s32)(pb - pa);
    if (r > (s32)es)
        fn_8026A07C(a, r / es, es, cmp);
    r = (s32)(pd - pc);
    if (r > (s32)es) {
        a = pn - r;
        n = r / es;
        goto loop;
    }
}
