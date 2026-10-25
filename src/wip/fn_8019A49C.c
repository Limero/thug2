// family=m2c range=0x8019A49C-0x8019AA58 size=1468B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// HAND-REBUILD 2026-10-07 , replacing the
// machine-generated m2c husk.  The husk modelled `sp8`/`sp198` as file-scope
// `static s32` (so every access was a lis+lwz global pair) and declared
// `Unk_B97C1601`'s float slots as `s32`; it could therefore never reproduce
// retail's `stwu r1,-0x2e0` / `stmw r14,0x230` / `stfd f19..f31` prologue.
// This body is decoded instruction-by-instruction from
// build/b34pkt/fn_8019A49C.psdiff.txt (WANT column) and
// build/b34pkt/fn_8019A49C.rb.diff.txt (WANT vs the *compiled* result).
//
// ===========================================================================
// — the frame/prologue now compiles IDENTICALLY to
// retail (`stwu r1,-0x2e0` + `stfd f19..f31` all OK); the remaining diff was
// traced to ONE struct bug plus two source-shape bugs:
// ===========================================================================
//  BUG 1 (the cascade): `Entry` was 0x20 bytes, retail's stride is 0x24.
//    Proof from the want column, independent of any guess: at A5D8 the
//    entry score-array base is derived as arg0 plus 0x20 into r21, and at
//    A5DC the entry gate base as arg0 plus 0x1c into r17; at A714 the
//    index is scaled by a multiply with stride 0x24 into r30 (not 0x20);
//    at A730 the gate is stored indexed as arg0 plus 0x1C plus 0x24 times
//    k, and at A920 a score is stored indexed as arg0 plus 0x20 plus
//    0x24 times k plus 4 times ra.
//    With entry[] at +0xC that means gate = +0x10 and score = +0x14 *and*
//    4 further bytes at +0x20..0x23 that this function never touches.  The
//    0x20-byte struct made every `arg0->0x1xx` store land 0x20 low, which is
// exactly what the earlier object showed (`stfs f30,0x10c(r27)` where the
//    want is `stfs f27,0x12c(r28)`; `stw r0,0x164(r27)` for 0x184; the judge
//    strings at 0x140..0x150 for 0x160..0x170; and `slwi ..,5` + `add` for
//    `mulli 0x24`).  `unk0x20` below is that trailing word.
//  BUG 2 (arg copies): retail copies the three float arguments into locals
//    BEFORE storing them (`fmr f27,f1` / `fmr f24,f2` / `fmr f23,f3` at
//    A4EC/A4F0/A4F8) and then *stacks onto those same registers*
// (`fadds f27,f27,f1` at A694). The first attempt wrote `arg0->f0x12C = farg0;`
//    and a single `var_f27 = farg0 + Mth_PlusOrMinus(...)`, so ngccc had to
//    keep its own copy in f30/f29/f26 and pushed everything one register
//    over.  Now: `var_f27 = farg0;` … `var_f27 = var_f27 + …`.
//  BUG 3 (missing call): the three-score loop MUST call Mth_PlusOrMinus —
//    retail A85C/A860 is `lfs f1,-0x553c(r18)` (= lbl_802AAAC4, 1.9f) then
// `bl 0x80003594`. The first attempt wrote the constant `lbl_802AAAC4` directly,
//    dropping a `lfs`+`bl`+`fadds` triple from the object (part of the 24B
//    length shortfall).
//
// Verified-correct spellings kept from round 1 (they compile OK):
//   * the empty `li r0,8 / mtctr r0 / bdnz .` loops at A958 and A998 are REAL
//     retail code (`W:bdnz 0x8019a958` / `W:bdnz 0x8019a9a0` — a self-branch),
//     rendered as empty `for (n = 0; n < 8; n++) {}`.
//   * `Script_GenerateCRC` must stay UNPROTOTYPED: retail's first call site
//     passes no argument (it leaves the previous call's r3 alone).
//   * the `(s32)(f32)(s32)` double round trip (fctiwz / stfd / lwz / xoris /
//     stw / lfd / fsub / frsp / fctiwz) is real, not an m2c artifact.
//
// STILL OPEN (needs a compiler, cannot be decided here):
//   1. the callee-saved GPR set: retail `stmw r14,0x230` (18 regs), the
// earlier object `stmw r17,0x23c` (15). Retail's extra three are the
//      label pages r14 (2.0f, live A52C..A7EC) and r18 (1.9f, A534..A85C) and
//      the hoisted `&sp1BC` (r15, A548) / `&sp1B8` (r16, A53C) — all live
//      across the calls of the entry loop.  Fixing BUG 1/3 may make GCC hoist
//      them again (they are loop-invariant there); if not, the lever is to
//      take the addresses/constants far enough from their uses that CSE is
//      forced to keep them live across the loop.
//   2. `lwzx`/`stwx` OPERAND ORDER in the two shuffles: retail emits
//      `lwzx r0, r29, r3` (array base first) for `sp198[j]` but
//      `lwzx r9, r31, r30` (byte offset first) for `*(s32 *)((char *)base +
// off)`, and the earlier object has both in the other order. Left as the
//      m2c spelling until the cascade above is measured.
//   3. the stray `stw r29,0x1c(r28)` at A66C (a value-7 store into
//      entry[0].gate that no source statement obviously produces, 1 word).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// ---- .rodata2 float pool, src/r2d_802AAAB4.c ---------------------------------
// `const` is the established correct declaration for these data:float rodata2
// symbols (recipes 362/16272, and the load-bearing case documented in
// src/fn_8019F938.c).
extern const f32 lbl_802AAAB8;   // 2.0f
extern const f32 lbl_802AAABC;   // 0.1f
extern const f32 lbl_802AAAC0;   // 0.125f
extern const f32 lbl_802AAAC4;   // 1.9f
extern const f32 lbl_802AAAC8;   // 0.49999899f
extern const f64 lbl_802AAAD0;   // 2^52 + 2^31 (the int->double convert dance)
extern s32 lbl_80305EFC;         // the players/leader-board manager object

