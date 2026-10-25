// PARKED 2026-10-30 r2 base 0% final 15.53% (1056B/1084B, 223/271 words masked,
// object 28B SHORT, frame -0x150 vs want -0x108) — semantic rebuild compiles, not byte-exact.
// RESIDUAL, in order of word cost (want_got.py, masked compare):
//  (1) FRAME +0x48. Want: stwu -0x108, stmw r14,0x90, CR 0x8c, LR 0x10c, f26..f31 @0xd8..0x100,
//      locals region L = Gsave-8 = 0x88 (verified law: frame = Gsave + 4*nGPR). Got: stwu -0x150,
//      stmw r14,0xd8, CR 0xd4, LR 0x154, f26..f31 @0x120..0x148. The *used* stack offsets are
//      already correct (fr.idx@0x08, s28@0x28, s30@0x30, s40@0x40, cvt@0x80/0x84) — only the
//      RESERVED region is 0x48 too big. Bisect: frame == Fr_struct_size + 0xCC exactly
//      (pad 0x00->0x118, 0x10->0x128, 0x20->0x138, 0x38->0x150), so the 0xCC is non-struct
//      locals/temps and must be cut by 0x48 for the 0x84 struct to land at 0x108. Removing
//      ALL PS arithmetic changed nothing (0x150), so it is not __ps_t slots; removing the
//      whole 2nd branch drops it to 0xc0, removing the 1st to 0xb8 — i.e. the 0x90 is spread
//      over the 2nd branch's non-struct locals. UNSOLVED: which ones.
//  (2) LENGTH: object 0x420 vs want 0x43c (7 words short). Per §6cs-1 the masked % is
//      meaningless until this matches. Suspected sources: want keeps TWO dead CR-cached
//      branches retail defers to the tail (`cmpwi cr3,r15,0` @0x510 -> `beq cr3` @0x79C and
//      `cmpwi cr4,r19,0` @0x554 -> `beq cr4` @0x7A8 — doc-28/§6x-89 shape, mfcr r12 already
//      present in got); got emits them as immediate branches in the other order. Also
//      want's `addi r9,r1,0x38` + `mr r10,r9` pair (a SECOND address web for &fr.col, §6bf
//      un-share) is absent from got.
//  (3) REGISTER MAP (the bulk of the 223). Objects that are only *read* through pointers in
//      want hold a callee-saved home and got picks a different one: r22 (fn_80057CA0 result,
//      FIXED with `register s32 r22 __asm__("r22")` — 0 emitted insns), r21/r29 (the two scan
//      counters, swapped), r31/r30 (idx base vs Ent*), r15/r19 vs r16/r20 (the two frees),
//      r25 vs r28 (the inner counter). §6ds-2: pin ONE member of each permuted group, the
//      one whose want colour is not the pool's head.
//  (4) `lq` where want has `psq_lx` (opcode 4 XO=6, 0x101A000C @0x5DC) for the
//      lbl_80364CC8 + idx*0x28 pair load. want keeps TWO address webs for one value
//      (r13 base+index for psq_lx, r31 +0x8 displacement for psq_l) — §6bt web identity;
//      got CSEs them into one `lq`. Untested: two separate address temporaries, the
//      §6dq "dead old value" pointer-reassignment form, volatile-qualified pair reads.
//  (5) `cmpw` vs `cmplw` on `*(s32 *)&lbl_8030089C` and on the `r21 < r23` loop test (want
//      `cmpw`, got sometimes unsigned) — §6c-27/§6ev: the count type must be s32 and the
//      guard written against the VARIABLE.
//  (6) Countdown loops: form `if (n > 0) { do {} while (--r9 != -1); }` reproduces want's
//      6-word `addi/cmpwi/ble/cmpwi/addi/bne` shape best (measured in an isolated probe) but
//      want has the `addi` BEFORE the guard compare; every spelling GCC emits puts the
//      compare first (§6dj: the addi's BIRTH order selects its block — untried lever).
// MEASURED-REJECTED (do not re-run): 6 separate __ps_t in a nested block vs function scope
//      vs a `__ps_t pv[6]` array (0x150 / 0x150 / 0x180); `register __ps_t x __asm__("frN")`
//      pins (no frame change, §6cx/§6be don't transfer to stack-slot allocation);
//      removing all PS math (frame unchanged); `volatile double _dummy`; every
//      `-fno-schedule*`/`-fno-gcse`/`-fno-sched-*`/`-Os`/`-O3`; `volatile Fr fr` vs plain
//      (plain wins, and it also removes the spurious crclr-free difference);
//      `s32 fn_80057CA0();` prototype vs none (neither emits the crclr retail has at 0x3E0);
//      r13-explicit addr -1 temporary for the pair load.
// TOOLING: no inline asm emitted except two zero-code `"+r"` identity barriers; no
//      `volatile double _dummy`; object has `.text` + `.rela.text` ONLY (no private .rodata,
//      so masked-EXACT would be promote-clean); 0 opcode-4/VMX mislabel traps applied — the
//      five PS ops were hand-decoded and verified against a cc1 probe.
// range=0x8005A3AC-0x8005A7E8 size=1084B
// family=m2c
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
#include "mem.h"

