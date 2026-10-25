// WIP DRAFT (non-matching) — C body REBUILT from the disassembly by hand
// family=m2c range=0x8004BFE4-0x8004C110 size=300B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics recovered (composite/COM "focus" bookkeeping — see the matched
// sibling src/fn_8004C2DC.c, same self+0x5A4 list-of-lists):
//   arg0 = the container: s32 list[4] at +0x5A4, s32 flags[4] at +0x5B4,
//          free-slot pool of 48 records of 0x1C bytes at +0x64.
//   arg1 = CObject **in (the caller passes &local, so every use in the want
//          is a LOAD: `lwz rX, 0(r27)` — it is an input, not an out-param).
//   arg2 = list index.
// Walk the 4 lists; if the wanted object sits in list[arg2], clear its 0x18
// flag and return.  Otherwise claim the first free pool slot, link it at the
// end of the walk (after `prev`, or at list[arg2] if nothing was walked),
// set flags[arg2].
//
// Three non-obvious things this body has to get right:
//  * the 0x1C stride needs a real 0x1C-sized record type — Unk_DB0E2BAB is
//    0xBC bytes, so `pool[j]` on it emits `addi r31,r31,0xb8` (wrong); the
//    local `Slot` struct below is what reproduces the want's
//    `addi r31,r31,0x1c` walk TOGETHER WITH the separate `cmpwi r9,0x2f`
//    counter (walking a plain `Slot*` + counter instead gets strength-
//    reduced into a pointer-END compare `cmpw r31,r0`, which the want does
//    not have).
//  * doc-09 store rotation: the three field stores go in the source in the
//    order [0xC, 0x10, 0x18] to be emitted [0x18, 0xC, 0x10].
//  * `arg2 << 2` spelled out in the two indexed stores; with a plain
//    `tbl[arg2]` / `flags[arg2]` the address is built index-first and both
//    stores come out `stwx rS,rIndex,rBase` instead of the want's
//    `stwx rS,rBase,rIndex`.
// The r25 pin is recipe §6a-6 (pin-a-copy): ngccc's global.c gives the
// r25/r26 home of these two scalar params to arg2/arg0 (arg0 loses on
// reference count); pinning arg0's copy reproduces want's order.  Pinning
// r26 as well is wrong — the r26 pin steals r22 for the arg2 copy (25%).
//
// 2026-10-20: pool/slot/flags assignment-order re-triage REVERTED (DIFF:
// `slot = pool` before `flags = ...` collapses the pool/flags webs onto the
// pinned r25 exactly as the 10-02 note predicts; order [pool, flags, slot]
// is load-bearing, restored to 93.3%. The addi-last lever remains the
// hoisted-invariant discovery order, not source order.
// 2026-10-15: dependency-barrier attempt on the flags-addi REVERTED (DIFF:
// staging `a2s = arg2<<2` + `__asm__("" : "+r"(flags) : "r"(a2s))` steals
// the pinned-r25 allocation globally — stmw r23, homes reshuffled from the
// prologue on. Unlike fn_8018BC14's entry window (scratch regs), a barrier on
// a PINNED home register perturbs coloring function-wide. Do not retry
// barriers on pinned homes here.
// PARKED 2026-10-02 (w75/0x8004BFE4): 93.3% (70/75 words).  Size exact 300B,
// frame exact (-0x30, stmw r22), object has no .rodata, and all 12 local
// branch targets verified by hand against the want's (object .rela.text
// addends).  Everything else matches: both loop shapes, the degenerate
// `cmpw/beq` pair, the mfcr/mtcrf 0x80 CR-0 carry across the fn_8004C410
// call (doc-28 "conditions consumed close together"), `cmpwi cr7` +
// mfcr/slwi 0x1c for the hoisted `prev != 0` test across the
// CObject_AddRefLink call, both `li` constants sharing r23, the doc-09
// store rotation, and both stwx operand orders.
// Residual = ONE word, and it is a scheduling position, not a semantics
// problem: the block-2 preheader `addi r25,r25,0x5b4` (the flags[] base) is
// emitted 2nd (0x8004C07C) where want has it 7th (0x8004C08C, after both
// `slwi`s), which rotates the 4 following words and costs the 5 diffs.
// Tried for it: flags[] assigned before/after pool[], with/without the
// `pool` local, flags[] assigned in the pool loop's for-init, flags[]
// derived from tbl (all three destroy the whole allocation — cc1 then
// coalesces the pool/flags addresses onto the pinned r25 and the frame goes
// to 0x38), flags[] assigned inside the loop body (top-of-body 8%, taken arm
// 68%), flags[] inlined at the store (produces `add r9,r5,r25` +
// `stw r23,0x5b4(r9)` displacement form instead of the want's
// displacement-free `stwx r23,r25,r5`).
#include "types.h"
#include "structs.h"

typedef struct Slot Slot;
struct Slot {
    Unk_78674569 *obj;    /* 0x00 — the CObject this slot tracks */
    s32 unk0x4;           /* link next, written by CObject_AddRefLink */
    s32 unk0x8;           /* link prev, written by CObject_AddRefLink */
    s32 unk0xC;           /* snapshot of obj->0x18 */
    Slot *next;           /* 0x10 — chain inside one of the 4 lists */
    s32 unk0x14;
    s32 unk0x18;          /* "visible" flag */
};

void fn_8004C410(s32, Slot *);
void CObject_AddRefLink(Unk_78674569 *, Slot *);

void fn_8004BFE4(s32 arg0, Unk_78674569 **arg1, s32 arg2) {
    register s32 self __asm__("r25");
    Slot **tbl;
    Slot *pool;
    Slot **p;
    Slot *prev = NULL;
    Slot *node;
    Slot *slot;
    Unk_78674569 *obj;
    s32 i;
    s32 j;
    s32 *flags;

    self = arg0;
    tbl = (Slot **)((char *)self + 0x5A4);
    for (i = 0, p = tbl; i <= 3; i++) {
        for (node = *p++; node != NULL; node = node->next) {
            fn_8004C410(self, node);
            if (node->obj == arg1[0] && arg2 == i) {
                node->unk0x18 = 0;
                return;
            }
            prev = node;
        }
    }
    pool = (Slot *)((char *)self + 0x64);
    flags = (s32 *)((char *)self + 0x5B4);
    slot = pool;
    for (j = 0; j <= 0x2F; j++) {
        if (slot->obj == NULL) {
            obj = arg1[0];
            slot->obj = obj;
            if (obj != NULL) {
                CObject_AddRefLink(obj, slot);
            }
            slot->unk0xC = arg1[0]->unk0x18;
            slot->next = NULL;
            slot->unk0x18 = 0;
            if (prev != NULL) {
                prev->next = slot;
            } else {
                *(Slot **)((char *)tbl + (arg2 << 2)) = slot;
            }
            *(s32 *)((char *)flags + (arg2 << 2)) = 1;
            return;
        }
        slot++;
    }
}