// ---- callees (all signatures lifted from the promoted siblings) --------------
s32 fn_801A5D88(s32);                  // src/fn_801A5D88.c
s32 fn_801A5C04(s32);                  // src/fn_801A5C04.c   (slot count)
s32 fn_801A5C40(s32, s32);             // src/fn_801A5C40.c
s32 fn_801A572C(s32);                  // src/fn_801A572C.c
s32 fn_801A5774(s32);                  // src/fn_801A5774.c
s32 fn_801A5C0C(s32, s32);             // src/fn_801A5C0C.c
s32 fn_801A5DAC(s32, s32);             // src/fn_801A5DAC.c
s32 fn_801A5848(s32);                  // src/fn_801A5848.c
s32 fn_8012935C(s32, s32);             // src/fn_8012935C.c (takes the GetArray slot)
s32 fn_8012591C(s32, s32);             // src/fn_8012591C.c
s32 GetArray(CStruct *, s32, s32 *, s32);   // @0x801285A4 src/fn_801285A4.c
s32 GetString(CStruct *, s32, s32 *, s32);  // @0x801280E0 src/fn_801280E0.c
s32 fn_800093A4(CStruct *);            // src/fn_800093A4.c
s32 fn_80009314(CStruct *, void *);    // src/fn_80009314.c
// 0x80131A88.  The retail call sites pass NO argument at the first call and
// leave the previous call's r3 in place at the second, so the declaration must
// stay unprototyped (a `(s32)` prototype makes ngccc materialise `li r3,0`).
s32 Script_GenerateCRC();
void fn_8019B2A0(void *);              // @0x8019B2A0 (this TU)
s32 Mth_Rnd2(s32);                     // @0x8000353C src/rng.c
f32 Mth_PlusOrMinus(f32);              // @0x80003594 src/fn_80003594.c

