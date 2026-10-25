// REBUILD — fn_800A970C, written from the
// COMPLETE retail listing (build/G2TE52/asm/auto_01_800A95EC_text.s,
// .fn fn_800A970C, 0x800A970C..0x800A9C68, size 0x560 = 1376B).
//
// The first attempt scored 1.74% (worse than the 9.01% husk). A later pass uses the measured
// index-aligned diff build/b34pkt/fn_800A970C.rb.diff.txt, which showed the
// first misalignment at 0x9740 and `?` past it.  Root causes fixed here:
//
//  (1) STRUCT WAS OFF BY 4 FROM 0xE4 ON.  Every field after unk0xE4 was
//      declared one word low, so `arg0->unk0xEC` compiled to `lwz r0, 0xe8(r31)`
//      (retail: `lwz r0, 0xec(r31)`) and arg0->unk0xF0 to 0xEC.  Fixed: a pad
//      s32 unk0xE8 between unk0xE4 and unk0xEC.
//  (2) THE `arg1` IF/ELSE WAS INVERTED.  Retail emits
//         cmpwi r4,0 ; beq .L_800A97A0 ; <psq block> ; b .L_800A97A4
//         .L_800A97A0: fmr f31, f9
//         .L_800A97A4: <switch>
//      i.e. the branch-if-FALSE of the tested condition jumps to the `fmr`.
//      That is the canonical layout of `if (c) { psq block } else { fmr }`
// with c = `arg1 != 0`. The first attempt wrote `if (arg1 == 0) {...} else {...}`,
//      which emits `bne` to the psq block and puts the `fmr` first — the whole
//      function was then index-shifted from 0x9740 on.
//  (3) FRAME.  Retail: stwu -0x90 / stfd f30,0x80 / stfd f31,0x88 /
//      stmw r30,0x78 / stw r0,0x94.  Locals are ONE address-taken array of
//      twelve 8-byte pairs at r1+0x08 (buf[i] = r1+0x08+8i); the f32 views are
//      lane 0 of buf[6..10]      (0x38,0x40,0x48,0x50,0x58) and lane 1 of buf[11]
//      (0x64), read through the builtin SN_PS_type union (`.flt.hi` lane 0,
// `.flt.lo` lane 1) — `*(f32 *)&pair` ICEs 3.9.3. The first attempt added a `f32 pad_lo[2]`, which GCC put *after* buf and
//      which both shrank the frame and left the outgoing-args area at 8 bytes.
//      The pad is gone here.  NOTE the remaining delta in round 2 was that we
//      saved ONE FPR (f31) where retail saves TWO (f30 AND f31): retail keeps
//      lbl_80298238 in f30 across the whole tail of case 3 (0x9B50..0x9C64),
//      so the body must keep that constant in a live local, not re-load it per
//      use.  `c2` below is exactly that.  With two FPR saves the frame becomes
//      0x60 (buf) + 0x10 (outgoing area) + 8 (stmw r30) + 16 (f30,f31) = 0x90.
//
// family=m2c range=0x800A970C-0x800A9C6C size=1376B
// INERT: not registered in splits.txt/configure.py — never compiled.
//
// TYPE MODEL: the shared Unk_0352A96C hides every paired-single field behind
// `char pad...`, which is why the old draft was cast soup.  A correctly-typed
// local struct is declared instead (0xA8/0xAC/0xB0/0xB8/0xE4/0xF0 are f32 —
// retail does lfs/stfs/fcmpu on them — and 0xB4/0x18/0x60/0x64/0xEC are s32).
//
// SEMANTIC POINTS taken from the retail stream (all of these were wrong or
// missing in the husk):
//   * case 3 divides BEFORE the branch (`fdivs f31,f0,f13` at 0x99BC, before
//     `bge 0x800A9A40`), and both case-3 halves write arg0->0x08/0x10;
//   * case 1's `& 2` mask lives in the callee-saved r30 because it is stored
//     back to 0xEC *after* the GetChecksum_3/fn_800A952C calls, while case 2's
//     `& 4` mask is dead after its branch (r9);
//   * the `unk0xB4 & 4` "stop the checksum motion" block appears ONCE in case 3
//     (0x9B20..0x9B48), not twice;
//   * case 1's tail is `if (arg0->unk0xA8 == lbl_80298234) { <copy+checksum>;
//     if (fn_800A952C() != 0) { arg0->unk0xEC = m2; return 0; } return 1; }
//     else { fn_800A8D04(); fn_800A952C(); arg0->unk0xB4 |= 4; fn_800A95EC(); }`;
//   * case 3's tail hoists lbl_80298238 into f30 and rereads arg0->0x40/0x48
//     after storing them (the two ps_adds are on the MEMORY values);
//   * the final rsqrte block stores the pair to buf[11] (0x60), overwrites
//     lane 1 with lbl_80298238 (stfs f30,0x64), then RELOADS the pair.
//
// STORE ORDER: around 0x9834..0x9848 and 0x9B80..0x9BC0 retail's stores come
// out in exactly the REVERSE of the source order the project documents as the
// seed; the statements below are written in that reversed order (e.g. 0x10
// before 0x08, 0x78 before 0x70, 0xEC last) because that is what reproduces the
// retail emission byte-for-byte.
//
// UNCERTAIN / worth measuring (the coordinator can and should iterate):
//   a) the 0x10-byte outgoing-argument area: retail's locals end at 0x67 and
//      stmw starts at 0x78, so 0x10 bytes sit between.  If the frame comes out
//      0x80 rather than 0x90 the missing 0x10 is that outgoing area (a callee
//      prototype one word wider than the actual call would produce it);
//   b) case 3's `f32 mag = d;` (pair→float conversion emitting `ps_mr`) versus
//      a union-lane read (`buf[n].f[0]`, which would store+reload): retail uses
//      ps_mr at 0x9C1C, so the register conversion is the right spelling here,
//      and the opposite (union lane) is right for the arg1 dot product at
//      0x9778/0x977C — both are used deliberately below;
//   c) the two `ps_mr` copies in case 1's first block (0x982C/0x9830) come from
//      using each loaded pair twice; they are written as named locals here.
#include "types.h"
#include "qb_constants.h"

