// WIP DRAFT (parked) — 0x8012E228, the QB token-stream pre-pass /
// statement walker (two `switch(*cursor)` loops over a byte script).
// family=m2c range=0x8012E228-0x8012E604 size=988B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEST MEASURED BODY: 988B object (size-EXACT) at 25.1% masked,
//   flags: -fno-schedule-insns -fno-schedule-insns2  (see // FLAG: below).
//   Baseline was the m2c draft at DIFF 5.3% / 988B-want-vs-868B-object.
//
// WHY PARKED (residual is register allocation + two block-layout choices;
// neither is reachable from plain C with the flags available to this
// compiler — details and the negative results below).
//
// 1. REGISTER COUNT / FRAME.  The want frame is 0x48 with
//    `stmw r21, 0x1c(r1)` = ELEVEN callee-saved regs (r21..r31) and the four
//    address-taken out-params at 0x8/0xc/0x10/0x14.  This body allocates NINE
//    (r23..r31), so without help the frame comes out 0x40 (LR at 0x44)
//    instead of 0x48 — the "issue-01 +8" shape, but the missing 8 bytes are
//    TWO MISSING CALLEE-SAVED REGISTERS, not a missing local:
//      * the want keeps its arg3 flag as a *predicate* only — `cmpwi cr4,r6,0`
//        at entry, captured with `mfcr r31; rlwinm r31,r31,0x10,0,3`, replayed
//        with `mtcrf 0x80, r31` — so arg3 itself never gets a GPR.  This body
//        materialises arg3 into a register (r30) and compares it after the
//        first call, costing one register;
//      * the want hoists the case-0x16 hash (`lwz r29, 0x10(r1)`) and the
//        case-0x23 hash (`lwz r27, 0x14(r1)`) into callee-saved regs for the
//        whole case body; this body re-loads them from the stack (3x and 2x).
//    A `volatile double _dummy;` DOES fix the frame size (0x40 -> 0x48) but
//    only by pushing the four out-params from 0x8.. to 0x10.., i.e. it
//    trades a size match for a worse offset match — measured 24.7% with it
//    vs 24.3% without.  It is kept only because it makes the object
//    size-exact; the 0x8-vs-0x10 local offsets stay wrong either way.
// 2. LOOP-1 case 0x2B.  want: `lwz r3,8(r1); addi r4,r30,4; mtcrf; beq; bl
//    fn_8012E0AC; b; bl fn_801263A0; lbzu r0,4(r30)` — the call argument is
//    p+4 with `p` still un-advanced, and the `p += 4` is fused into the
//    string-skip loop's first `lbzu` AFTER the branch join.  This body (same
//    source, same flags) sinks `p += 4` into BOTH if/else arms, duplicating
//    `addi r30,r30,4 / lwz r3,sp / mr r4,r30` and adding a `mr r3,r30;
//    mr r30,r3` pair — +6 instructions there.  GCC's if-conversion /
//    crossjumping declines to merge them.  MEASURED AND REJECTED: moving
//    `p += 4` before the calls (988B->976B, 16.0%); duplicating the whole
//    skip into both arms (988B, 13.8%); a shared `u8 *nm = p + 4` (984B,
//    4.9%); a goto-shared tail (988B, same 25.1%).
// 3. case 0x45 block order.  want branches `beq` OUT OF LINE to the
//    `spC == 0x0FA33D9B` body (it sits last in the case, after the 0x70CB0238
//    body and the *p scan loop); this body lays that body INLINE and branches
//    `bne` past it.  Same instruction count, ~14 words out of alignment.
//    MEASURED AND REJECTED: swapping the two `if` tests (988B, 23.5%).
// 4. Loop-invariant arg4 predicate.  The want compares it TWICE —
//    `cmpwi cr3,r22,0` hoisted before loop 2 for the case-0x16 path, and
//    `cmpwi cr4,r22,0` inside the case-0x23 preheader — and keeps both
//    across the loop in non-volatile CR fields.  This body hoists a single
//    `cmpwi cr4` and reuses it for all three tests (−1 instruction, and it
//    changes the CR field, so every `beq cr4`/`bne cr4` word differs).
//
// SEMANTIC NOTES (all verified against the want disassembly):
//  * 5 parameters, not 4: r25=arg0 (`const char *`, a script/symbol name,
//    hashed by fn_8000A778), r29=arg1 (cursor, reset before loop 2 — this is
//    why the want keeps arg1 and the cursor in SEPARATE registers),
//    r21=arg2, r6=arg3 (used only as a predicate), r22=arg4.
//  * `skip = !arg2;` is what produces the want's `subfic r9,r21,0 /
//    adde r0,r9,r21` idiom; the `case 0x02` polarity is the OPPOSITE of the
//    m2c draft: fn_8012B2A0 is called when arg2 == 0, and arg2 != 0 is the
//    `b .` infinite loop.
//  * loop-2 case 0x23 "remove vs keep" reduces to ONE test, `arg4 != 0`
//    (the type==7 and type!=7 paths only differ in which polarity GCC emits:
//    `bne cr4` then `beq cr4`).  The gotos force the two call blocks to be
//    shared; writing the ternary `del = type==7 ? (arg4!=0) : (arg4==0)`
//    materialises `del` and costs 5 instructions (measured, rejected).
//  * the node==NULL arm needs its own `fn_8012C678` call plus
//    `if (arg4 != 0) fn_8012E928(ret)` — fn_8012C678 returns the value
//    fn_8012E928 consumes.
//  * fn_8012CB2C must stay UNPROTOTOTYPED: the want has `crclr cr1eq`
//    before exactly the four calls to it and nowhere else.
//  * globals must be declared house-style (`extern char lbl_...[]` + cast):
//    with a typed `extern Unk_C7387A53 **lbl_802FFE98;` GCC materialises the
//    symbol's ADDRESS in a register and emits an extra `lwz` per access
//    (1020B vs 992B object) — measured, rejected.
//
// INDEPENDENT CHECK THAT THE BODY IS THE RIGHT PROGRAM (not just a byte
// shuffle): both the want and this object contain exactly 39 `bl`
// instructions, and the MULTISET of their resolved targets is IDENTICAL —
// same 39 callees, same multiplicities (fn_8012CB2C x8, fn_8012CBE8 x6,
// fn_8012B2A0 x6, ...).  Only 5 of the 39 differ in POSITION, and those 5
// are the two block-ordering swaps of item 2 and item 3 above.  Every
// `crclr cr1eq` sits before a fn_8012CB2C call and nowhere else, and the
// global references are the house `lbl_802FFE98` / `lbl_802FFE54` /
// `lbl_803032B4` symbols, so the link-time addresses are right by
// construction.  The residual is codegen-shape, not semantics.
// FLAG: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
#include "structs.h"

