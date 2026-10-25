// WIP DRAFT (non-matching) — reconstructed by hand from the want disassembly.
// family=m2c range=0x8012D62C-0x8012DC0C size=1504B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKING NOTE (tools/want_got.py + tools/test_wip_drafts.py, relocation
// masked): want 1504B / got 1504B — the object is the EXACT want size, the
// basic-block layout matches want INSTRUCTION-FOR-INSTRUCTION (all 40 block
// start addresses and all 40 block sizes are identical), and 315 of the 376
// instructions are byte-identical (83.8% masked, 61 diffs — up from 69).
// Every remaining diff is a REGISTER NUMBER inside an otherwise identical
// instruction stream (plus 2 scheduling swaps + 1 FPR swap):
//   (1) a 3-cycle in local-alloc: b2 / 2nd-&lbl_8039C324-hi / tok-hi are
//       r24/r25/r26 in want and r25/r26/r24 here (28 sites);
//   (2) the entry block ends `lis hi2; li zero; lis hi3` where want has
//       `lis hi2; lis hi3; li zero` (2 sites) — see LOOP-INVARIANT `zero`
//       below;
//   (3) in cases 0x17/0x1a the block-local &lbl_8039C520 is r31 and the saved
//       `p` is r30; here they are r30/r31 (plus the f0<->f13 swap of the
//       `fcmpu` against 0.0f in case 0x1a); 15 sites
//   (4) push_int sets up r4 before r5 (want: r5 then r4). 2 sites
// The zero/hi3 2-cycle of the previous revision is CLOSED: `zero` is now r20
// and the 3rd &lbl_8039C324 page anchor is r19, exactly as want.
//
// LOOP-INVARIANT `zero` (worth 8 diffs, the one lever that still moved):
//   ngccc's hoisted constant/page-anchor reloads are inserted at the very END
//   of the entry block, so a *source* `li` can never follow them. With
//   `zero = 0;` written in the entry-block init sequence the entry block was
//     [5 li's] [li zero] [lis hi2] [lis hi3]
//   and want is
//     [5 li's] [lis hi2] [lis hi3] [li zero].
//   `zero` is only ever assigned 0 and only ever READ at the two
//   `tok.p = zero; tok.w.b = zero;` sites inside the loop, so the assignment
//   may live at the TOP OF THE LOOP BODY instead: it is then loop-invariant
//   and ngccc's invariant motion hoists the `li` out to the preheader, where
//   it interleaves with the page anchors. That moves it one slot LEFT (one
//   step towards want) and, as a side effect, fixes the `zero`/3rd-hi 2-cycle.
//   Measured positions of `zero = 0` (all inside the loop unless noted):
//     top of loop body .................. 61 diffs  <-- kept
//     between the call and `op = *p` .... 61
//     after the call, before `op = *p` .. 61
//     as `p = (zero = 0, fn_8012CD84(p))`  61
//     right before its 1st use (case 0x16) 283
//     right before its 2nd use (case 0x2d) 311
//     after the switch, before the back edge 345
//     in the entry block (previous draft)  69
//   Same 61 for `do {} while (go)`, `for (;;) { ... if (!go) break; }` and
//   `while (go)` — the loop shape itself is not a lever.
// Rejected by measurement this round: -fno-schedule-insns2 (206),
// -fno-schedule-insns (209), -fno-gcse (281), -fno-thread-jumps (61, no-op),
// -fno-loop-optimize / -fno-move-loop-invariants / -fno-crossjumping (cc1
// does not know them); hard-register pins `register s32 b2 __asm__("r24")`
// (125 — pinning b2 to r24 displaces b3 r28->r26 and `p` r29->r31, so it is
// a 64-diff regression), the same pin plus `zero`->r20 (124), `zero`->r20
// alone (61, no-op); the float case written as
// `if (p.f >= 0.0f || b2 == 0) go = 0; else {...}` (253) or with `&&`
// operands swapped (271); `zero` replaced by the literal 0 at both use sites
// (319 — two materialisations, two registers).
//
// BLOCKED ON: local-alloc tie-breaking between pseudos of equal live length
// (`b2` / the two &lbl_8039C324 page anchors / the &lbl_8039C520 page anchor,
// all function-wide). The RTL ORDER is identical everywhere — prologue init
// sequence, loop preheader, both switch b-trees, frame 0x50 / LR slot 0x54 /
// callee-save area 0x14 — so this is not reachable by changing types, casts
// or statement order. Note that the whole residual CASCADES from the entry
// block: cases 0x17/0x1a's r30<->r31 swap and the f0<->f13 swap are the SAME
// allocation decision made later, so they should fall out of (1) once (1) is
// reachable.
//
// WHAT THIS DRAFT ESTABLISHED (each confirmed by measurement):
//   * `&lbl_8039C324` / `&lbl_8039C520` must be written as GLOBAL objects
//     (`extern char lbl_8039C324[]; extern Tok lbl_8039C520;`), NOT through
//     local pointer copies. A local copy makes ngccc keep one register, and
//     the function loses ~5 words and the 3 extra address temps want has.
//   * tok.w bitfield `b` is at LSB bits 16..22, i.e. declare
//     `u32 f0:9; b:7; y:16` — GCC allocates big-endian bitfields from the
//     MSB down, so the FIRST member takes the TOP bits (recipes §4:
//     "rlwinm/rlwimi MB and ME are MSB-relative").
//   * the inner node-type switch needs SEPARATE `case` statements with
//     duplicated bodies, NOT `case 1: case 3: ...`. With one grouped case GCC
//     range-clusters 3..6 into a single `cmpwi 6 / bgt` test; want compares
//     6, 3, 1, 2, 4, 5 individually and merges the identical bodies
//     afterwards via cross-jumping. Worth 8 instructions + the right tree.
//   * the source order of the inner cases decides the block layout:
//     2, 1, 3, 4, 5, 6, 0xd, 0xa, 0xc, 8, 9, default — and `default:` must be
//     LAST (moving it up from between 0xc and 8 is worth 8 diffs).
//   * the outer switch's case order also decides the tail block order: the
//     `case 0x05/0x07/0x08/0x0a..0x0d/0x12/0x14/0x32/0x33` "open block" case
//     must be declared BEFORE `case 0x01: case 0x06:` and `case 0x02:` or the
//     last three basic blocks come out rotated by one.
//   * cases 0x17/0x1a each need their OWN copy of
//     `fn_8013400C(g,&tok); fn_801266EC(&tok);` (no shared `goto flush`
//     label) — with the shared label GCC hoists the argument setup into one
//     common block and each case loses 2 instructions.
//   * fn_8012CB2C must be called with NO prototype (`void fn_8012CB2C();`) —
//     that is what emits want's `crclr cr1eq` before the `bl` (recipes item 16
//     / "the spurious crclr": a missing prototype emits crclr).
//   * fn_8012DC0C takes THREE args (o, p, arg1), not two — want loads r3 from
//     the CStruct_ctor result and passes p in r4, arg1 in r5.
//   * case 8 builds `o = CStruct_ctor(CStruct_new(8))` — TWO calls
//     (0x80019D08 then 0x80126EAC), not one.
//   * masking honesty: every REL14/REL24/ADDR16_HA/LO field in the object is a
//     LINKER PLACEHOLDER, so the masked diff proves nothing about branch
//     targets. Re-derived from the branch-RESOLVED `ngccc -S` form (map .L
//     labels to instruction indices, calls to symbols.txt): all 129 branches
//     in this draft — condition (BO/BI) AND resolved target — match want.
//     (Two traps when scripting that: `blrl`/`blr` have NO operands so a
//     `^\t(mn) (ops)$` regex silently drops them and every later index shifts
//     by 2; and GCC's own `bc BO,BI` comments use BI 0=LT 1=GT 2=EQ.)
#include "types.h"