/* The 8-byte pair-with-f32-view stack object retail stores to and reloads
   (stfs/psq_l at 0x38, 0x40, 0x48, 0x50, 0x58, 0x60/0x64) is the compiler's
   own SN_PS_type union: `.ps` is the pair, `.flt.hi` is LANE 0 and
   `.flt.lo` LANE 1 (per the promoted dot-product template fn_800A11D8).
   `*(f32 *)&<register pair>` ICEs 3.9.3 (docs/parkings/06), so the builtin
   union members are the only correct way to read a lane back out. */

/* Skate script-motion object, paired-single fields typed.  Offsets verified
   against every lfs/stfs/lwz/stw/psq_* in the retail listing. */
typedef struct {
    char pad0x0[0x08];
    __ps_t unk0x08;
    __ps_t unk0x10;
    s32 unk0x18;
    char pad0x1C[0x24];      /* 0x1C..0x3F */
    __ps_t unk0x40;
    __ps_t unk0x48;
    char pad0x50[0x10];      /* 0x50..0x5F */
    s32 unk0x60;
    s32 unk0x64;
    char pad0x68[0x08];      /* 0x68..0x6F */
    __ps_t unk0x70;
    __ps_t unk0x78;
    __ps_t unk0x80;
    __ps_t unk0x88;
    char pad0x90[0x18];      /* 0x90..0xA7 */
    f32 unk0xA8;
    f32 unk0xAC;
    f32 unk0xB0;
    s32 unk0xB4;
    f32 unk0xB8;
    char pad0xBC[0x04];
    __ps_t unk0xC0;
    __ps_t unk0xC8;
    __ps_t unk0xD0;
    __ps_t unk0xD8;
    char pad0xE0[0x04];
    f32 unk0xE4;
    s32 unk0xE8;
    s32 unk0xEC;
    f32 unk0xF0;
} SkateCtl;