// ---- the object (replaces Unk_B97C1601 for this function) --------------------
// entry[i] is at 0xC + 0x24*i.  Only these fields are ever touched by this
// function; fn_8019AA88 ("Rec") overlaps the same bytes with a looser model.
// The trailing `unk0x20` is load-bearing: it is what makes sizeof(Entry) 0x24
// so `entry[i]` compiles to `mulli ..,0x24` (retail A714) instead of the
// 0x20-stride `slwi ..,5; add` the earlier body produced.
typedef struct {
    s32 name[3];    /* +0x00: the 0xC-byte text object handed to fn_80009314 */
    s32 unk0x0C;    /* +0x0C: untouched here */
    s32 gate;       /* +0x10: sp198[] value (0 for entry[0]) */
    s32 score[3];   /* +0x14,+0x18,+0x1C: the int score triple */
    s32 unk0x20;    /* +0x20: never read here; pads the stride to 0x24 */
} Entry;            /* 0x24 */

typedef struct {
    char pad0x0[0x4];
    CStruct *unk0x4;    /* +0x04: the array/text context for GetArray/GetString */
    s32 unk0x8;         /* +0x08: slot index, set to -1 by this function */
    Entry entry[8];     /* +0x0C, 8 * 0x24 -> ends at 0x12C */
    f32 f0x12C;         /* +0x12C: the 7 float thresholds, farg0..farg6 */
    f32 f0x130;
    f32 f0x134;
    f32 f0x138;
    f32 f0x13C;
    f32 f0x140;
    f32 f0x144;
    char pad0x148[0x18];
    s32 unk0x160;       /* +0x160..+0x170: the five judge strings */
    s32 unk0x164;
    s32 unk0x168;
    s32 unk0x16C;
    s32 unk0x170;
    char pad0x174[0x10];
    s32 unk0x184;       /* +0x184: the "already scored" flag */
} Comp;