typedef struct Tok {
    union {
        struct { u16 lo; u16 hi; } hw;
        struct { u32 f0:9; u32 b:7; u32 y:16; } bits;
    } w;
    u32 pad;
    union { s32 i; f32 f; } p;
} Tok;

typedef struct Node {
    u16 lo;
    u8 type;
    u8 pad3[9];
    union { s32 i; f32 f; s32 (*fn)(void *, s32); } v;
} Node;

typedef struct Comp {
    u16 lo;
    u16 pad2;
    u32 name;
    s32 value;
    struct Comp *next;
} Comp;

typedef struct Script {
    u32 flags;
    Comp *head;
} Script;

extern char lbl_8039C324[];
extern Tok lbl_8039C520;

void fn_8013237C(void *);
void fn_801323CC(void *, s32);
void *fn_8012CD84(void *);
void fn_80134080(void *);
void fn_8013409C(void *);
void *fn_8012D190(void *, s32, Tok *);
void fn_80133F8C(void *, s32);
void fn_8013400C(void *, Tok *);
void fn_801266EC(Tok *);
void *fn_80125480(s32);
s32 fn_8012ED70(void);
void *CStruct_new(s32);
void *CStruct_ctor(void *);
void CStruct_delete(void *, s32);
void *fn_8012DC0C(void *, void *, s32);
void fn_8012701C(void *, s32);
Comp *fn_801272AC(Script *, s32);
void fn_8012B1C0(Tok *);
void fn_80125320(Tok *);
void fn_801340FC(void *, s32);
void fn_8012CB2C();

