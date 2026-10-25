// WIP DRAFT (non-matching) — body hand-rebuilt from the want disassembly
// family=m2c range=0x8012FDC0-0x80130250 size=1168B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-04. Verdict: DIFF. Official masked score 39.93%
// (test_wip_drafts.py scores over the GOT's own 298 words); the object is
// 1192 B = +6 words vs the 1168 B want, and tools/want_got.py silently
// truncates the got so its 40.75% is the same content measured over the
// first 292 want words. Either way it is not a match.
//
// The body is SEMANTICALLY COMPLETE — every branch, callee, arity, field
// offset, constant and return path of the 292-word want is reproduced, and
// ~40% of the words are already byte-identical. Two residuals block 100%:
//
// (1) BLOCKER A — ngccc never merges the four identical
//     `li r5,0 ; bl fn_8012FC30|fn_8012FBCC ; b <epilogue>` tails that want
//     shares (want has 2 shared 3-word tail blocks at 0x801301E0/0x801301F4
//     and 2 at 0x8013009C/0x801300A8; here each of the 8 call sites keeps its
//     own inline copy). That is docs/parkings/31 (intra-fn `bl` crossjump):
//     every body that ends in one of those calls is +1 word, which is exactly
//     the +6 over-length. Synthetic probes in /tmp show GCC's crossjumping
//     DOES merge such tails for 2 branches but not for 4, and the merge did
//     not fire here even after forcing the other half of the problem (below).
//
// (2) BLOCKER B — the five `fn_8012CB2C` out-param slots (0x8..0x1C) are
//     reloaded AFTER the intervening `bl fn_8012FAB8` into a call-saved
//     register (want: `lwz r30,8(r1)` hoisted BEFORE that call, into a
//     callee-saved register, then `mr r4,r30`). Making the slots
//     `volatile` + copying them into a local (`volatile void *sp8; ...
//     v = sp8;`) DOES produce want's exact hoisted load
//     (`lwz r29,8(r1)` right after `mr r3,r31`) but costs +5 words net and
//     loses (1) worse. GCC 2.95 copy-propagates `v = sp8` straight through
//     the call, so a plain copy cannot pin the reload early (tried: copy
//     before/after `cur += 4`, `v = 0` pre-init, u32 vs void* slot types,
//     ++/+= statement forms — all identical output).
//
// BREAKTHROUGH worth writing up (recipes / doc-28): the original's ONLY
// non-CR0 condition-code use in all 292 words is a single compare of r0
// against 0x46 into cr4 at 0x8012FE28, re-tested by a cr4 not-equal branch to
// 0x8012FE6C at 0x8012FE2C (first chain) and again by a cr4 not-equal branch
// to 0x80130010 at 0x8012FFD0 (second chain, inside the 0x42 arm).
// plus the paired `mfcr r12 / stw r12,0x20(r1)` prologue and
// `lwz r12,0x20(r1) / mtcrf 8,r12` epilogue (doc-28 class). The chain-2
// `bne cr4` has NO compare of its own: it re-tests chain 1's flag 15 calls
// later, so the 0x46 arm at 0x8012FFD4..0x8013000C is DEAD CODE in the retail
// binary (reaching it requires chain 1's `c == 0x46` to have been FALSE).
// That artifact is reproducible in plain C and only from a LOCAL opcode
// variable that is read once and never redefined — declaring
// `u8 op = arg0->cur[0];` and testing `if (op == 0x46)` in BOTH chains makes
// GCSE hoist the invariant compare into CR4 and emits the whole doc-28
// mfcr/mtcrf 8 + call-saved-CR dance verbatim (measured: prologue 7/7 words
// exact, `cmpwi cr4` + both `bne cr4` exact, got 1204 B = +9). Using
// `*arg0->cur` inline in both chains (the body kept here) does NOT CSE/GCSE
// at all, because cse/GCSE kills the memory expression on the intervening
// `stw rX,0x10(r31)` stores. -fno-gcse removes the CR machinery and confirms
// the hoist is GCSE (not cse_basic_block).
// MEASURED VARIANTS: mem-inline body (kept) 39.9% official / 1192 B;
// mem + `volatile` slots + copies 8.90%, 1212 B;
// `op`-local body 11.64%, 1204 B;
// `op`-local + `volatile` slots + copies 5.14%, 1216 B.
// Also rejected: switch/case for the opcode chains (want uses a linear
// if-chain; the switch builds a balanced case tree, 3.42%);
// -fno-schedule-insns / -fno-schedule-insns2 / -fno-gcse / -fno-thread-jumps
// / -fstrict-aliasing (all neutral or worse).
// Semantics fixed along the way (m2c had them wrong): fn_8012D190's first
// arg is the STREAM pointer (like fn_8012D62C), not arg0; fn_8012FCA8 is
// value-returning (want returns its r3); fn_80125480 takes an s32 handle;
// the resolved node is `u8 type@+2, s32 id@+4, void *unkC@+C`.
// ---------------------------------------------------------------------------
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* Scripted-parameter stream object. arg0 doubles as a script-value node in
 * the opcode-0xE path (fn_801252BC zeroes fields +0..+0xC of arg0 itself). */