extern char lbl_802FFE98[];
extern char lbl_802FFE54[];
extern char lbl_803032B4[];

unsigned int fn_8000A778(const char *str);
s32 fn_8000F2F8(s32, s32);
void fn_8000F320(Unk_C7387A53 *self);
void fn_8012DF78(void);
void fn_8012E018(s32);
void fn_8012E0AC(s32, u8 *);
void fn_801263A0(s32, void *);
u8 *fn_8012CBE8(u8 *p);
u8 *fn_8012B2A0(u8 *p);
u8 *fn_8012D0D8(u8 *p);
s32 fn_8012D11C(u8 *p);
u8 *fn_8012C790(u8 *, u8 *, void *, s32);
void *fn_8012C678(CScript *, s32, u8 *, s32, void *);
Unk_5AA7B5D7 *fn_8012543C(s32);
void fn_8012E94C(Unk_5AA7B5D7 *);
void fn_801254E4(void *);
void fn_8012DE30(void *);
void fn_8012E928(Unk_5AA7B5D7 *);

typedef struct ScriptNode {
    char pad0x0[2];
    u8 type;
    char pad0x3[1];
    s32 unk0x4;
    s32 unk0x8;
    s32 *unk0xC;
} ScriptNode;

void fn_8012E228(const char *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile double _dummy;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 done;
    s32 skip;
    u8 *p;

    fn_8012DF78();
    if (arg3 != 0) {
        fn_8012E018(0);
    }
    done = 0;
    skip = !arg2;
    p = arg1;
    while (done == 0) {
        switch (*p) {
        case 0x2B:
            p++;
            fn_8012CB2C(&sp8, p);
            if (arg3 == 0) {
                fn_801263A0(sp8, p + 4);
            } else {
                fn_8012E0AC(sp8, p + 4);
            }
            p += 4;
            while (*p != 0) {
                p++;
            }
            p++;
            break;
        case 0x00:
            done = 1;
            break;
        case 0x02:
            if (skip) {
                p = fn_8012B2A0(p);
                break;
            }
            for (;;) {
            }
        default:
            p = fn_8012B2A0(p);
            break;
        }
    }

    fn_801263A0(fn_8000A778(arg0), arg0);
    *(s32 *)lbl_803032B4 = fn_8000A778(arg0);
    fn_8000F2F8(*(Unk_C7387A53 **)lbl_802FFE98, (*(Unk_C7387A53 **)lbl_802FFE98)->unk0x12C);

    p = arg1;
    done = 0;
    do {
        p = fn_8012CBE8(p);
        switch (*p) {
        case 0x45:
            p += 2;
            fn_8012CB2C(&spC, p);
            p += 4;
            if (spC == 0x0FA33D9B) {
                fn_8000F320(*(Unk_C7387A53 **)lbl_802FFE98);
                fn_8000F2F8(*(Unk_C7387A53 **)lbl_802FFE98, (*(Unk_C7387A53 **)lbl_802FFE98)->unk0x12C);
            } else if (spC == 0x70CB0238) {
                if (*(s32 *)lbl_802FFE54 != 0) {
                    fn_8000F320(*(Unk_C7387A53 **)lbl_802FFE98);
                    fn_8000F2F8(*(Unk_C7387A53 **)lbl_802FFE98, (*(Unk_C7387A53 **)lbl_802FFE98)->unk0x178);
                } else {
                    while (*p != 0x45 && *p != 0) {
                        p = fn_8012B2A0(p);
                    }
                }
            }
            break;
        case 0x16: {
            Unk_5AA7B5D7 *node;
            p++;
            fn_8012CB2C(&sp10, p);
            p = fn_8012CBE8(fn_8012CBE8(p + 4) + 1);
            node = fn_8012543C(sp10);
            if (node != NULL) {
                if (arg4 != 0) {
                    fn_8012E94C(node);
                    fn_801254E4(node);
                } else {
                    fn_8012DE30(node);
                }
            }
            p = fn_8012C790(sp10, p, arg0, arg2);
            if (node == NULL && arg4 != 0) {
                fn_8012E928(fn_8012543C(sp10));
            }
            break;
        }
        case 0x23: {
            ScriptNode *node;
            u8 *q;
            s32 len;
            s32 val;
            p += 2;
            fn_8012CB2C(&sp14, p);
            p += 4;
            q = p;
            p = fn_8012D0D8(q);
            len = p - q;
            val = fn_8012D11C(q);
            node = fn_8012543C(sp14);
            if (node != NULL) {
                if (node->type == 7) {
                    if (val == *node->unk0xC) {
                        break;
                    }
                    if (arg4 == 0) {
                        goto keep;
                    }
                } else if (arg4 == 0) {
                    goto keep;
                }
                fn_8012E94C(node);
                fn_801254E4(node);
                goto emit;
            keep:
                fn_8012DE30(node);
            emit:
                fn_8012C678(sp14, val, q, len, arg0);
            } else {
                s32 err = fn_8012C678(sp14, val, q, len, arg0);
                if (arg4 != 0) {
                    fn_8012E928(err);
                }
            }
            break;
        }
        case 0x2B:
            p = fn_8012B2A0(p);
            break;
        case 0x00:
            done = 1;
            break;
        default:
            break;
        }
    } while (done == 0);

    fn_8000F320(*(Unk_C7387A53 **)lbl_802FFE98);
    *(s32 *)lbl_803032B4 = 0;
}