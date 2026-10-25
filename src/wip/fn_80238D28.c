// WIP DRAFT (non-matching) — hand reconstruction of the guard + 4-way kind
// dispatch + int->double->float core (see NOTE at the end).
// family=m2c range=0x80238D28-0x80239224 size=1276B
// RE-MEASURED 2026-10-17: DIFF 0.3% — first ever score of the hand rebuild
// (got 812B vs want 1276B, 464B short; want frame 0x108 with stfd f23-f31 +
// stmw r17, got 0x80 with stfd f29-f31 + stmw r14). The rebuild is missing
// ~40% of the code (likely folded float arms / collapsed dispatch) AND sits
// in the FPR-saving blocked class (recipes §4c, 9 FPRs). No dummy dual-test
// run. Parking as-is; needs a from-scratch FPR-frame pass, out of scope here.
// PARKED 2026-10-06: this slice ran; the body is the hand
// from-WANT reconstruction and could not be re-measured (no compiler in the
// worker slice). This pass fixed ONE concrete arity defect: fn_802413C0 is the
// 2-arg mixed-ABI (s32, f32) setter (recipes: "fn_802413C0 mixed-ABI (s32,f32)",
// and src/wip/fn_802413C0.c declares (Unk_C7387A53 *, f32)) — the WANT leaves
// the fn_8022D6E4 result in r3 and puts the quotient in f1, so the call must
// pass `rc` as the first argument, not just the float.
// Blocker (unchanged): the f31 reload of .rodata2 0x802B0544 at 0x80239128
// (two-read CSE/LICM decision) plus the 9-FPR / 0x108 8-aligned frame.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.2% ([5]rev->2.2%).
// REBUILT 2026-10-06 by hand from the want disassembly: the old m2c body read
// `*((s32 *)arg1 + 0xC + var_r26)` (s32-scaled index added to a byte
// displacement) and used an uninitialised temp_r3_2 — i.e. it could not
// describe this function at all. The body below reproduces the guard record
// (6-byte blob), the three parallel s32 arrays, the loop and the four
// kind-dispatch arms.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// .rodata2 floats: 0x802B0544/548/54C are consecutive, 0x802B0D50/54/58 too.
extern f32 lbl_802B0544;
extern f32 lbl_802B0548;
extern f32 lbl_802B054C;
extern f32 lbl_802B0D50;
extern f32 lbl_802B0D54;
extern f32 lbl_802B0D58;

// The per-item record: 6 bytes, copied as a 4-byte word + a halfword
// (lwz/lhz), but addressed byte-wise by the four dispatch arms (note b1 is
// loaded with lbz+extsb => signed, the others are plain lbz => unsigned).
typedef union {
    struct {
        s32 w0;
        u16 w4;
    } p;
    struct {
        u8 b0;
        s8 b1;
        u8 b2;
        u8 b3;
        u8 b4;
        u8 b5;
    } b;
} Rec6;

s32 fn_80237D14(Unk_673C6403 *arg0, Rec6 *rec, s32 a2, s32 a3, s32 a4);
void fn_80243318(s32 *guard, s32 v);
void fn_80243320(s32 *guard, s32 v);
void fn_8024336C(s32 *guard);
void fn_802432A0(void);
Unk_4A174A22 *fn_802416F8(void);
f32 fn_802434B0(Unk_C7387A53 *arg1, s32 idx);
s32 fn_8022D6E4(s32 arg0, f32 *vec, s32 flag, f32 scale);
void fn_802413C0(s32 arg0, f32 farg0);
s32 fn_80243788(s32 handle);
void fn_802437C0(s32 handle, s32 rc, Unk_4A174A22 *obj, s32 id);
void fn_80243840(s32 handle, s32 rc, Unk_4A174A22 *obj, s32 id);
void fn_80243924(s32 handle, s32 id, Unk_C7387A53 *arg1);