typedef struct {
    f32 p0[2];
    f32 p1[2];
    f32 f10;
    f32 f14;
    char _p18[4];
    u8 b1C;
    u8 b1D;
    u8 b1E;
    char _p1F[9];
} Ent;

typedef struct {
    s32 idx[8];
    volatile f32 s28[2];
    volatile f32 s30[2];
    s32 col;
    char _p3C[4];
    f32 s40[2];
    char _p48[0x38];
    struct { u32 h; u32 l; } cvt;
    char _p88[4];
} Fr;

s32 fn_8005A0D4(Ent *, s32);
s32 fn_8005F550(s32);
void fn_8005F584(s32, void *);
void fn_8005F688(s32, void *);
void fn_8005F740(s32, void *);
f32 sqrtf(f32);

extern char lbl_80364CC8[];
extern s32 lbl_8030089C;
extern char lbl_802934DC[];
extern char lbl_802934E0[];
extern char lbl_802934E8[];
extern char lbl_80293458[];

void fn_8005A3AC(s32 arg0) {
    Fr fr;
    Ent *r30;
    Ent *r31b;
    s32 *r24;
    s32 *r31;
    s32 *r26p;
    s32 r9;
    s32 r9_2;
    s32 r10;
    s32 r15;
    s32 r16;
    s32 r17;
    s32 r18;
    s32 r19;
    s32 r20;
    s32 r21;
    register s32 r22 __asm__("r22");
    s32 r23;
    s32 r25;
    s32 r27b;
    s32 r29;
    s32 r30b;
    s32 t0;
    s32 b1;
    s32 b2;
    u8 *b3;
    f32 f0;
    f32 f1;
    f32 f10;
    f32 f11;
    f32 f12;
    f32 f13;
    f32 f26;
    f32 f28;
    f32 f29;
    f32 f30;
    f32 f31;
    f64 m27;
    f64 m31;
    f32 fv;

    r22 = fn_80057CA0();
    if (r22 == 0) {
        goto end;
    }
    r21 = 0;
    r29 = 0;
    if (r21 < *(s32 *)&lbl_8030089C) {
        f31 = *(f32 *)&lbl_802934DC;
        r30 = (Ent *)lbl_80364CC8;
        r31 = &fr.idx[0];
        do {
            if (r30->f10 > f31 && fn_8005A0D4(r30, arg0) != 0) {
                *r31 = r29;
                r21 += 1;
                r31 += 1;
                if (r21 > 7) {
                    break;
                }
            }
            r29 += 1;
            r30 += 1;
        } while (r29 < *(s32 *)&lbl_8030089C);
    }
    if (r21 == 0) {
        r23 = fn_8005F550(r22);
        if (r23 <= 0) {
            goto end;
        }
        r20 = (s32)Mem_Alloc(r23 * 4);
        r9 = r23 - 1;
        if (r23 != 0) {
            while (0 != r9--) {
            }
        }
        fn_8005F688(r22, (void *)r20);
        fn_8005F740(r22, (void *)r20);
        if (r20 != 0) {
            Mem_Free2((void *)r20);
        }
        goto end;
    } else if (r21 > 0) {
        r23 = fn_8005F550(r22);
        if (r23 <= 0) {
            goto end;
        }
        r15 = (s32)Mem_Alloc(r23 * 0x10);
        r9 = r23 - 1;
        r9_2 = r9;
        r19 = (s32)Mem_Alloc(r23 * 4);
        if (r9_2 != -1) {
            while (0 != r9_2--) {
            }
        }
        fn_8005F584(r22, (void *)r15);
        r24 = (s32 *)r19;
        fn_8005F688(r22, (void *)r19);
        r26p = (s32 *)r15;
        r10 = 0;
        m27 = *(f64 *)lbl_802934E0;
        f26 = *(f32 *)&lbl_802934E8;
        while (r10 < r23) {
            r25 = 0;
            f30 = *(f32 *)&lbl_802934DC;
            r16 = r10 + 1;
            r17 = r24 + 1;
            f29 = f30;
            r18 = r26p + 4;
            f28 = f30;
            if (r25 < r21) {
                __ps_t pa;
                __ps_t pb;
                __ps_t pm;
                __ps_t pw;
                __ps_t pt;
                __ps_t pz;
                m31 = *(f64 *)lbl_802934E0;
                r27b = (s32)lbl_80364CC8;
                r20 = (s32)lbl_80293458;
                r29 = (s32)&fr.idx[0];
                r30b = r21;
                do {
                    t0 = *(s32 *)r29;
                    pb = *(__ps_t *)((char *)r26p + 8);
                    r29 += 4;
                    t0 = t0 * 0x28;
                    pa = *(__ps_t *)r26p;
                    pm = *(__ps_t *)lbl_80293458;
                    r31b = (Ent *)((char *)r27b + t0);
                    pw = *(__ps_t *)((char *)r27b + t0);
                    pt = *(__ps_t *)((char *)r31b + 8);
                    f10 = r31b->f14;
                    pz = __builtin_ps_sub(pa, pw);
                    pb = __builtin_ps_sub(pb, pt);
                    ((volatile __ps_t *)fr.s28)[0] = pz;
                    pw = __builtin_ps_mul(pb, pw);
                    ((volatile __ps_t *)fr.s30)[0] = pb;
                    pw = __builtin_ps_merge10(pw, pm);
                    pz = __builtin_ps_madd(pz, pw, pz);
                    pz = __builtin_ps_sum0(pz, pz, pz);
                    ((__ps_t *)fr.s40)[0] = pz;
                    fv = fr.s40[0];
                    f10 = f10 * f10;
                    f0 = fv;
                    f1 = f0;
                    if (f1 < f10) {
                        f1 = sqrtf(f0);
                        r25 = 1;
                        f0 = r31b->f14;
                        f1 = (f0 - f1) / f0;
                        b2 = r31b->b1C;
                        b1 = r31b->b1D;
                        t0 = r31b->b1E;
                        f11 = r31b->f10;
                        fr.cvt.h = 0x43300000;
                        fr.cvt.l = (u32)b2;
                        f12 = (f32)(*(f64 *)&fr.cvt - m31);
                        fr.cvt.h = 0x43300000;
                        fr.cvt.l = (u32)b1;
                        f13 = (f32)(*(f64 *)&fr.cvt - m31);
                        fr.cvt.h = 0x43300000;
                        fr.cvt.l = (u32)t0;
                        f0 = (f32)(*(f64 *)&fr.cvt - m31);
                        f11 = f11 * f1;
                        f28 = f28 + f11 * f0;
                        f29 = f29 + f11 * f12;
                        f30 = f30 + f11 * f13;
                    }
                    r30b -= 1;
                } while (r30b != 0);
            }
            if (r25 != 0) {
                fr.col = *r24;
                t0 = fr.col >> 24;
                fr.cvt.h = 0x43300000;
                fr.cvt.l = (u32)t0;
                f0 = (f32)((f32)(*(f64 *)&fr.cvt - m27) + f29);
                if (f0 <= f26) {
                    t0 = (u8)f0;
                } else {
                    t0 = 0xFF;
                }
                b1 = (fr.col >> 16) & 0xFF;
                *((u8 *)&fr.col + 0) = t0;
                fr.cvt.h = 0x43300000;
                fr.cvt.l = (u32)b1;
                f0 = (f32)((f32)(*(f64 *)&fr.cvt - m27) + f30);
                if (f0 <= f26) {
                    t0 = (u8)f0;
                } else {
                    t0 = 0xFF;
                }
                b3 = (u8 *)&fr.col;
                *((u8 *)b3 + 1) = t0;
                b3 = b3 + 1;
                b2 = (fr.col >> 8) & 0xFF;
                fr.cvt.h = 0x43300000;
                fr.cvt.l = (u32)b2;
                f0 = (f32)((f32)(*(f64 *)&fr.cvt - m27) + f28);
                if (f0 <= f26) {
                    t0 = (u8)f0;
                } else {
                    t0 = 0xFF;
                }
                *((u8 *)b3 + 1) = t0;
                *r24 = fr.col;
            }
            r10 = r16;
            r24 = (s32 *)r17;
            r26p = (s32 *)r18;
        }
        fn_8005F740(r22, (void *)r19);
        if (r15 != 0) {
            Mem_Free2((void *)r15);
        }
        if (r19 != 0) {
            Mem_Free2((void *)r19);
        }
    }
end:
    return;
}
