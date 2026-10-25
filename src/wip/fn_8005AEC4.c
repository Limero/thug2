// PARKED 2026-10-03 (a67): DIFF. Reproduce with
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_got.py 0x8005AEC4
// (test_wip_drafts.py --addr 0x8005AEC4 prints "DIFF" with no pct; want_got's
// index-aligned figure is 17.57% / 122 diffs — the previous m2c body gave 476B,
// this one gives 592B against want 600B, i.e. the whole 600-byte function now
// compiles instead of two thirds of it.)
//
// The body below is hand-derived from the disassembly and is SEMANTICALLY
// COMPLETE; what is left is layout/allocation:
//
// 1. CR save (4 words, doc-28). WANT's prologue has `mfcr r12` + `stw r12,0x3c(r1)`
//    and its epilogue `lwz r12,0x3c(r1)` + `mtcrf 8,r12`: flag1's `cmpwi cr4`
//    sits at 0x8005AEF4 and its only user is the `beq cr4` at 0x8005B038, ~50
//    instructions and 8 calls later, so the compare is cached in a CR field.
//    WANT has all four callee-saved regs spoken for (r31=arg0, r30=&colour,
//    r29=fn_800F0AFC result, r28=flag2), so flag1 could NOT get a register.
//    My C makes GCC keep BOTH flags in callee-saved regs instead (r26/r27) and
//    to do that it keeps &sp18 in r29 and &sp8 in r25 — i.e. it creates the
//    register pressure that WANT doesn't have. No mfcr/mtcrf, no cr4 cache.
//    Best lead: stop keeping those two addresses live (recompute them) so the
//    pool runs out at the right point.
//
// 2. Stack slots. WANT: 0x8=sp8, 0x18=sp18, 0x1c/0x20/0x24=sp1C/sp20/sp24,
//    0x28=colour word, 0x2c=sp2C, 0x30=sp30, 0x34=sp34 (0xc..0x14 and 0x38 are
//    unused). My object: sp1C@0xc, sp24@0x14, colour@0x18, sp34@0x24, sp18@0x28
//    — every slot is exactly 4 bytes below WANT's except sp18, which GCC 2.95's
//    local-priority allocator puts LAST (highest) because it is written once.
//    Declaration order (sp34, sp30, sp2C, colour, sp24, sp20, sp1C, sp18, sp8)
//    is already the reverse of WANT's address order; what is missing is the
//    3-word pad between sp18 and sp8 that WANT's unused 0xc..0x14 implies.
//
// 3. The 4 words at 0x8005B058..0x8005B064, which block all alignment after
//    them: `beq cr1eq,+8 / fcmpu cr1,f6,f3 / beq cr1eq,+0x10 / fcmpu cr1,f6,f3`.
//    They are NOT multiplies (opcode 63 with XO=8 is `fcmpu`; `fmuls` is XO=50
//    — an easy misread here). They are dead float comparisons between f3 and
//    f6, registers this function never writes, guarded by CR1 — which the
//    `subfic r9,r3,0 / adde r3,r9,r3` at 0x8005B030 set to `(sp30 ^ QB_POINT) == 0`
//    (recipe 100). They sit immediately in front of `lfs f0,0x1c(r1); fmuls
//    f0,f0,f13`, the value stored to +0x24, so the shape is a conditional store
//    `ptr->f_0x24 = cond ? (<cmp> ? already-in-f0 : already-in-f0) : sp1C*0.01f;`
//    whose true arm selects values that are already in f0, i.e. the original
//    reads an uninitialised f32 there. m2c rendered the whole block as `if (0)`.
//    Ruled out: asking ngccc for dead float code — a probe file shows GCC 2.95
//    deletes `if (c) x = x*y;` and `(0-t)+t` outright, so the survival of these
//    two dead compares depends on a context I could not find.
//
// Also ruled out: `ContainsFlag(...) ^ 1` instead of `!ContainsFlag(...)`
// (13.70% / 584B object — `!` is better). WANT's `xori r3,r3,1` + `cmpwi cr4,r3,0`
// is the `!` shape, so the polarity is right; only the allocation differs.
//
// WIP DRAFT (non-matching) — hand-derived from the 0x8005AEC4 disassembly.
// family=m2c range=0x8005AEC4-0x8005B11C size=600B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATE 2026-10-03 (a67): semantics rebuilt from the disassembly, not the
// m2c draft: arg0 was missing from the two ContainsFlag calls, the QB hashes
// are real constants (qb_constants.h), `if (0)` became `if (!exclude_skater)`,
// the s8 colour word became an s32 written through u8 puns (matching the
// lwz/stw copy), and the struct fields at 0x1C/0x20/0x24 are floats (stfs).
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x1C];
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
} Unk_LightVol;
s32 ContainsFlag(CStruct *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetArray(CStruct *, s32, void *, s32);
s32 GetChecksum_2(void *, s32, s32 *, s32);
s32 fn_800F0AFC(CStruct *);
void fn_800F078C(CStruct *, void *);
s32 fn_801293FC(CStruct *, s32);
Unk_LightVol *fn_800596E4();
Unk_LightVol *fn_800598C8(void *, void *, s32 *, s32, f32, f32);
extern f32 lbl_8029350C; // 100.0f
extern f32 lbl_80293510; // 300.0f
extern f32 lbl_80293514; // 0.01f
extern f32 lbl_80293518; // 0.0f
extern f32 lbl_8029351C; // 1.0f
extern f32 lbl_80293520; // 1.0e10f
void *fn_8005AEC4(CStruct *arg0) {
    s32 sp34;
    s32 sp30;
    CStruct *sp2C;
    s32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    s32 sp18;
    s32 sp8;
    s32 temp_r29;
    s32 temp_r28;
    s32 exclude_skater;
    Unk_LightVol *var_r3;
    exclude_skater = !ContainsFlag(arg0, QB_EXCLUDESKATER);
    temp_r28 = !ContainsFlag(arg0, QB_EXCLUDELEVEL);
    temp_r29 = fn_800F0AFC(arg0);
    fn_800F078C(arg0, &sp8);
    sp20 = lbl_80293510;
    sp1C = lbl_8029350C;
    sp24 = lbl_80293510;
    GetFloat(arg0, QB_BRIGHTNESS, &sp1C, 0);
    GetFloat(arg0, QB_INNERRADIUS, &sp20, 0);
    GetFloat(arg0, QB_OUTERRADIUS, &sp24, 0);
    ContainsFlag(arg0, QB_CREATEDATSTART);
    *(u8 *)&sp28 = -1;
    *((u8 *)&sp28 + 2) = -1;
    *((u8 *)&sp28 + 1) = -1;
    *((u8 *)&sp28 + 3) = 0;
    sp2C = 0;
    GetArray(arg0, QB_COLOR, &sp2C, 0);
    if (sp2C != 0) {
        *(u8 *)&sp28 = fn_801293FC(sp2C, 0);
        *((u8 *)&sp28 + 1) = fn_801293FC(sp2C, 1);
        *((u8 *)&sp28 + 2) = fn_801293FC(sp2C, 2);
    }
    sp30 = QB_POINT;
    GetChecksum_2(arg0, QB_LIGHT_TYPE, &sp30, 0);
    var_r3 = (sp30 == QB_POINT);
    if (exclude_skater) {
        var_r3 = fn_800596E4();
        if (var_r3 != NULL) {
            var_r3->unk0x2C = temp_r29;
            var_r3->unk0x24 = sp1C * lbl_80293514;
            var_r3->unk0x28 = sp28;
            var_r3->unk0x1C = sp24;
            if (sp24 != lbl_80293518) {
                var_r3->unk0x20 = lbl_8029351C / sp24;
            } else {
                var_r3->unk0x20 = lbl_80293520;
            }
            var_r3->unk0x30 = 1;
        }
    }
    if (temp_r28 != 0) {
        sp34 = 0;
        GetArray(arg0, QB_EXCLUDEGEOMETRY, &sp34, 0);
        sp18 = sp28;
        var_r3 = fn_800598C8(temp_r29, &sp8, &sp18, sp34, sp1C, sp24);
    }
    return var_r3;
}