void fn_8019A49C(Comp *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                 f32 farg4, f32 farg5, f32 farg6) {
    // The local region is pinned by declaration order: retail addresses r1+0x08
    // (sp8), r1+0x198 (sp198) and r1+0x1B8/0x1BC (sp1B8/sp1BC), and GCC's
    // float<->int conversion temp lands on r1+0x228.
    // these are SEPARATE locals, not one `fr` struct. Retail never
    // addresses sp198 off the sp8 base: it hoists `&sp198[0]` into a
    // callee-saved register (r20, live from A504 to A730) and folds the index
    // as a register add — `addi r9,r20,0x18` for &sp198[6] and
    // `lwzx r9,r31,r30` for the shuffle. With one struct the earlier body
    // instead folded `sp198[j]` as `0x190(r31)` off a hoisted `&sp8` (r22),
    // which is also what cost the extra callee-saved register and shifted the
    // whole entry block (r27 vs r28, f30 vs f27, ...).
    s32 sp8[8];               /* r1+0x008 */
    char pad0x28[0x170];      /* r1+0x028: retail's untouched local region */
    s32 sp198[8];             /* r1+0x198 */
    s32 sp1B8;                /* r1+0x1B8 */
    s32 sp1BC;                /* r1+0x1BC */
    char pad0x1C0[0x68];      /* r1+0x1C0: retail's convert-temp area */
    Entry *entry;
    s32 *p;
    s32 *q;
    s32 *base;
    s32 temp_r24;   /* the manager object */
    s32 temp_r26;   /* slot count */
    s32 temp_r31;   /* one manager slot */
    s32 temp_r30;   /* first Script_GenerateCRC result */
    s32 var_r25;    /* number of surviving slots */
    s32 var_r27;
    s32 var_r31;
    s32 n;
    s32 j;
    s32 s;
    s32 off;
    s32 ra;
    s32 rb;
    f32 var_f27;
    f32 var_f24;
    f32 temp_f23;
    f32 var_f31;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f28;

    temp_r24 = lbl_80305EFC;
    // BUG 2: the three jittered thresholds are copies of the arguments from
    // the very start (retail `fmr f27,f1` / `fmr f24,f2` / `fmr f23,f3`), and
    // the object stores write those copies, not the incoming registers.
    var_f27 = farg0;
    var_f24 = farg1;
    temp_f23 = farg2;
    arg0->f0x12C = var_f27;
    arg0->f0x130 = var_f24;
    arg0->f0x134 = temp_f23;
    arg0->f0x138 = farg3;
    arg0->f0x13C = farg4;
    arg0->f0x140 = farg5;
    arg0->f0x144 = farg6;
    arg0->unk0x184 = 0;
    var_r25 = 0;
    var_r27 = 0;
    // r3 of this fn_801A5D88 call feeds fn_801A5848 directly (retail has no
    // second `bl 0x801a5d88`), so the two calls are nested.
    fn_80009314((CStruct *)((char *)arg0 + 0xC),
                (void *)fn_801A5848(fn_801A5D88(temp_r24)));

    temp_r26 = fn_801A5C04(temp_r24);
    if (var_r25 < temp_r26) {   /* capacity guard; retail: cmpw r25,r26 / bge */
        p = sp8;
        for (var_r27 = 0; var_r27 < temp_r26; var_r27++) {
            temp_r31 = fn_801A5C40(temp_r24, var_r27);
            if ((fn_801A572C(temp_r31) != 0) && (fn_801A5774(temp_r31) == 0)) {
                fn_800093A4((CStruct *)((char *)arg0 + 0xC));
                temp_r30 = Script_GenerateCRC();
                if (temp_r30 != Script_GenerateCRC(fn_801A5848(temp_r31))) {
                    *p = var_r27;
                    var_r25 += 1;
                    p += 1;
                }
            }
        }
    }
    if (var_r25 > 0) {
        // Fisher-Yates against the same array through two pointers (retail
        // walks one pointer and indexes the other).
        base = sp8;
        q = sp8;
        for (n = var_r25; n != 0; n--) {
            j = Mth_Rnd2(var_r25);
            s = *q;
            *q = base[j];
            base[j] = s;
            q += 1;
        }
    }
    // sp198 = {1,2,3,4,5,6,7} written descending from index 6.
    p = sp198 + 6;
    for (n = 7; n != 0; n--) {
        *p = n;
        p -= 1;
    }
    // In-place shuffle of sp198 against itself; retail keeps the running
    // element as a raw byte offset (`lwzx r9,r31,r30`).
    off = 0;
    for (n = 7; n != 0; n--) {
        j = Mth_Rnd2(7);
        s = *(s32 *)((char *)sp198 + off);
        *(s32 *)((char *)sp198 + off) = sp198[j];
        sp198[j] = s;
        off += 4;
    }
    // entry[0].gate = 0 and entry[0].score[0..2] = 0 (three stores descending
    // from score[2]).
    arg0->entry[0].gate = 0;
    p = &arg0->entry[0].score[2];
    for (n = 3; n != 0; n--) {
        *p = 0;
        p -= 1;
    }

    // BUG 2: jitter the same three locals in place (retail `fadds f27,f27,f1`).
    var_f27 = var_f27 + Mth_PlusOrMinus(lbl_802AAAB8);
    var_f24 = var_f24 + Mth_PlusOrMinus(lbl_802AAAB8);
    temp_f23 = temp_f23 + Mth_PlusOrMinus(lbl_802AAAB8);
    if (var_f24 >= temp_f23) {
        var_f24 = temp_f23 - lbl_802AAABC;
    }
    if (var_f27 >= var_f24) {
        var_f27 = var_f24 - lbl_802AAABC;
    }

    for (var_r31 = 0; var_r31 <= 6; var_r31++) {
        var_r27 = var_r31 + 1;
        entry = &arg0->entry[var_r27];
        entry->gate = sp198[var_r31];
        if (GetArray(arg0->unk0x4, QB_LEADER_BOARD_NAMES, &sp1B8, 0) != 0) {
            fn_80009314((CStruct *)entry, (void *)fn_8012935C(sp1B8, var_r31));
        } else {
            fn_80009314((CStruct *)entry,
                        (void *)fn_801A5848(fn_801A5DAC(
                            temp_r24, fn_801A5C0C(temp_r24, sp8[var_r31]))));
        }
        if (var_r31 == 0) {
            var_f31 = temp_f23;
        } else if (var_r31 == 1) {
            var_f31 = var_f24;
        } else {
            var_f31 = var_f27;
            if (var_r31 != 2) {
                temp_f31 = var_f27 * lbl_802AAAC0;
                var_f31 = (var_f27 - temp_f31) + Mth_PlusOrMinus(temp_f31);
                if (var_f31 >= var_f27) {
                    var_f31 = var_f27 - lbl_802AAABC;
                }
            }
        }
        temp_f30 = var_f31 + Mth_PlusOrMinus(lbl_802AAAB8);
        temp_f31 = (var_f31 + var_f31) - temp_f30;
        var_f28 = temp_f30;
        if (temp_f31 < temp_f30) {
            var_f28 = temp_f31;
        }
        ra = Mth_Rnd2(3);
        do {
            rb = Mth_Rnd2(3);
        } while (rb == ra);
        p = &entry->score[0];
        for (n = 3; n != 0; n--) {
            // BUG 3: the `lbl_802AAAC4` (1.9f) term is an actual call, not a
            // constant — retail A85C `lfs f1,-0x553c(r18)` + A860 `bl`.
            *p = (s32)(f32)(s32)((var_f28 - lbl_802AAAB8)
                                 + Mth_PlusOrMinus(lbl_802AAAC4) + lbl_802AAAC8);
            p += 1;
        }
        entry->score[ra] = (s32)(f32)(s32)(temp_f30 + lbl_802AAAC8);
        entry->score[rb] = (s32)(f32)(s32)(temp_f31 + lbl_802AAAC8);
    }
    // Retail's empty 8-count loop (li r0,8 / mtctr r0 / bdnz .).
    for (n = 0; n < 8; n++) {
    }
    fn_8019B2A0(arg0);
    if (GetString(arg0->unk0x4, QB_FIRST_PLACE_NAME, &sp1BC, 0) != 0) {
        fn_80009314((CStruct *)((char *)arg0 + 0xC), (void *)sp1BC);
    }
    // Retail's second empty 8-count loop.
    for (n = 0; n < 8; n++) {
    }
    arg0->unk0x160 = fn_8012591C(QB_COMP_STR_JUDGE1, 0);
    arg0->unk0x164 = fn_8012591C(QB_COMP_STR_JUDGE2, 0);
    arg0->unk0x168 = fn_8012591C(QB_COMP_STR_JUDGE3, 0);
    arg0->unk0x16C = fn_8012591C(QB_COMP_STR_JUDGE4, 0);
    arg0->unk0x170 = fn_8012591C(QB_COMP_STR_JUDGE5, 0);
    arg0->unk0x8 = -1;
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// PARKED 2026-10-07: first divergence is the prologue — want
//   `stwu -0x2e0 / stfd f19..f31 / stmw r14` with locals r1+8..~0x228; got
//   `stwu -0x110 / stfd f21..f31`.  The m2c body modelled its two scratch arrays
//   as file-scope statics (every access a global lis+lwz).  Still to decode: want
//   0x14C-0x1A0 (the real 8x0x24 table) and the f32 heap stores the m2c
//   `(s32)(f32)(f64)(s32)` casts hide.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
