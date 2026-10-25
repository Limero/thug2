// PARKED 2026-10-07 (hand-rebuild, best body so far): DIFF 19.0% (22/116 insns),
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 18.0328% -> 19.8276% `volatile` keyword(s) removed from the body
// object .text 488B vs want 464B.  Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A2D10
//
// The m2c husk (family=m2c, 1.7%) declared 7 named args + 8 f64 args; the real
// function is **variadic** — the whole prologue is the ngccc varargs sequence.
// This draft is the first body built on that insight and reproduces the ENTIRE
// prologue *shape* (only the frame offsets are off): frame creation,
// link-register and condition-register save, callee-saved register save, then
// the saveregs triplet recording 3 named GP args and 0 FP args, then the
// incoming-argument register saves to their slots, then the conditional
// float-register save block — all byte-identical in the want.  The float save
// block and the 3-named-arg triplet value fall out of `__builtin_saveregs()`
// in a 3-named-arg `...` function, so NO stdarg.h / va_start is needed (this
// compiler has no stdarg.h and treats __builtin_va_start as an out-of-line
// implicit call — see src/wip/fn_80269F4C.c's header for the same discovery).
//
// WHAT IS STILL WRONG (single blocker, everything else is downstream):
//   the locals area is 8 bytes too small.  WANT: aq@0x70 (12B), p@0x80,
//   node/sentinel@0x88, saveregs triplet@0x90..0x9c, CR slot@0xa0, saved
//   r23..r31@0xa4..0xc0, LR@0xcc, frame 0xc8.  GOT: triplet@0x88, CR@0x98,
//   saved@0x9c, frame 0xc0 — i.e. exactly 8 bytes lower.  Adding 8 bytes of
//   *used* locals allocated before the saveregs temp moves every one of those
//   offsets into place (and the frame to 0xc8); 0x84/0x8c are never touched
//   in the want, so the extra 8 bytes belong to two more words of an
//   *unreferenced* slot (or an 8-byte-aligned local) — unknown which source
//   construct creates them.  TRY NEXT: a 16-byte iterator aggregate
//   {Node *cur; Node *sent; ...} declared before the saveregs call, or a
//   second va_list copy that is only assigned once.
//   NOTE: `Node * volatile p,node;` is what makes GOT's saved set exactly
//   r23..r31 (matching the want) — without it one more register (r22) is
//   saved.  The want reloads p from 0x80 inside the loop, i.e. p/node really
//   are memory-resident in the original too.
//
// BODY SHAPE (verified against the disasm; keep if resuming):
//   s32 fn(s32 arg0 /*r24: max matches*/, Node *arg1 /*r25*/, u32 arg2 /*r31:
//           how many va args to test*/, ...)
//   node = lbl_8037BB58;                    /* the list sentinel (global) */
//   p = node ? node->next : NULL;           /* unk4 = next */
//   count = 0;
//   while (p != node) {                     /* the global is RELOADED each
//                                              iteration (a call may change it) */
//       n = 0; aq = *ap;                    /* va_copy per outer iteration */
//       while (n < arg2) {                  /* do/while with an entry guard */
//           obj = *(void **)va_arg_word(&aq);          /* the expansion below */
//           vt = *(VT **)obj;                          /* obj's vptr */
//           if (vt->fn((char *)obj + vt->off, p->unk0) == 0) break;
//           n++;
//       }
//       if (n == arg2) { count++; ((VT *)arg1->unk0)->fn((char *)arg1 + off, p->unk0); }
//       if (arg0 >= 0 && count >= arg0) break;         /* arg0's sign test is
//                                       hoisted out of the loop (tested once,
//                                       branched inside the loop) */
//       p = p->next; node = lbl_8037BB58;
//   }
//   return count;
//   - the va_arg expansion (want 0x800A2DE8..0x800A2E30) is, in C:
//       g = (s8)aq.gpr;
//       if (g + 1 <= 8) { addr = (char *)aq.rsv + g*4; aq.gpr = (u8)g + 1; }
//       else { if (g <= 7) aq.gpr = 8; addr = aq.ovf; aq.ovf = (char *)aq.ovf + 4; }
//     (sign-extending counter load, small-arg limit check, scale-and-add with
//      counter bump, and an overflow path loading and bumping the overflow
//      pointer, sharing the tail bump-and-store), i.e. a 4-byte (word) va_arg.
//     The unreachable `g <= 7` arm survives this compiler's range analysis —
//     keep it.
//   - the two vcalls are the standard
//     `((s32(*)(void *,s32))vt->unk0xC)((char *)obj + *(s16 *)((char *)vt + 8), p->unk0)`
//     (indirect call through the vtable — never a counted branch) — same
//     idiom as the matched fn_80139600.
//   - lbl_8037BB58's global-pointer load is `extern Node *lbl_8037BB58;`
//     (address relocs are masked in the diff).

// family=hand range=0x800A2D10-0x800A2EE0 size=464B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct {
    s32 gpr;
    void *ovf;
    void *rsv;
} ap_t;

typedef struct Node {
    s32 unk0;
    struct Node *next;
} Node;

typedef struct VT {
    char pad[8];
    s16 off;
    char pad2[2];
    s32 (*fn)(void *, s32);
} VT;

extern Node *lbl_8037BB58;

s32 fn_800A2D10(s32 arg0, Node *arg1, u32 arg2, ...) {
    ap_t aq;
    ap_t *ap;
    Node * node;
    Node * p;
    s32 count;
    s32 n;
    void *obj;
    s32 g;
    void *addr;

    node = lbl_8037BB58;
    p = node ? node->next : NULL;
    __builtin_saveregs();
    ap = (ap_t *)((char *)&aq + 0x10);
    count = 0;
    while (p != node) {
        n = 0;
        aq = *ap;
        if (n < arg2) {
            do {
                g = (s8)aq.gpr;
                if (g + 1 <= 8) {
                    addr = (char *)aq.rsv + g * 4;
                    aq.gpr = (u8)g + 1;
                } else {
                    if (g <= 7) {
                        aq.gpr = 8;
                    }
                    addr = aq.ovf;
                    aq.ovf = (char *)aq.ovf + 4;
                }
                obj = *(void **)addr;
                if (((VT *)*(void **)obj)->fn((char *)obj + ((VT *)*(void **)obj)->off, p->unk0) == 0) {
                    break;
                }
                n += 1;
            } while (n < arg2);
        }
        if (n == (s32)arg2) {
            ((VT *)arg1->unk0)->fn((char *)arg1 + ((VT *)arg1->unk0)->off, p->unk0);
            count += 1;
        }
        if ((arg0 >= 0) && (count >= arg0)) {
            break;
        }
        p = p->next;
        node = lbl_8037BB58;
    }
    return count;
}
