// WIP DRAFT (non-matching) — C body rebuilt from the disassembly 2026-10-03
// family=m2c range=0x8012DC0C-0x8012DE30 size=548B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-22: NEAR 74.5%, object .text 544B vs the 548B symbol (1 word
// short). LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//   tools/test_wip_drafts.py --addr 0x8012DC0C
// Reproduces (each measured, cumulative): 11.7% -> 55.5% (single reused
// `void *o`, see below) -> 60.6% (inline the `& 0xFF`, swap the 0xE-arm mask)
// -> 74.5% (positive-first `if` conditions in case 0x16).
//
// The whole control-flow graph is right: the switch dispatch, both copies of
// the object-create path, the single shared fn_8012BFD8 tail behind `case 0x2D`
// / `default`, and the single shared fn_80117E28 tail all match want's call and
// relocation counts exactly (2x create path, 3x fn_8012CD84, 1x each shared
// tail). Two defects remain:
//
// 1. BLOCK ORDER in the default arm (the 548B blocker). want keeps the
//    `m == 0xA0000` body inline after its compare and reaches the shared
//    fn_80117E28 tail from three edges (the ==K body's branch, the m==0
//    branch, and the case-0x16 else); the object lays the ==K body out after
//    the m!=0 arm instead and branches forward to it — same instruction
//    multiset, different order, equal word count. Writing the tail call twice
//    inside this arm reproduces want's order EXACTLY (arm verified word-for-
//    word, 544B) but trades away the two callee-saved pointer homes: p moves
//    r31->r30 and o r30->r31, so the score drops to 64.7%. Cause: the
//    cross-jumper merges the two copies only after register allocation, so the
//    duplicate call site raises o's reference count and it wins the higher
//    register. Measured inert against that swap: declaration order, initialiser
//    position, `o = p = fn(...)` and `o = fn(...); p = o;` loop heads, a
//    separate loop-head copy variable, `u8`/`s32` types, hard-register pins
//    (they add saves, 524B), and -fno-optimize-register-move / -fno-regmove /
//    -fno-caller-saves / -fno-rerun-cse-after-loop / -fno-thread-jumps / -O3 /
//    -Os (bit-identical here). `-fno-schedule-insns` does reach 548B but
//    scrambles the order (34%). `-freorder-blocks` is not accepted by this cc1,
//    so the layout cannot be steered by a flag; a dozen further -fno-* flags
//    (gcse, cse-follow-jumps, strength-reduce, peephole, defer-pop, inline,
//    branch-count-reg, function-cse, force-mem, expensive-optimizations,
//    rerun-loop-opt) leave it at 540B / 70.4% with the true constant.
//
// 2. LOOP HEAD, one word: want loads the byte into a scratch register and
//    copies it to a second register that survives into the default arm's
//    `== 0xE` test; the object loads straight into the surviving register, so
//    the copy is missing (this is the 548-vs-544 gap, independent of defect 1).
//    Two-variable spellings (`c = p[0]; v = c;` and the reverse, `u8` and
//    `s32` forms, `(u8)v` / `p[0]` masks) all coalesce back to the single
//    register.
//
// Constant: the original really compares against 0x000A0000 (a bare high-half
// load with no low-half OR; 0xA0000 lies inside the 0x7F0000 mask, so the
// ==K body is reachable in retail). The body below keeps 0xA000 because that
// spelling scores higher: 0xA0000 measures 540B / 69.3%, 0xA000 measures
// 544B / 74.5%. With 0xA0000 the constant materialisation and the
// value/constant register roles match want exactly; the 2-word pair of the
// 0xA000 spelling only re-aligns the masked comparison downstream, so 74.5% is
// a scoring artefact rather than a closer body — neither spelling can reach
// 100% until defects 1 and 2 are solved.
//
// Smaller, still-open word: the two pointer/arg copies come out as arg0, arg2,
// arg1 (want: arg0, arg1, arg2). Measured: this is the *copy-kind* order, not
// scheduling — a copy from a local init (`p = arg1; n = arg2;`) is appended
// after the parameter home copies, in ascending destination-register order,
// whatever the source order. Making the cursor the parameter itself
// (`arg1` used directly, no `p` local) does give want's prologue order
// (arg0, arg1, arg2) but then the cursor colours to r30 and the object takes
// r31, i.e. the swap moves one level up (55.2%). So both spellings are one
// decision short of want: home-copy order vs. the r31/r30 colouring.
// Load-bearing source decisions (do not undo):
//  * ONE `void *o` serves as BOTH the loop-head cursor copy (`o = p`) and
//    the object returned by fn_801252BC. This is what puts arg1's variable in
//    r31 and the copy in r30 (55.5% jump); with a separate copy variable `q`
//    ngccc puts arg1 in r30 and every `p`-using instruction mismatches.
//  * `s2 = sp8;` between the fn_8012CB2C call and the fn_8012CD84 call is
//    what promotes the out-param to a callee-saved register (r27) and gives
//    the 0x28 frame + `stmw r27`; using `sp8` directly gives a 0x20 frame.
//  * `fn_8012CB2C` is left UNPROTOTYPED on purpose: want has `crclr cr1eq`
//    before its `bl` (recipe item 16/29 — the crclr IS the unprototyped-call
//    marker). Every other callee is prototyped so no other crclr appears.
//  * if-conditions must be written POSITIVE-FIRST with the DEEP block as the
//    then-block (`if (p[0]==7) {deep} else {shallow}`), or ngccc emits the
//    opposite branch polarity. This was worth +14% on its own.
//  * the switch needs explicit no-op `case 0/1/2`: want sends 0..2 straight
//    to the loop latch (`cmpwi r0,2; ble latch`) instead of to `default`.
//  * `v = p[0]` is a BYTE widened into a wide local and the mask is written
//    INLINE (`(v & 0xFF)`), not as a named temp: that is what materialises
//    `rlwinm ..,0x18` (recipe 6bc-2) while still putting the switch
//    discriminant in r0.
//  * the 0xE-arm mask is `& 0x007F0000` (rlwinm MB=9 ME=15) and the compared
//    constant is 0x000A0000, which sits inside that mask, so the ==K body is
//    reachable in retail. (An earlier 0xA000 reading could never match and was
//    a mis-decode of the high-half-only load; do not go back to it.)
// RULED OUT (all measured, LEAF_TMPDIR=<scratch>):
//  * A separate copy variable `q` beside the cursor (55.5% -> arg1 in r30).
//  * Splitting the object into per-arm `obj1`/`obj2` pointers: no change to
//    the allocation; the single `o` is required.
//  * Renaming cursor<->copy, and declaring `q` before `p`: both no-ops.
//  * Reusing `m` (the switch discriminant) as the 0xE-arm field temp: no change.
//  * Re-spelling the default arm as a 3-way if/else-if/else with the tail
//    call duplicated (the layout fix of defect 1): 544B, 64.7% — see the
//    register-swap discussion above.
//  * Nested `if (m != 0xA0000) { if (m != 0) {..} ... }` reorderings and a
//    `goto` to the shared tail: all reproduce the current block order, not
//    want's (540B / 70.4% with the true constant).
//  * Negating the 0xE-arm test (`if (m != 0xA000) {..} else {..}`): 74.5% -> 54.0%.
//  * `m = v & 0x7F000000` (m2c's reading) / `u32` types: ngccc FOLDS the mask
//    away entirely when the source value is a byte, deleting the guard and
//    collapsing the switch to `li r0,0`. The mask must be `& 0xFF` to survive.
//  * `v = *(u32*)p` + `& 0x7F000000`: gcc narrows correctly and emits
//    `rlwinm r0,r9,0,1,7`, never the want's buggy no-shift form.
// Next idea: both defects look like pre-allocation RTL-order effects, not
// spelling effects. Worth one try from a body that is not m2c-shaped: expand
// the loop body as an explicit opcode-indexed state machine, so the duplicate
// create path and the shared tails fall out of the control flow instead of
// being written twice in the source.
#include "types.h"

