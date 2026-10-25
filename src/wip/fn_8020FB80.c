// PARKED 2026-10-03 (b03): DIFF 2.0% (baseline FAIL - did not compile).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x8020FB80
// Baseline was FAIL: the m2c draft called `sqrtf()` with no argument. Fixing
// that alone only got as far as a second ngccc failure (an ICE), so the whole
// body was rewritten from the disassembly; the body below is the honest
// reconstruction, not scaffolding.
//
// WHAT THIS FUNCTION IS
//   404 instructions (1616B), f28-f31 + r29-r31 saved, and ~130 of the words
//   are Gekko paired-single (psq_l/psq_st/ps_add/ps_mul/ps_madd/ps_sum0/
//   ps_muls0/ps_res/ps_rsqrte/ps_merge00/01).  Plain tools/disasm.py prints
//   NOTHING past 0x8020FDD4 because capstone cannot decode opcode 56/60; use
//   tools/ps_disasm.py, or better `tools/venv/bin/python -c "import sys;
//   sys.path.insert(0,'tools'); import ps_diff; ..."` which labels every op4
//   word (ps_diff.dec).  That decode is what the body below is written from.
//
// REMAINING DIFF (not a scheduling puzzle - a size/allocation problem)
//   * frame: want `stwu r1,-0xe0` with `stmw r29,0xb4` + f28..f31 at 0xc0..0xd8.
//     Got `stwu r1,-0xa8` with `stmw r27,0x7c` (r27! extra callee-saved GPR) and
//     only f29..f31 saved.  So got-1 vs want-1 differ in length AND register set,
//     which shifts EVERY subsequent word - the 2.0% is positional garbage, not
//     a measure of correctness.  Compiled .text = 1540B vs want 1616B (-19 words).
//   * The want's locals occupy 0x00..0xb3 (180B) with 11 pair slots
//     (0x08,0x10,0x38,0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78), 7 f32
//     (0x18..0x30), a double+u32 at 0xa8/0xac, and ~40B (0x80..0xa7) of
//     transient pair temps that nothing in this function names.
//   * The want keeps a DEAD `psq_st f13, 8(r1)` in BOTH case 2 and case 4
//     (the stored pair is never read).  Plain C deletes it; I marked the two
//     stack temps `volatile __ps_t` to force it, but that is a guess about how
//     the original escaped the address.
//
// RULED OUT / WORTH KNOWING
//   * `*(f32 *)&ps_local` (scalar lane read out of a `__ps_t` local) ICEs
//     ngccc 3.9.3 at expmed.c:1115 once that local has been through
//     __builtin_ps_madd/ps_sum0.  Minimal repro:
//         __ps_t a; f32 f; a = __builtin_ps_sum0(x,y,y); f = *(f32*)&a;
//     alone is FINE, but with a preceding ps_madd in the same function it ICEs.
//     Workaround used here: a `union { __ps_t ps; struct { f32 hi, lo; } flt; }`
//     and `.flt.hi` / `.flt.lo` instead of a pointer cast.
//   * `__ps_t * __ps_t` via the mode(PS) type (i.e. plain `a * b`) is a second
//     expmed.c:1115 ICE - always write __builtin_ps_mul(a, b).
//   * `(f32)((f64)s32_value - double_const) / f32_divisor` DOES reproduce the
//     want's `fsub; frsp; fdivs` + `lis r0,0x4330 / stw / lfd` 2^52-bias
//     sequence, but GCC 2.95 also prepends `xoris r30,r30,0x8000`, which the
//     want does not have.
//   * Switch shape: the want tests `cmpwi r0,2; beq / ble / cmpwi r0,3; beq /
//     cmpwi r0,4; beq / b skip`, i.e. t<=1 first, and t>4 skipping the whole
//     switch.  m2c's `default:` + `if (t>=0)` guard gets the t>4 case wrong.
//     A plain `switch` drops the `cmpwi r0,4; bgt` word entirely.
//   * `Unk_5EFC3140` in include/structs.h has `unk0x1944` and
//     `unk0x19B0` typed `s32` and `pad0x184C` typed `char[]` - all three are
//     `lfs`/s32-deref sites, so byte-offset macros (FL_/PS_) are needed;
//     structs.h cannot be edited from a wip draft.
//
// MOST PROMISING NEXT IDEA
//   Attack the frame first and ignore the body: get `stwu r1,-0xe0` +
//   `stmw r29,0xb4` + f28..f31 by naming the ~40B of unidentified pair temps
//   at 0x80..0xa7 as explicit locals and removing the r27 pressure (r27 comes
//   from the four hoisted `addi r6/r7/r10/r11, r31, ...` base pointers that the
//   want also has, so it may need the ps pair copies split as in
//   docs/parkings/06 M5.0m technique 5).  Until frame size and the saved-register
//   set agree, no percentage here means anything.
// family=m2c range=0x8020FB80-0x802101D0 size=1616B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AF58C;
extern f64 lbl_802AF590;
extern f32 lbl_802AF598;
extern f32 lbl_802AF59C;
extern char lbl_802AF808[];
extern __ps_t lbl_802AF450;