typedef struct Stream {
    s32 flags;
    s32 unk4;
    void *val;
    void *next;
    u8 *cur;
    s32 unk14;
    s32 unk18;
    char pad1C[0xA0];
    void *unkBC;
    char padC0[0x8];
    s32 unkC8;
} Stream;

/* node built in place by fn_801252BC / fn_8012D62C (opcode 0xE) */
typedef struct SNode {
    s32 flags;
    void *unk4;
    void *val;
    void *next;
} SNode;

/* resolved script-value node (fn_80125480 / fn_8012FCD8 result) */
typedef struct RNode {
    char pad0[2];
    u8 type;
    char pad3;
    s32 id;
    char pad8[0x4];
    void *unkC;
} RNode;

extern s32 lbl_8030342C;

void fn_8012CB2C();                     /* no prototype: want's crclr cr1eq */
u8 *fn_8012CD84(u8 *);
void fn_8012FAB8(Stream *);
s32 fn_8012FC30(Stream *, void *, void *);
s32 fn_8012FBCC(Stream *, void *, void *);
s32 fn_8012FCA8(Stream *, void *);
void *fn_8012FCD8(Stream *);
RNode *fn_80125480(void *);
void fn_8012F68C(Stream *, void *, s32, s32, void *, s32);
s32 fn_8013465C(s32, s32);
SNode *fn_801252BC(void *);
u8 *fn_8012D62C(u8 *, s32, SNode *);
u8 *fn_8012D190(u8 *, s32, SNode *);
void fn_801266EC(SNode *);
void fn_80117E28(SNode *);
void fn_80127438(s32, SNode *);
void *fn_8009F498(void *);
void fn_8009F4C4(s32);