extern f32 lbl_80298234;     /* 0.0f  */
extern f32 lbl_80298238;     /* 1.0f? */
extern f32 lbl_8029823C;     /* 2.0f? */
extern __ps_t lbl_802981C0;

void fn_800A85A0(SkateCtl *);
void fn_800A8D04(SkateCtl *);
void fn_800A8D9C(SkateCtl *, f32);
s32 fn_800A952C(SkateCtl *);
void fn_800A95EC(SkateCtl *);
s32 GetChecksum_3(s32, s32);
void fn_800D68B8(void *, s32);

s32 fn_800A970C(SkateCtl *arg0, __ps_t *arg1, f32 farg0) {
    SN_PS_type buf[12];
    f32 var_f31;
    f32 x;
    __ps_t t0, t1;
    __ps_t k, m, r;
    SN_PS_type d;
    f32 c2;

    if (arg0->unk0xEC == 4) {
        return 1;
    }

    if (arg1 != 0) {
        /* dot product of arg1[] with the object's 0x40/0x48 pair, +1.0 from
           lbl_802981C0 in lane 1; result lane 0 is read back through the
           stack slot (psq_st/lfs pair at 0x9778/0x977C). */
        t0 = __builtin_ps_mul(arg1[1], arg0->unk0x48);
        t0 = __builtin_ps_merge00(t0, lbl_802981C0);
        t0 = __builtin_ps_madd(arg1[0], arg0->unk0x40, t0);
        buf[6].ps = __builtin_ps_sum0(t0, t0, t0);
        x = buf[6].flt.hi;
        if (x == lbl_80298234) {
            var_f31 = lbl_80298238;
        } else {
            var_f31 = farg0 * x;
        }
    } else {
        var_f31 = farg0;
    }

    switch (arg0->unk0xEC) {
    case 0:
        fn_800A85A0(arg0);
        arg0->unk0xEC = 1;
        arg0->unk0xF0 = lbl_80298234;
        /* fall through */
    case 1: {
        s32 m2 = arg0->unk0xB4 & 2;

        arg0->unk0xB0 = arg0->unk0xB0 + var_f31;
        if (m2 != 0) {
            if (arg0->unk0xB0 >= arg0->unk0xAC) {
                fn_800A8D04(arg0);
                return 0;
            }
            t0 = arg0->unk0x80;
            t1 = arg0->unk0x88;
            arg0->unk0x10 = t1;
            arg0->unk0x08 = t0;
            arg0->unk0x78 = t1;
            arg0->unk0x60 = arg0->unk0x64;
            arg0->unk0x70 = t0;
            arg0->unk0xEC = 4;
            return 1;
        }
        if (arg0->unk0xB0 >= arg0->unk0xAC - arg0->unk0xA8) {
            fn_800A8D04(arg0);
            return 0;
        }
        if (arg0->unk0xA8 == lbl_80298234) {
            t0 = arg0->unk0x80;
            t1 = arg0->unk0x88;
            arg0->unk0x10 = t1;
            arg0->unk0x08 = t0;
            fn_800D68B8(GetChecksum_3(arg0->unk0x18, QB_MOTION), arg0->unk0x64);
            if (fn_800A952C(arg0) != 0) {
                arg0->unk0xEC = m2;
                return 0;
            }
            return 1;
        }
        fn_800A8D04(arg0);
        fn_800A952C(arg0);
        arg0->unk0xB4 = arg0->unk0xB4 | 4;
        fn_800A95EC(arg0);
        break;
    }
    case 2:
        arg0->unk0xB0 = arg0->unk0xB0 + var_f31;
        if ((arg0->unk0xB4 & 4) != 0) {
            if (arg0->unk0xB0 >= arg0->unk0xE4 * lbl_8029823C) {
                arg0->unk0xB4 = arg0->unk0xB4 & ~4;
                fn_800D68B8(GetChecksum_3(arg0->unk0x18, QB_MOTION),
                            arg0->unk0x60);
            }
        }
        if (arg0->unk0xB0 <= arg0->unk0xE4) {
            fn_800A8D9C(arg0, var_f31);
        } else {
            f32 diff = arg0->unk0xB0 - arg0->unk0xE4;

            fn_800A8D9C(arg0, var_f31 - diff);
            arg0->unk0xB8 = diff;
            var_f31 = lbl_80298234;
            arg0->unk0xB8 = var_f31;
            fn_800A85A0(arg0);
            fn_800A8D04(arg0);
            arg0->unk0xF0 = var_f31;
            arg0->unk0xEC = 1;
        }
        break;
    case 3:
        arg0->unk0xB0 = arg0->unk0xB0 + var_f31;
        var_f31 = arg0->unk0xB0 / arg0->unk0xAC;
        if (arg0->unk0xB0 < arg0->unk0xAC) {
            /* retail 0x99C4..0x9A3C */
            arg0->unk0x08 = arg0->unk0xC0;
            arg0->unk0x10 = arg0->unk0xC8;
            buf[7].flt.hi = var_f31;
            k = buf[7].ps;
            buf[0].ps = __builtin_ps_muls0(
                __builtin_ps_sub(arg0->unk0x70, arg0->unk0xC0), k);
            buf[1].ps = __builtin_ps_sub(arg0->unk0x78, arg0->unk0xC8);
            buf[1].ps = __builtin_ps_muls0(buf[1].ps, k);
            arg0->unk0x08 = __builtin_ps_add(arg0->unk0x08, buf[0].ps);
            arg0->unk0x10 = __builtin_ps_add(arg0->unk0x10, buf[1].ps);
        } else {
            /* retail 0x9A40..0x9ABC */
            arg0->unk0x08 = arg0->unk0x70;
            arg0->unk0x10 = arg0->unk0x78;
            buf[8].flt.hi = var_f31 - lbl_80298238;
            k = buf[8].ps;
            buf[0].ps = __builtin_ps_muls0(
                __builtin_ps_sub(arg0->unk0xD0, arg0->unk0x70), k);
            buf[1].ps = __builtin_ps_sub(arg0->unk0xD8, arg0->unk0x78);
            buf[1].ps = __builtin_ps_muls0(buf[1].ps, k);
            arg0->unk0x08 = __builtin_ps_add(arg0->unk0x08, buf[0].ps);
            arg0->unk0x10 = __builtin_ps_add(arg0->unk0x10, buf[1].ps);
        }

        /* retail 0x9AC0..0x9C48 */
        {
            __ps_t e, f, g, h;

            e = __builtin_ps_sub(arg0->unk0x70, arg0->unk0xC0);
            f = __builtin_ps_sub(arg0->unk0x78, arg0->unk0xC8);
            g = __builtin_ps_sub(arg0->unk0xD0, arg0->unk0x70);
            h = __builtin_ps_sub(arg0->unk0xD8, arg0->unk0x78);
            buf[4].ps = e;
            buf[5].ps = f;
            var_f31 = var_f31 * lbl_8029823C;
            buf[0].ps = e;
            buf[1].ps = f;
            buf[2].ps = g;
            buf[3].ps = h;
            buf[4].ps = g;
            buf[5].ps = h;
        }
        if (var_f31 >= lbl_8029823C) {
            if ((arg0->unk0xB4 & 4) != 0) {
                arg0->unk0xB4 = arg0->unk0xB4 & ~4;
                fn_800D68B8(GetChecksum_3(arg0->unk0x18, QB_MOTION),
                            arg0->unk0x60);
            }
        }
        c2 = lbl_80298238;
        if (var_f31 < c2) {
            var_f31 = c2;
            arg0->unk0xB8 = lbl_80298234;
            fn_800A85A0(arg0);
            arg0->unk0xEC = 1;
        }
        buf[9].flt.hi = c2 - var_f31;
        k = buf[9].ps;
        buf[10].flt.hi = var_f31;
        m = buf[10].ps;
        buf[5].ps = __builtin_ps_muls0(buf[1].ps, k);
        buf[4].ps = __builtin_ps_muls0(buf[0].ps, k);
        arg0->unk0x40 = buf[4].ps;
        arg0->unk0x48 = buf[5].ps;
        buf[4].ps = __builtin_ps_muls0(buf[2].ps, m);
        buf[5].ps = __builtin_ps_muls0(buf[3].ps, m);
        arg0->unk0x40 = __builtin_ps_add(arg0->unk0x40, buf[4].ps);
        arg0->unk0x48 = __builtin_ps_add(arg0->unk0x48, buf[5].ps);
        d.ps = __builtin_ps_mul(arg0->unk0x48, arg0->unk0x48);
        d.ps = __builtin_ps_merge00(d.ps, lbl_802981C0);
        d.ps = __builtin_ps_madd(arg0->unk0x40, arg0->unk0x40, d.ps);
        d.ps = __builtin_ps_sum0(d.ps, d.ps, d.ps);
        {
            f32 mag = d.flt.hi;
            if (mag > lbl_80298234) {
                r = __builtin_ps_rsqrte(d.ps);
                buf[11].ps = r;
                arg0->unk0x40 = __builtin_ps_muls0(arg0->unk0x40, r);
                buf[11].flt.lo = c2;
                arg0->unk0x48 = __builtin_ps_mul(arg0->unk0x48, buf[11].ps);
            }
        }
        break;
    }

    return 0;
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — semantic paired-single reconstruction
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SIGNATURE: caller at 0x800D960C passes (obj, ptr_or_null, float) r3/r4/f1.
// STATUS: 3.4% masked (12/351 words), compiled 1404B vs retail 1376B.
// KEY INSIGHT: frame size 0x90 matches via volatile char pad[0x28], but
// the compiler allocates 3 FPR saves (f29,f30,f31) vs retail's 2 (f30,f31)
// because 4 PSU locals (f0,f11,f12,f13) exceed the 2 scratch FPRs (f12-f13)
// available after the input lands in f11. The extra f29 save shifts r30 from
// 0x78 to 0x70, cascading every subsequent stack offset.
//
// 2026-10-07: the "4-operand ps_mul not expressible with the
// 2-operand builtin" claim above was WRONG for the var_f31 select block. WANT
// 0x800A9750 is a plain 2-operand `ps_mul f13,f13,f12` (= *(arg1+8) *
// *(arg0+0x48)) and 0x800A9764 is `ps_madd f0,f0,f12,f13` (fA*fC+fB with
// fC=f12, fB=f13) -- i.e. __builtin_ps_madd(a, f12, f13) with the natural
// a*b+c sense. The old body had (a) scalar `f13.flt.hi/lo = ...` lane
// multiplies, which compiled to the lwz/lwz/fmuls/stfs mess in the GOT column
// at 0x48-0x94, and (b) the madd operands swapped (f13,f12). Both are now
// fixed to the want spelling (1:1 vs the WANT words quoted in the comments at
// those lines); that also drops 4 scalar temps, which is the first step to
// removing the extra f29 save.
//
// PARKED 2026-10-07: still far from a match. FIRST divergence is the
// prologue: WANT saves f30/f31 + stmw r30@0x78 (frame 0x90), GOT saves
// f29/f30/f31 + stmw r30@0x70 (same 0x90 frame), and that one extra stfd
// pushes r30 down 8 and cascades every stack slot and the whole register
// allocation. ROOT CAUSE: this draft declares FOUR function-scope PSU locals
// (`PSU f0, f11, f12, f13;`) whose live ranges span the entire switch, so cc1
// must home some of them in callee-saved FPRs. Retail has no such named
// variables -- each case re-derives its __ps_t values from fresh loads and
// keeps only the running result (f31) and one loop invariant (f30) across
// statements. NEXT IDEA (the only route with a real chance): delete the
// function-scope `f0/f11/f12/f13` declarations and re-spell each case's PS
// sequence with block-scoped `__ps_t` temps that are loaded and consumed
// immediately (one temp per reuse), so no PS value stays live across a call
// or across case boundaries. Also check the case-3 `ps_mul(var_f31, f0.ps)`
// and the duplicated `unk0xB4 & 4`/`unk0xB8 = lbl_80298234`
// blocks -- retail has each of those ONCE (see WANT 0x800A99F0-0x800A9A5C),
// while the draft emits them twice.