s32 fn_80238D28(Unk_673C6403 *arg0, Unk_C7387A53 *arg1) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    Rec6 rec;
    s32 sp8;
    u8 *walk;
    s32 *arrA;
    s32 *arrB;
    s32 i;
    s32 flag;
    s32 handle;
    s32 rc;
    Unk_4A174A22 *obj;
    f32 f27;

    handle = fn_80243788(arg0->unk0x177C8);
    if (handle == -1) {
        return 0;
    }
    walk = (u8 *)arg1;
    arrA = (s32 *)((u8 *)arg1 + 0x14);
    arrB = (s32 *)((u8 *)arg1 + 0x1C);
    for (i = 0; i < arg1->unk0x48; i++) {
        walk[3] = 1;
        walk[4] = 1;
        walk[5] = 1;
        rec.p.w0 = *(s32 *)walk;
        rec.p.w4 = *(u16 *)(walk + 4);
        fn_80243318(&sp8, fn_80237D14(arg0, &rec, 0, 0, 1));
        if (sp8 == 0) {
            fn_80243320(&sp8, 2);
            return 0;
        }
        flag = 0;
        fn_8024336C(&sp8);
        fn_802432A0();
        obj = fn_802416F8();
        obj->unk0x8 |= 0x1000;
        *(s32 *)walk = obj->unk0x0;
        *(u16 *)(walk + 4) = obj->unk0x4;
        rec.p.w0 = obj->unk0x0;
        rec.p.w4 = obj->unk0x4;
        f27 = fn_802434B0(arg1, i);
        switch (((s32 *)((u8 *)arg1 + 0xC))[i]) {
        case 0:
            flag = 1;
            sp18 = (f32)(rec.b.b0 + rec.b.b3) * lbl_802B0544
                 - lbl_802B0544 * lbl_802B0D50 - lbl_802B0D54;
            sp20 = (f32)(rec.b.b2 - arrB[i]) * lbl_802B054C
                 + f27 * lbl_802B0D50 - lbl_802B054C;
            sp1C = (f32)rec.b.b1 * lbl_802B0548;
            break;
        case 1:
            sp18 = (f32)(rec.b.b0 - arrB[i]) * lbl_802B0544
                 + f27 * lbl_802B0D50 - lbl_802B0544;
            sp20 = (f32)rec.b.b2 * lbl_802B054C
                 - lbl_802B054C * lbl_802B0D50 + lbl_802B0D54;
            sp1C = (f32)rec.b.b1 * lbl_802B0548;
            break;
        case 2:
            flag = 1;
            sp18 = (f32)rec.b.b0 * lbl_802B0544
                 - lbl_802B0544 * lbl_802B0D50 + lbl_802B0D54;
            sp20 = (f32)(rec.b.b2 - arrA[i]) * lbl_802B054C
                 + f27 * lbl_802B0D50 - lbl_802B054C;
            sp1C = (f32)rec.b.b1 * lbl_802B0548;
            break;
        case 3:
            sp18 = (f32)(rec.b.b0 - arrA[i]) * lbl_802B0544
                 + f27 * lbl_802B0D50 - lbl_802B0544;
            sp20 = (f32)(rec.b.b2 + rec.b.b5) * lbl_802B054C
                 - lbl_802B054C * lbl_802B0D50 - lbl_802B0D54;
            sp1C = (f32)rec.b.b1 * lbl_802B0548;
            break;
        }
        sp18 = sp18 - lbl_802B0544 * lbl_802B0D58 * lbl_802B0D50;
        sp20 = sp20 - lbl_802B054C * lbl_802B0D58 * lbl_802B0D50;
        rc = fn_8022D6E4(arg0->unk0x0, &sp18, flag, f27);
        fn_802413C0(rc, f27 / lbl_802B0544);
        if (i == 0) {
            fn_802437C0(arg0->unk0x177C8, rc, obj, handle);
        } else {
            fn_80243840(arg0->unk0x177C8, rc, obj, handle);
        }
        fn_80243320(&sp8, 2);
        walk += 6;
    }
    arg1->unk0x4C = handle;
    fn_80243924(arg0->unk0x177C8, handle, arg1);
    return 1;
}