u8 *fn_8012D62C(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = (u8 *)arg0;
    u8 *q;
    u8 op;
    Node *node;
    Comp *comp;
    void *o;
    s32 a;
    s32 typ;
    s32 val;
    s32 sp8;
    s32 b1;
    s32 b2;
    s32 b3;
    s32 b4;
    s32 go;
    s32 zero;

    fn_8013237C(lbl_8039C324);
    fn_801323CC(lbl_8039C324, arg0);
    p++;
    b1 = 0;
    b2 = 0;
    b3 = 1;
    b4 = 0;
    go = 1;

    while (go != 0) {
        // `zero` is only ever READ at the two `tok.p = zero; tok.w.b = zero;`
        // sites below (case 0x16's tail and case 0x2d), and it is only ever
        // assigned 0, so the initialisation may live at the top of the loop
        // body instead of in the entry block: it is then loop-invariant and
        // ngccc's loop-invariant motion hoists the `li` out to the preheader.
        // Measured: that moves the `li r20,0` from BEFORE the two hoisted
        // `lis` page anchors to BETWEEN them, which is what want wants, and
        // it is worth 8 diffs (69 -> 61). See the parking note at the top.
        zero = 0;
        p = fn_8012CD84(p);
        op = *p;
        switch (op) {

        case 0x0e:
            if (b3 == 0) { go = 0; break; }
            p++;
            fn_80134080(lbl_8039C324);
            b2 = 0;
            b3 = 1;
            b1++;
            break;

        case 0x0f:
            p++;
            if (b1 == 0) { go = 0; break; }
            fn_8013409C(lbl_8039C324);
            b2 = 1;
            b3 = 0;
            b1--;
            break;

        case 0x17:
            if (b3 != 0) goto push_int;
            q = fn_8012D190(p, arg1, &lbl_8039C520);
            if ((lbl_8039C520.p.i < 0) && (b2 != 0)) {
                fn_80133F8C(lbl_8039C324, 10);
                p = q;
                lbl_8039C520.p.i = -lbl_8039C520.p.i;
                b2 = 1;
                fn_8013400C(lbl_8039C324, &lbl_8039C520);
                fn_801266EC(&lbl_8039C520);
            } else {
                go = 0;
            }
            break;

        case 0x1a:
            if (b3 != 0) goto push_int;
            q = fn_8012D190(p, arg1, &lbl_8039C520);
            if ((lbl_8039C520.p.f < 0.0f) && (b2 != 0)) {
                fn_80133F8C(lbl_8039C324, 10);
                p = q;
                b2 = 1;
                lbl_8039C520.p.f = -lbl_8039C520.p.f;
                fn_8013400C(lbl_8039C324, &lbl_8039C520);
                fn_801266EC(&lbl_8039C520);
            } else {
                go = 0;
            }
            break;

        case 0x16:
            if (b3 == 0) { go = 0; break; }
            p = fn_8012D190(p, arg1, &lbl_8039C520);
            b3 = 0;
            node = NULL;
            if (b4 == 0) {
                node = fn_80125480(lbl_8039C520.p.i);
            }
            if (node != NULL) {
                // Read the type byte into a 32-bit local first: with
                // `switch (node->type)` ngccc adds a clrlwi + mr to narrow the
                // u8 field for the compares; want has neither.
                typ = node->type;
                // NOTE: these cases are deliberately NOT merged into
                // `case 1: case 3: ...` (see the parking note at the top):
                // want's b-tree compares 6, 3, 1, 2, 4 and 5 one at a time
                // and merges the identical bodies afterwards, which only
                // happens when each case owns its label. The ORDER here and
                // `default:` last also decide the block layout.
                switch (typ) {
                case 2:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.f = node->v.f;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 1:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 3:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 4:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 5:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 6:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 0xd:
                    lbl_8039C520.w.bits.b = typ;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 0xa:
                    lbl_8039C520.w.bits.b = 0x14;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 0xc:
                    lbl_8039C520.w.bits.b = 0x15;
                    lbl_8039C520.p.i = node->v.i;
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 8:
                    a = fn_8012ED70();
                    lbl_8039C520.w.bits.b = 1;
                    o = CStruct_ctor(CStruct_new(8));
                    p = fn_8012DC0C(o, p, arg1);
                    lbl_8039C520.p.i = node->v.fn(o, a);
                    if (o != NULL) {
                        CStruct_delete(o, 3);
                    }
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                case 9:
                    break;
                default:
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    break;
                }
            } else {
                fn_8013400C(lbl_8039C324, &lbl_8039C520);
            }
            b2 = 1;
            lbl_8039C520.p.i = zero;
            b3 = 0;
            lbl_8039C520.w.bits.b = zero;
            break;

        case 0x03: case 0x1b ... 0x1c: case 0x1e ... 0x1f: case 0x30:
            if (b3 == 0) { go = 0; break; }
        push_int:
            p = fn_8012D190(p, arg1, &lbl_8039C520);
            b2 = 1;
            b3 = 0;
            fn_8013400C(lbl_8039C324, &lbl_8039C520);
            fn_801266EC(&lbl_8039C520);
            break;

        case 0x2d:
            if (b3 == 0) { go = 0; break; }
            p = p + 2;
            fn_8012CB2C(&sp8, p);
            p = p + 4;
            val = sp8;
            if (arg1 != 0) {
                comp = fn_801272AC((Script *)arg1, val);
                if (comp != NULL) {
                    lbl_8039C520.w.bits.b = comp->lo & 0x7F;
                    lbl_8039C520.p.i = comp->value;
                    fn_8012B1C0(&lbl_8039C520);
                    fn_80125320(&lbl_8039C520);
                    fn_8013400C(lbl_8039C324, &lbl_8039C520);
                    lbl_8039C520.p.i = zero;
                    lbl_8039C520.w.bits.b = zero;
                }
            }
            b2 = 1;
            b3 = 0;
            break;

        case 0x2c:
            if (b3 == 0) { go = 0; break; }
            p++;
            if (arg1 != 0) {
                lbl_8039C520.p.i = arg1;
                lbl_8039C520.w.bits.b = 0x14;
                fn_8013400C(lbl_8039C324, &lbl_8039C520);
            }
            b2 = 1;
            b3 = 0;
            break;

        case 0x05: case 0x07 ... 0x08: case 0x0a ... 0x0d:
        case 0x12: case 0x14: case 0x32 ... 0x33:
            fn_80133F8C(lbl_8039C324, op);
            p++;
            b2 = 0;
            b3 = 1;
            b4 = (op == 8);
            break;

        case 0x01: case 0x06:
            p++;
            break;

        case 0x02:
            p = p + 5;
            break;

        case 0x00: case 0x09: case 0x24:
            break;

        default:
            break;
        }
    }

    fn_801340FC(lbl_8039C324, arg2);
    return p;
}