s32 fn_8012FDC0(Stream *arg0) {
    RNode *n;
    SNode *node;
    void *sp8;
    void *spC;
    void *sp10;
    void *sp14;
    void *sp18;
    void *sp1C;
    void *v29;

    if (*arg0->cur == 0x44) {
        arg0->cur = arg0->cur + 1;
        fn_8012CB2C(&sp8, arg0->cur);
        arg0->cur = arg0->cur + 4;
        fn_8012FAB8(arg0);
        return fn_8012FC30(arg0, sp8, 0);
    }
    if (*arg0->cur == 0x46) {
        arg0->cur = arg0->cur + 1;
        fn_8012CB2C(&spC, arg0->cur);
        arg0->cur = arg0->cur + 4;
        fn_8012FAB8(arg0);
        return fn_8012FBCC(arg0, spC, 0);
    }
    if (*arg0->cur == 0x43) {
        arg0->cur = arg0->cur + 1;
        fn_8012CB2C(&sp10, arg0->cur);
        arg0->cur = arg0->cur + 4;
        fn_8012FAB8(arg0);
        return fn_8012FCA8(arg0, sp10);
    }
    v29 = 0;
    if (*arg0->cur == 0xE) {
        fn_8009F4C4(0x10);
        node = fn_801252BC(arg0);
        arg0->cur = fn_8012D62C(arg0->cur, arg0->unk18, node);
        if ((node->flags & 0x7F0000) == 0xD0000) {
            v29 = node->val;
            fn_801266EC(node);
            fn_80117E28(node);
        } else {
            s32 ok = (node->val != 0);
            fn_801266EC(node);
            fn_80117E28(node);
            return ok;
        }
    }
    if (v29 == 0) {
        v29 = fn_8012FCD8(arg0);
    }
    if (*arg0->cur == 0x42) {
        if ((v29 = fn_8009F498(v29)) == 0) {
            return 1;
        }
        arg0->cur = arg0->cur + 1;
        arg0->cur = fn_8012CD84(arg0->cur);
        if (*arg0->cur == 0x44) {
            arg0->cur = arg0->cur + 1;
            fn_8012CB2C(&sp14, arg0->cur);
            arg0->cur = arg0->cur + 4;
            fn_8012FAB8(arg0);
            return fn_8012FC30(arg0, sp14, v29);
        }
        if (*arg0->cur == 0x46) {
            arg0->cur = arg0->cur + 1;
            fn_8012CB2C(&sp18, arg0->cur);
            arg0->cur = arg0->cur + 4;
            fn_8012FAB8(arg0);
            return fn_8012FBCC(arg0, sp18, v29);
        }
        node = fn_8012FCD8(arg0);
        fn_8012FAB8(arg0);
        if (((n = fn_80125480(node)) != NULL) || (arg0->unkC8 != -QB_UNKNOWN_0x04EE1933)) {
            if (n->type == 7) {
                fn_8012F68C(arg0, node, fn_8013465C(lbl_8030342C, n->id), arg0->unk14, v29, 0);
                return 1;
            }
            if (n->type == 9) {
                if (n->unkC != 0) {
                    return fn_8012FBCC(arg0, n->unkC, v29);
                }
                return fn_8012FC30(arg0, node, v29);
            }
        }
        return 0;
    }
    if (*arg0->cur == 7) {
        arg0->cur = arg0->cur - 4;
        fn_8012CB2C(&sp1C, arg0->cur);
        arg0->cur = arg0->cur + 5;
        arg0->cur = fn_8012CD84(arg0->cur);
        fn_8009F4C4(0x10);
        node = fn_801252BC(arg0);
        if (*arg0->cur == 0xE) {
            arg0->cur = fn_8012D62C(arg0->cur, arg0->unk18, node);
        } else {
            arg0->cur = fn_8012D190(arg0->cur, arg0->unk18, node);
        }
        if ((node->flags & 0x7F0000) != 0) {
            node->unk4 = sp1C;
            fn_80127438(arg0->unk18, node);
        } else {
            fn_80117E28(node);
        }
        return 1;
    }
    fn_8012FAB8(arg0);
    if ((n = fn_80125480(v29)) != NULL) {
        switch (n->type) {
        case 8:
            return fn_8012FCA8(arg0, n->unkC);
        case 9:
            if (n->unkC != 0) {
                return fn_8012FBCC(arg0, n->unkC, 0);
            }
            return fn_8012FC30(arg0, v29, 0);
        case 7:
            fn_8012F68C(arg0, v29, fn_8013465C(lbl_8030342C, n->id), arg0->unk14, arg0->unkBC, 0);
            return 1;
        default:
            return 0;
        }
    } else {
        s32 r = 1;
        if (arg0->unkC8 == -QB_UNKNOWN_0x04EE1933) {
            r = 0;
        }
        return r;
    }
}