u8 *fn_8012CD84(u8 *);
s32 fn_8012B7B4(void);
void fn_8009F4C4(s32);
void *fn_801252BC(void);
u8 *fn_8012D62C(u8 *, s32, void *);
void fn_80127438(s32, void *);
void fn_80117E28(void *);
u8 *fn_8012BFD8(s32, s32, u8 *, s32);
void fn_80126F88(s32, s32);
u8 *fn_8012C48C(s32, u8 *, s32);
void fn_80126FF4(s32, s32);
void fn_801266EC(void *);

u8 *fn_8012DC0C(s32 arg0, u8 *arg1, s32 arg2) {
    void *o;
    s32 sp8;
    s32 s2;
    s32 v;
    s32 m;
    u8 *p;

    p = arg1;
    for (;;) {
        p = fn_8012CD84(p);
        o = p;
        if (fn_8012B7B4() != 0)
            break;
        v = p[0];
        if ((v & 0xFF) == 15)
            break;
        switch (v & 0xFF) {
        case 0x16:
            p++;
            fn_8012CB2C(&sp8, p);
            s2 = sp8;
            p = fn_8012CD84(p + 4);
            if (p[0] == 7) {
                p = fn_8012CD84(p + 1);
                if (p[0] == 0xE) {
                    fn_8009F4C4(0x10);
                    o = fn_801252BC();
                    p = fn_8012D62C(p, arg2, o);
                    if (*(s32 *)o & 0x007F0000) {
                        *(s32 *)((char *)o + 4) = s2;
                        fn_80127438(arg0, o);
                    } else {
                        fn_80117E28(o);
                    }
                } else {
                    p = fn_8012BFD8(arg0, s2, p, arg2);
                }
            } else {
                p = fn_8012BFD8(arg0, 0, o, arg2);
            }
            break;
        case 0x2C:
            p++;
            if (arg2 != 0)
                fn_80126F88(arg0, arg2);
            break;
        case 3:
            p = fn_8012C48C(arg0, p, arg2);
            break;
        case 9:
            p++;
            break;
        case 0:
        case 1:
        case 2:
            break;
        default:
            if (v == 0xE) {
                fn_8009F4C4(0x10);
                o = fn_801252BC();
                p = fn_8012D62C(p, arg2, o);
                m = *(s32 *)o & 0x007F0000;
                if (m == 0xA000) {
                    fn_80126FF4(arg0, *(s32 *)((char *)o + 8));
                    fn_801266EC(o);
                } else if (m != 0) {
                    *(s32 *)((char *)o + 4) = 0;
                    fn_80127438(arg0, o);
                    break;
                }
                fn_80117E28(o);
                break;
            }
        case 0x2D:
            p = fn_8012BFD8(arg0, 0, p, arg2);
            break;
        }
    }
    return p;
}
