// PARKED 2026-10-03 (b41): NEAR 74.4% (baseline DIFF 11.6% — UP, not down).
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x8018B6F8
//   got 520B / want 532B (130 of 133 words), 78/133 words byte-identical.
//   Whole body re-derived from the DOL; every remaining diff is instruction
//   ORDER, not a missing/extra operation, except the 3-word tail noted below.
//
// NEW HOUSE FINDING (reusable): m2c's ONE combined mask expression vs several
//   separate `&=` statements decides whether ngccc emits ONE mask op or the
//   retail pair. The want has `and 0xBF5FFFFF / oris 8 / rlwinm(0,5,1) /
//   clrlwi 1 / oris 0x200` = FIVE unmerged read-modify-writes on unk0x70.
//   Written as m2c did — one expression
//     x = ((x & 0xBF5FFFFF) | 0x80000) & 0xC7FFFFFF & 0x7FFFFFFF | 0x2000000
//   GCC's combine folds `& A & B` into `x & (A&B)` and emits
//     lis 0x47ff / ori / and / oris 8 / oris 0x200            (4 ops).
//   Written as separate statements `x &= A; x |= B; x &= C; x &= D; x |= E;`
//   ngccc 3.9.3 does NOT fold that combination (mask 0xC7FFFFFF alone is not
//   representable by the SH=0 rlwinm it builds — recipes §16 "ngccc DROPS the
//   rotate when it materialising a bare x & BIGMASK") and emits EXACTLY the
//   retail 5 ops. Measured constants (all m2c originals, all correct):
//     Measured constants (all m2c originals, all correct): the 0xBF5FFFFF
//     clear builds a load-immediate / or-immediate / and trio; the 0xC7FFFFFF
//     clear builds a (0,5,1) rotate-mask; the 0x00080000 set builds an
//     or-immediate-shifted 8; the 0x7FFFFFFF clear builds a clear-left-word-
//     immediate 1; the 0x02000000 set builds an or-immediate-shifted 0x200;
//     and the 0xFBFFFFFF clear builds a (0,6,4) rotate-mask.
//   => for any want with an unmerged AND-chain, SPLIT m2c's `a & b & c`
//      into separate `&=` statements before touching constants or flags.
//
// Other fixes that mattered (all from the disassembly, not from m2c):
//   * 9 spurious `crclr cr1eq`: every callee now declared (Mem_Alloc2,
//     fn_8018B6B8, CStruct_ctor, fn_801908F4, fn_801A6CCC, ContainsFlag were
//     undeclared; CStruct_new/ctor/ContainsFlag need real arity).
//   * `Mem_Alloc2(0xC)` / `fn_8018B6B8` / `CStruct_new(8)` / `CStruct_ctor`
//     are NESTED calls: want has back-to-back `bl; bl` with the 2nd taking
//     the 1st's r3. m2c split them into two statements -> phantom `li r4,0xc`
//     and a lost argument.
//   * `fn_80126FF4` takes TWO args (r3 = ctor result, r4 = arg1) — m2c had 1.
//   * `fn_801908F4` takes TWO args (r3 = Mem_Alloc2(0x14) result, r4 = the
//     reloaded unk0x20) — m2c had 1. So it IS `fn_901908F4(Mem_Alloc2(0x14),
//     arg0->unk0x20)`, not two statements.
//   * `GetChecksum_2` takes FOUR args (r6 = 0 fourth); m2c had 3.
//   * UNITS BUG in m2c: `*(s32 *)((s32 *)(*(void**)lbl_80305EAC) + 0x24)`
//     scales by 4 -> `lwz r3,0x90(r9)`. Want is `lwz r3,0x24(r11)`, i.e. the
//     +0x24 must be a BYTE offset: `((char*)*(void**)lbl_80305EAC) + 0x24`.
//     Grep every m2c `(<T>*)base + 0xNN` for this.
//   * store ORDER (emission == source order here, no reverse): the first run
//     must be 0x4,0x8,0xc,0x10,0x40,0x44,0x14 (ascending, with the lbl store
//     last); m2c's descending guess was the whole 0-11% band.
//
// WHAT IS STILL WRONG (the remaining 26%, all positional):
//   (a) 3-word shortfall + tail shift: the `if/else` chain at the end puts
//       the FIRST then-body (`lwz 0x70 / oris 0x400 / b join`) OUT OF LINE,
//       so everything from there on is 3 words early. WANT has both then-bodies
//       inline (beq/beq) and the ELSE body last. The two then-bodies are
//       byte-identical, so I suspect ngccc's tail-merge/cross-jump is folding
//       them; making them textually distinct (e.g. one via a temp, one
//       writing unk0x70 directly) is the next thing to try.
//   (b) `fn_8018BA34(arg0, arg1)`: GOT emits `mr r4,r28` BEFORE `mr r3,r31`,
//       WANT has `mr r3,r31` first. Arg-position order should be fixed by the
//       prototype, but swapping the prototype's two params did not change it
//       in an earlier probe — try giving the 2nd param a distinct type, or
//       reordering the statement so the call is not adjacent to GetInteger.
//   (c) the lbl_80305EAC page load: WANT `lis r9,-0x7fd0 / lwz r11,0x5eac(r9)`
//       (base r9, value r11, both hoisted to the TOP of the run); GOT uses r11
//       as the base and r9 as the value, emitted mid-run. Same 2 words.
//   (d) `stw r30,0x50(r31)` is emitted FIRST in got's 0x4c/0x28/0x5c/0x60/0x64/
//       0x50 run; want has it last. (d) is a pure store-order fix worth ~1
//       word positionally.
// RULED OUT (do not redo):
//   * ngccc-rotated "equivalent" mask constants (0xCFFFFFFF / 0x80000001 /
//     0xFC000000 give the same rlwinm/clrlwi fields but then GCC folds the
//     whole chain to 2 ops — see the house finding above; m2c's literals are
//     the right ones).
//   * hand-decoding capstone's rlwinm MB/ME: the fields print MSB-first
//     (recipes §115/§16). Guessing masks from them produces constants that
//     fold away.
//   * re-deriving the mask ops from arithmetic (`& ~0x3F`, `& ~1`, `& ~0x7F`):
//     all give different words and all fold.
//
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x8018B6F8-0x8018B90C size=532B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// 2026-10-03 (b41): full re-derivation from the disassembly. Every callee is
// now declared (9 spurious `crclr cr1eq` removed), the three Mem_Alloc2/ctor
// pairs are nested calls (m2c split them into two statements), the two
// `fn_80126FF4` / `fn_801908F4` arities were fixed from the call-site
// registers, `GetChecksum_2` really takes 4 args, the lbl_80305EAC offset was
// a units bug ((s32*)p + 0x24 -> 0x90 bytes; it must be byte +0x24), and the
// 0x70 flag word is 5 separate read-modify-writes (rlwinm 0,5,1 +
// clrlwi 1) instead of one AND-chain of literals.
extern char lbl_802A9690[];
extern char lbl_80305EAC[];
void *Mem_Alloc2(s32);
s32 fn_8018B6B8(s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80126FF4(s32, void *);
s32 fn_801908F4(s32, s32);
s32 fn_801A6CCC(s32);
s32 ContainsFlag(void *, u32);
s32 GetInteger(void *, u32, void *, u32);
s32 fn_8018BA34(void *, void *);
s32 GetChecksum_2(void *, u32, void *, u32);
#include "qb_constants.h"
#include "structs.h"
void *fn_8018B6F8(Unk_9AA07378 *arg0, CStruct *arg1) {
    s32 temp_r3;
    arg0->unk0x4 = (s32)arg0;
    arg0->unk0x8 = 0;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x14 = (s32)lbl_802A9690;
    arg0->unk0x2C = fn_8018B6B8(Mem_Alloc2(0xC));
    arg0->unk0x30 = fn_8018B6B8(Mem_Alloc2(0xC));
    arg0->unk0x70 &= 0xBF5FFFFF;
    arg0->unk0x40 = 0;
    arg0->unk0x70 |= 0x00080000;
    arg0->unk0x44 = 0;
    arg0->unk0x70 &= 0xC7FFFFFF;
    arg0->unk0x48 = 0;
    arg0->unk0x70 &= 0x7FFFFFFF;
    arg0->unk0x54 = 0;
    arg0->unk0x70 |= 0x02000000;
    arg0->unk0x6C = -1;
    arg0->unk0x68 = -1;
    temp_r3 = CStruct_ctor(CStruct_new(8));
    arg0->unk0x20 = temp_r3;
    fn_80126FF4(temp_r3, arg1);
    arg0->unk0x18 = fn_801908F4(Mem_Alloc2(0x14), arg0->unk0x20);
    temp_r3 = CStruct_ctor(CStruct_new(8));
    arg0->unk0x4C = 0x7FFFFFFF;
    arg0->unk0x28 = 0;
    arg0->unk0x5C = 0;
    arg0->unk0x60 = 0;
    arg0->unk0x64 = 0;
    arg0->unk0x50 = 0;
    arg0->unk0x24 = temp_r3;
    arg0->unk0x38 = fn_801A6CCC(*(s32 *)((char *)*(void **)lbl_80305EAC + 0x24));
    arg0->unk0x3C = -1;
    GetInteger(arg1, QB_UNKNOWN_0xBAE9387B, &arg0->unk0x3C, 0);
    fn_8018BA34(arg0, arg1);
    if (ContainsFlag(arg1, QB_SINGLE_TIMER) != 0) {
        arg0->unk0x1C |= 2;
    }
    if (ContainsFlag(arg1, QB_RETRY_STAGE) != 0) {
        arg0->unk0x1C |= 4;
    }
    arg0->unk0x34 = QB_NONE;
    GetChecksum_2(arg1, QB_SKATER, &arg0->unk0x34, 0);
    if (ContainsFlag(arg1, QB_UNLOCKED_BY_ANOTHER) == 0) {
        if (ContainsFlag(arg1, QB_PRO_GOAL) == 0) {
            temp_r3 = arg0->unk0x70 & 0xFBFFFFFF;
        } else {
            temp_r3 = arg0->unk0x70 | QB_UNKNOWN_0x04000000;
        }
    } else {
        temp_r3 = arg0->unk0x70 | QB_UNKNOWN_0x04000000;
    }
    arg0->unk0x70 = temp_r3;
    return arg0;
}