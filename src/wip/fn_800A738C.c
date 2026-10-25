// PARKED 2026-10-03 (b43): DIFF 24.6% (17/69 masked words), got 276B vs want 284B
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 23.9437% -> 25.3521% `volatile` keyword(s) removed from the body
// family=m2c range=0x800A738C-0x800A74A8 size=284B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SCORE: was DIFF 11.3% (m2c draft, plain f32/s32 shell — it had NO PS ops at
// all, so every psq_l/ps_sub/psq_st word was wrong). Now the body is
// instruction-for-instruction identical to the want for the ENTIRE else-branch
// tail (head/cursor update + the two ring stores + the count clamp) and the
// whole PS block; the 24.6% is a positional artefact of the 8-byte length
// shortfall described under RESIDUAL, not merit.
//
// WHAT THE FUNCTION IS (hand-decoded, op-4 words via tools/ps_diff.py dec()):
//   s32 r3 = fn_8009F498(arg0->unk410);          // +0x14,+0x18
//   if (!r3) return r3;
//   arg0->d418 = *(ps*)((char*)r3 + 0x58);        // +0x24,+0x2c  (two psq_l/st)
//   c = arg0->count;                             // +0x28  lwz 0x408
//   arg0->d420 = *(ps*)((char*)r3 + 0x60);        // +0x30,+0x38
//   if (c == 0) {                                // +0x34 cmpwi, +0x3c bne
//       arg0->head    = c;                        // +0x4c  stw 0x40c
//       arg0->ring[0].a = arg0->d418;             // +0x50  psq_st 8(r31)
//       arg0->ring[0].b = arg0->d420;             // +0x5c  psq_st 16(r31)
//       arg0->count  = c + 1;                     // +0x58  stw 0x408
//   } else {
//       i = arg0->head;                           // +0x64  lwz 0x40c
//       zc  = lbl_80298124;                        // psq_l f10 (0.0 pair)
//       a   = ps_sub(d418, ring[i].a);             // +0x94  ps_sub f13,f13,f11
//       b   = ps_sub(d420, ring[i].b);             // +0x9c  ps_sub f0,f0,f12
//       t   = ps_mul(a, a);                        // +0x98  ps_mul f13,f13,f13
//       b   = ps_merge00(b, zc);                   // +0xa0  (zeroes b.ps1)
//       u   = ps_madds0(b, b, t);                  // +0xa4
//       res = ps_sum0(u, u, u);                   // +0xa8  -> volatile slot sp+8
//       if (*(volatile f32*)&res > lbl_80298158) { // +0xb0 lfs 8(r1), 1600.0f
//           nh = i + 1; arg0->head = nh;           // +0xc0,+0xc8,+0xc4,+0xcc
//           if (nh > 0x3F) arg0->head = 0;         // +0xd0,+0xd4
//           arg0->ring[arg0->head] = {d418, d420}; // +0xd8..+0xf0 psq_stu+8
//           if (arg0->count <= 0x3F) arg0->count++; // +0xf4..+0x104
//       }
//   }
//   return r3;
// The ring is 64 x 16B entries at arg0+0x08: ring[i].a = arg0+0x08+16i,
// ring[i].b = arg0+0x10+16i. Both literals are REAL symbols: 0x80298124 is a
// double 0.0 (the ps_merge00 zero donor), 0x80298158 is f32 1600.0f.
//
// KEY LEVERS MEASURED THIS ROUND (all in src/wip/fn_800A738C.c, keep them):
//  * `__builtin_ps_madds0` (NOT `__builtin_ps_madd`) — the want word is
//    0x1000681c (xo5=14). `__builtin_ps_madd` emits 0x...3a (xo5=29). Probed
//    both: they are identical apart from the XO field, and ProDG chose the
//    "s0" form in retail (the merge00 zeroes b.ps1 so madds0 is equivalent).
//  * `__builtin_ps_merge00`'s operand must be its OWN NAMED statement placed
//    EARLY in the block (`zc = lbl_80298124;` right after the head load) — as an
//    inline argument cc1 sinks its psq_l to the bottom of the window and the
//    whole 11-word head re-blocks (same finding as fn_800A9200, recipes/§800A9200).
//  * The two ring reads are DIFFERENT addresses, not one CSE'd value:
//    q[1] = ring[i].a (psq_lu+ f11,8(r11), which ALSO bumps r11) and
//    q[2] = ring[i].b (psq_l f12,8(r11) off the bumped r11).  Writing
//    `q[1]` for both is a semantic bug that also drops a word.
//  * The tail's two ring stores need `volatile __ps_t *p = (__ps_t*)arg0 +
//    2*k + 1; p[0] = ..; p[1] = ..;` — non-volatile gives psq_stx (indexed)
//    + a second base; volatile gives the retail psq_stu+ / psq_st 8 pair.
//    Same `volatile` trick got the retail store FORM; same statement shape got
//    the retail `slwi; add rX,rX,r31` base folding (displacements 8/16 instead
//    of 8/16 off arg0+8+16k).
//  * The scalar read must be `res.flt.hi`, NOT `res.flt.lo`: ps_sum0 lands the
//    sum in ps0 = the LOW word = sp+8, and `lfs f0, 8(r1)` in the want reads
//    sp+8. `flt.lo` gives `lfs fX, 0xc(r1)` and is wrong.
//  * `register s32 c __asm__("r0")`, `register volatile __ps_t *p
//    __asm__("r9")`, `register __ps_t *q __asm__("r11")` — all three are
//    LOAD-BEARING for register assignment (without them GCC swaps r9/r11
//    between the literal page and the ring base, and picks r9 for c).
//  * `__ps_t zc = 0.0;` as a local instead of the lbl ICEs cc1 (silent empty
//    .o) — the merge donor must come from the rodata symbol.
//
// RESIDUAL — object .text 276B vs want 284B (2 words short), so the whole
// body after +0x44 is shifted one word and every scorer number is noise:
//  (A) +0x44/+0x48 want `mr r9,r0 ; addi r9,r9,1` before `stw r0,0x40c`;
//      got `li r9,1`.  This is GCC 2.95 -O2 CONSTANT PROPAGATION of `c == 0`
//      into the branch body: measured 6 different spellings
//      (`c+1`, `o->count+1`, `(u32)c+1`, `o->head+1`, via `s32*pc`, through a
//      `register ... __asm__("r0")` pin) and ALL fold to 1.  Also pinning the
//      result (`register s32 n1 __asm__("r9")`) still folds — only the
//      destination register matches, not the length.  Hoisting `n1 = c + 1`
//      above the branch also defeats the fold but puts `addi` at +0x34, before
//      the cmpwi (wrong slot, same word count).  The want's extra `mr` is a
//      reload copy the retail source forced; no pure-C spelling found.
//  (B) +0xb0/+0xb4 want `lfs f0,8(r1) ; fmr f13,f0` before `fcmpu cr0,f13,f9`;
//      got `lfs f13,8(r1)`.  Probed 3 shapes (named f32, volatile PSU, raw
//      `*(volatile f32*)&res`): all emit a single lfs and compare it directly
//      — no copy.  The retail copy needs a second pseudo for the compare
//      operand (e.g. `scv13 = scv0;`), which would be a pin-forced dead copy.
//  (C) +0x84 want `psq_lu+ f11,8(r11)` (r11 bumped) then +0x90 `psq_l
//      f12,8(r11)`; got `psq_l f12,8(r11)` then `psq_l f11,16(r11)` — same two
//      addresses, no update form, and the f11/f12 roles swapped.  Pinning q to
//      r11 keeps the base register right but suppresses the psq_lu form.
//  (D) `lfs f9, -0x7ea8(r9)` (limit) sits at +0x8c in the want, i.e. right
//      after the second `lis`, before the subs; got sinks it to just before
//      the fcmpu.  Scheduling only.
//  ALL FOUR are worth 8 bytes total.  Fixing (A) alone re-aligns the tail, so
//  that is the highest-value next idea — but I could not find a C spelling for
//  it.  The two obvius dead ends: `__asm__("" : "+r"(c))` as a const-prop
//  barrier (recipe 105) would defeat the fold but still yield ONE word
//  (`addi r9,r0,1`), not the retail two, so it cannot fix the length either.
//
// AUDIT: object .text 276B, no private .rodata, 0 inline asm emitted (3
// register-var attribute pins only), the one `bl` is REL24 to fn_8009F498,
// branch displacements/ADDI16 pairs hand-checked against the want.
#include "types.h"