// NOTE (2026-10-06, hand reconstruction — parked, not a match):
// What the want says, and what this body reproduces:
//   * guard: handle = fn_80243788(arg0->unk0x177C8); == -1 -> return 0.
//   * per-item guard object sp8 (r1+8) driven by fn_80243318(&sp8, ...) /
//     fn_8024336C(&sp8) / fn_80243320(&sp8, 2); sp8==0 -> cleanup, return 0.
//   * walk is a 6-byte-stride u8 walker over arg1 (addi r29,r29,6); three
//     parallel s32 arrays at arg1+0xC (rematerialised per iteration), +0x14
//     and +0x1C (hoisted into r21/r20); count at +0x48, out slot +0x4C.
//   * the four arms all end with the same two statements (`sp20 = ...;
//     sp1C = (f32)rec.b.b1 * <0x802B0548>;`) which GCC cross-jumped into the
//     shared block at 0x80239114; the default arm skips that block and jumps
//     straight to 0x80239128.
//   * every int operand is converted with the 0x43300000/^0x8000 int->double
//     bias idiom + frsp (compiler-generated for `(f32)int`), and the six
//     .rodata2 floats are loop-invariant loads LICM hoists into the preheader.
// Remaining mismatches (why it is parked):
//   1. 0x80239128 reloads f31 from 0x802B0544 even though f28 already holds it
//      from the preheader (0x80238DBC); the only way that happens at source
//      level is a *second* read of that global inside the loop body (after the
//      calls at 0x8024336C/802432A0/802416F8/802434B0, so CSE cannot merge
//      them). This body reads the global there, but ngccc's CSE/LICM decision
//      on the two reads is a scheduling-level coin flip.
//   2. Register allocation of the nine live FPRs / the 0x108 frame: the want
//      saves f23-f31 and r17-r31 (stmw) — frame 0x108 is 8-aligned, i.e. the
//      issue-01 class, so the sweep must dual-test with an injected
//      `volatile double _dummy;` before believing any score.
//   3. Array-base materialisation: the want rematerialises arg1+0xC inside the
//      loop (addi r9,r27,0xc at 0x80238EA0) but keeps arg1+0x14/+0x1C in
//      r21/r20; arrA/arrB are locals here and arg1+0xC is written inline, but
//      the allocator may still pick the other split.
//   4. Local stack layout is believed exact: sp8@0x8, rec@0x10, sp18@0x18,
//      sp1C@0x1C, sp20@0x20 (declaration order = descending address, verified
//      against the want's stw/sth/stfs offsets).
// 2026-10-06 re-audit:
//   * fn_802413C0 callee arity FIXED (2-arg mixed-ABI (s32,f32); see header) —
//     the previous body passed only the float, leaving r3 undefined at the
//     call, whereas the WANT leaves the fn_8022D6E4 result in r3 and the
//     quotient in f1.
//   * all four dispatch arms re-derived term-by-term from the WANT's
//     fmsubs/fmadds/fsubs chains (f28=+0x544, f29=+0x54C, f26=+0xD50,
//     f24=+0xD54, f23=+0xD58, f25=+0x548):
//       arm0: (b0+b3)*f28 - f28*f26 - f24 ; (b2-arrB[i])*f29 + f27*f26 - f29
//       arm1: (b0-arrB[i])*f28 + f27*f26 - f28 ; b2*f29 - f29*f26 + f24
//       arm2: b0*f28 - f28*f26 + f24 ; (b2-arrA[i])*f29 + f27*f26 - f29
//       arm3: (b0-arrA[i])*f28 + f27*f26 - f28 ; (b2+b5)*f29 - f29*f26 - f24
//     sp1C is (f32)(s8)b1 * 0x802B0548, computed in the shared block from the
//     same int->double bias f0 the arms end on (0x80239114 stores sp20 first,
//     then sp1C at 0x8023911C, then re-loads 0x802B0544/0x802B054C and adjusts).
//   * NOT modelled: the WANT's `mr r7,r8` / `mr r6,r8` (and arm2's
//     `mr r8,r10` / `mr r7,r10`) argument-register copies interleaved into each
//     arm's int->double text. They read r8/r10 with no visible producer in the
//     function, so they look like compiler shuffling of a value this body does
//     not name (8 words). Inventing a source for them would be guessing.
//   * frame 0x108 (stfd f23..f31 + stmw r17) is 8-aligned => issue-01 class;
//     any sweep verdict must be the dual-tested `volatile double _dummy;` one.
// No inline asm and no whole-body transcription: the arms above are the
// source-level float expressions the want's fmsubs/fmadds/fsubs chains imply.