void GetStructure(u32 arg0, s32 arg1);
void GetFloat(u32 arg0, f32 *arg1, s32 arg2);
s32 fn_800AA02C(void *arg0);
s32 fn_800DF004(void *arg0, void *arg1, void *arg2);
void fn_80005A90(void *arg0, void *arg1);
void fn_8009F054(void *arg0, s32 arg1, s32 arg2, f32 farg0);
void fn_8020D2E4(void *arg0, s32 arg1);
void fn_80212C54(void *arg0, void *arg1, void *arg2);
void fn_802144B8(Unk_5EFC3140 *arg0);
f32 fn_80214C90(Unk_5EFC3140 *arg0);
void fn_802101D0(Unk_5EFC3140 *arg0);
void fn_80214690(Unk_5EFC3140 *arg0);
f32 sqrtf(f32 x);

typedef union { __ps_t ps; struct { f32 hi, lo; } flt; } PsPair;

#define PS_(p, o) (*(__ps_t *)((char *)(p) + (o)))
#define FL_(p, o) (*(f32 *)((char *)(p) + (o)))
#define HI_(p) (*(f32 *)(p))
#define LO_(p) (*(f32 *)((char *)(p) + 4))

void fn_8020FB80(Unk_5EFC3140 *arg0) {
    f32 s18;
    f32 s1C;
    f32 s20;
    f32 s24;
    f32 s28;
    f32 s2C;
    f32 s30;
    f32 fv;
    f32 fw;
    f32 f13;
    f32 fx;
    s32 t;
    volatile __ps_t p08;
    volatile __ps_t p10;
    PsPair p38;
    PsPair p40;
    PsPair ve;
    __ps_t p50;
    __ps_t p58;
    PsPair p60;
    PsPair p68;
    PsPair p70;
    PsPair p78;
    __ps_t p54;
    f32 s54;
    __ps_t va;
    __ps_t vb;
    __ps_t vc;
    __ps_t vd;
    void *scr;

    fw = lbl_802AF58C;
    t = arg0->unk0x1C;
    if (t >= 0) {
        if (t <= 1) {
            s32 itime;
            GetStructure(0x6775E538u, 0);
            GetFloat(0x0246DBF3u, &s18, 1);
            fw = s18;
            itime = fn_800AA02C((void *)((char *)arg0->unk0x183C + 0x1FC));
            GetStructure(0x6775E538u, 0);
            GetFloat(0x12333EBDu, &s1C, 1);
            fv = (f32)((f64)itime - lbl_802AF590) / s1C;
            f13 = (fv > lbl_802AF598) ? lbl_802AF598 : fv;
            fw = (lbl_802AF598 - fw) * f13 + fw;
        } else if (t <= 4) {
            GetStructure(0x6775E538u, 0);
            GetFloat(0x2F29D458u, &s20, 1);
            fw = s20;
        }
        if (t == 0 && arg0->unk0x1940 != 0) {
            if (fn_800DF004((void *)arg0->unk0x1848, &lbl_802AF808,
                            (void *)((char *)arg0 + 0x1880)) == 0) {
                if (*(s32 *)((char *)arg0 + 0x184C + 0x30) != 0) {
                    return;
                }
            }
        }
    }
    scr = (void *)arg0->unk0xC;
    GetStructure(0x6775E538u, 0);
    GetFloat(0x63D62A21u, &s24, 1);
    FL_(scr, 0xBC) = fw * s24;
    switch (t) {
    default:
        if (t >= 0) {
            fn_802144B8(arg0);
            fv = FL_(arg0, 0xA0);
            if (fv == lbl_802AF58C) {
                PS_(arg0, 0x1958) = PS_(arg0, 0x50);
                PS_(arg0, 0x1960) = PS_(arg0, 0x58);
                goto copy_done;
            }
            fw = fn_80214C90(arg0);
            GetStructure(0x6775E538u, 0);
            GetFloat(0x839FE542u, &s28, 1);
            fx = s28;
            GetStructure(0x6775E538u, 0);
            GetFloat(0xCC461B87u, &s2C, 1);
            fv = s2C;
            GetStructure(0x6775E538u, 0);
            GetFloat(0x7213EF07u, &s30, 1);
            va = PS_(arg0, 0x98);
            vb = PS_(arg0, 0x40);
            vc = lbl_802AF450;
            fw = fw * fx;
            vb = __builtin_ps_mul(vb, va);
            vd = PS_(arg0, 0x90);
            p38.ps = PS_(arg0, 0x38);
            vb = __builtin_ps_merge00(vb, vc);
            p38.ps = __builtin_ps_madd(p38.ps, vd, vb);
            fv = FL_(arg0, 0x1944);
            p38.ps = __builtin_ps_sum0(p38.ps, p38.ps, p38.ps);
            fx = s30 - fv;
            fx = fx * fv + fv;
            fv = p38.flt.hi;
            fw = fw / fx;
            if (p38.flt.hi > lbl_802AF58C) {
                fn_80005A90((void *)((char *)arg0 + 0x38),
                            (void *)((char *)arg0 + 0x90));
                va = PS_(arg0, 0x40);
                vb = lbl_802AF450;
                vd = __builtin_ps_mul(va, va);
                vc = PS_(arg0, 0x38);
                vb = __builtin_ps_merge00(vd, vb);
                vb = __builtin_ps_madd(vc, vc, vb);
                vb = __builtin_ps_sum0(vb, vb, vb);
                vb = __builtin_ps_rsqrte(vb);
                vb = __builtin_ps_res(vb);
                p40.ps = vb;
                if (p40.flt.hi < fw) {
                    ve.ps = __builtin_ps_merge01(vd, PS_(arg0, 0x48));
                    ve.ps = __builtin_ps_madd(vc, vc, ve.ps);
                    ve.ps = __builtin_ps_sum0(ve.ps, ve.ps, ve.ps);
                    if (ve.flt.hi > lbl_802AF58C) {
                        ve.ps = __builtin_ps_rsqrte(ve.ps);
                        ve.ps = __builtin_ps_muls0(ve.ps, PS_(arg0, 0x48));
                        p50 = __builtin_ps_muls0(vc, ve.ps);
                        s54 = lbl_802AF598;
                        p54 = __builtin_ps_mul(va, p50);
                        PS_(arg0, 0x38) = p50;
                        PS_(arg0, 0x40) = p54;
                    }
                }
            } else {
                p58 = PS_(arg0, 0x48);
                p58 = __builtin_ps_muls0(va, p58);
                p58 = __builtin_ps_muls0(vd, p58);
                PS_(arg0, 0x38) = p58;
                PS_(arg0, 0x40) = p58;
            }
            PS_(arg0, 0x1958) = PS_(arg0, 0x90);
            PS_(arg0, 0x1960) = PS_(arg0, 0x98);
            PS_(arg0, 0x50) = PS_(arg0, 0x90);
            PS_(arg0, 0x58) = PS_(arg0, 0x98);
        copy_done:
            fn_802101D0(arg0);
            vb = PS_(arg0, 0x40);
            va = lbl_802AF450;
            vd = PS_(arg0, 0x38);
            vc = __builtin_ps_mul(vb, vb);
            vb = __builtin_ps_merge00(vb, vc);
            vb = __builtin_ps_madd(vd, vd, vb);
            p60.ps = __builtin_ps_sum0(vb, vb, vb);
            if (p60.flt.lo > lbl_802AF59C) {
                PS_(arg0, 0x1958) = vd;
                PS_(arg0, 0x1960) = vb;
                p68.ps = sqrtf(p60.flt.lo);
                p68.ps = __builtin_ps_res(p68.ps);
                PS_(arg0, 0x1958) = __builtin_ps_muls0(vd, p68.ps);
                PS_(arg0, 0x1960) = __builtin_ps_muls0(vb, p68.ps);
            } else {
                PS_(arg0, 0x1958) = PS_(arg0, 0x50);
                PS_(arg0, 0x1960) = PS_(arg0, 0x58);
            }
            fn_80214690(arg0);
        }
        break;
    case 4:
        arg0->unk0x1998 = 1;
        PS_(arg0, 0x19A8) = PS_(arg0, 0x30) + PS_(arg0, 0x7E0);
        PS_(arg0, 0x19A0) = PS_(arg0, 0x50);
        p08 = PS_(arg0, 0x28) + PS_(arg0, 0x7D8);
        p70.ps = __builtin_ps_mul(PS_(arg0, 0x19A0),
              __builtin_ps_madd(__builtin_ps_mul(PS_(arg0, 0x19A8), PS_(arg0, 0x19A8)),
                                p08,
                                __builtin_ps_merge00(__builtin_ps_mul(PS_(arg0, 0x19A8),
                                                                       PS_(arg0, 0x19A8)),
                                                     lbl_802AF450)));
        p70.ps = __builtin_ps_sum0(p70.ps, p70.ps, p70.ps);
        FL_(arg0, 0x19B0) = p70.flt.hi;
        FL_(scr, 0xB8) = lbl_802AF58C;
        FL_(scr, 0xC0) = lbl_802AF58C;
        PS_(arg0, 0x1958) = PS_(arg0, 0x50);
        PS_(arg0, 0x1960) = PS_(arg0, 0x58);
        break;
    case 2:
        arg0->unk0x1998 = 1;
        PS_(arg0, 0x19A0) = PS_(arg0, 0x50);
        PS_(arg0, 0x19A8) = PS_(arg0, 0x58);
        p10 = PS_(arg0, 0x30) + PS_(arg0, 0x7E0);
        p08 = PS_(arg0, 0x28) + PS_(arg0, 0x7D8);
        p78.ps = __builtin_ps_mul(PS_(arg0, 0x19A0),
              __builtin_ps_madd(__builtin_ps_mul(PS_(arg0, 0x19A8), PS_(arg0, 0x19A8)),
                                p08,
                                __builtin_ps_merge00(__builtin_ps_mul(PS_(arg0, 0x19A8),
                                                                       PS_(arg0, 0x19A8)),
                                                     lbl_802AF450)));
        p78.ps = __builtin_ps_sum0(p78.ps, p78.ps, p78.ps);
        FL_(arg0, 0x19B4) = FL_(arg0, 0x2C) - FL_(arg0, 0x19BC);
        FL_(arg0, 0x19B0) = p78.flt.hi;
        FL_(scr, 0xB8) = lbl_802AF58C;
        FL_(scr, 0xC0) = lbl_802AF58C;
        PS_(arg0, 0x1958) = PS_(arg0, 0x50);
        PS_(arg0, 0x1960) = PS_(arg0, 0x58);
        break;
    case 3:
        FL_(scr, 0xB8) = lbl_802AF58C;
        FL_(scr, 0xC0) = lbl_802AF58C;
        PS_(arg0, 0x1958) = PS_(arg0, 0x50);
        PS_(arg0, 0x1960) = PS_(arg0, 0x58);
        break;
    }
    fn_80212C54(arg0, (void *)((char *)scr + 0xB8), (void *)((char *)scr + 0xBC));
    fn_8020D2E4(arg0, 1);
    fn_8009F054(scr, 0x8687163A, 0, lbl_802AF58C);
}