extern __ps_t lbl_80298124;
extern f32 lbl_80298158;

s32 fn_8009F498(s32);

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

typedef struct {
    __ps_t a;
    __ps_t b;
} ELEM;

typedef struct {
    char pad00[0x08];
    ELEM ring[64];
    s32 count;
    s32 head;
    s32 unk410;
    char pad414[4];
    __ps_t d418;
    __ps_t d420;
} ARG;

s32 fn_800A738C(ARG *arg0) {
    s32 r3 = fn_8009F498(arg0->unk410);
    if (r3 != 0) {
        register s32 c __asm__("r0");
        s32 nh;
        s32 k;
        s32 cnt;
        register __ps_t *p __asm__("r9");
        register __ps_t *q __asm__("r11");
        __ps_t a;
        __ps_t b;
        __ps_t t;
        __ps_t zc;
        __ps_t u;
        PSU res;
        arg0->d418 = *(__ps_t *)((char *)r3 + 0x58);
        c = arg0->count;
        arg0->d420 = *(__ps_t *)((char *)r3 + 0x60);
        if (c == 0) {
            arg0->ring[0].a = arg0->d418;
            arg0->head = c;
            arg0->ring[0].b = arg0->d420;
            arg0->count = c + 1;
        } else {
            s32 i = arg0->head;
            q = (__ps_t *)arg0 + 2 * i;
            zc = lbl_80298124;
            a = __builtin_ps_sub(arg0->d418, q[1]);
            b = __builtin_ps_sub(arg0->d420, q[2]);
            t = __builtin_ps_mul(a, a);
            b = __builtin_ps_merge00(b, zc);
            u = __builtin_ps_madds0(b, b, t);
            res.ps = __builtin_ps_sum0(u, u, u);
            if (res.flt.hi > lbl_80298158) {
                nh = i + 1;
                arg0->head = nh;
                if (nh > 0x3F) {
                    arg0->head = 0;
                }
                k = arg0->head;
                p = (__ps_t *)arg0 + 2 * k + 1;
                p[0] = arg0->d418;
                p[1] = arg0->d420;
                cnt = arg0->count;
                if (cnt <= 0x3F) {
                    arg0->count = cnt + 1;
                }
            }
        }
    }
    return r3;
}
