// WIP DRAFT (non-matching) — semantic C reconstruction
// family=m2c range=0x800419C0-0x80041AC0 size=256B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-rerun-cse-after-loop
#include "types.h"

extern f32 lbl_80292388;
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);

// arg0 of fn_800419C0. Only +0x0C, +0x64, +0x70, +0x184 are touched.
typedef struct Obj_419C0 {
    char pad0x00[0x0C];
    s32 unk0x0C;
    char pad0x10[0x54];
    void *unk0x64;
    char pad0x68[0x08];
    void *unk0x70;
    char pad0x74[0x110];
    f32 unk0x184;
} Obj_419C0;

// the "link" object handed to CObject_AddRefLink / CObject_RemoveRefLink as
// arg1: {payload, next, prev} at +0/+4/+8 (those are the only offsets the two
// callees read or write).  The object itself is 32 bytes -- that size is what
// pins the 0x48 frame (Gsave 0x2c + 4*3 GPRs + 8*2 FPRs).
typedef struct RefLink_419C0 {
    void *obj;
    void *next;
    void *prev;
    char pad0x0C[0x14];
} RefLink_419C0;

void fn_800419C0(Obj_419C0 *arg0, f32 farg0) {
    RefLink_419C0 w;
    register RefLink_419C0 *wq __asm__("r9");
    RefLink_419C0 *lp;
    void *obj;
    void *next;

    if (!(arg0->unk0x0C & 0x8000)) {
        arg0->unk0x184 = farg0;
        arg0->unk0x0C |= 0x1000;
    }
    wq = &w;
    lp = wq;
    obj = arg0->unk0x64;
    wq->next = NULL;
    wq->prev = NULL;
    if (obj != NULL) {
        w.obj = obj;
        CObject_AddRefLink(obj, lp);
    }
    if (w.obj != NULL) {
        f32 one = lbl_80292388;
        do {
            fn_800419C0((Obj_419C0 *)w.obj, farg0 + one);
            next = ((Obj_419C0 *)w.obj)->unk0x70;
            if (w.obj != NULL) {
                CObject_RemoveRefLink(w.obj, lp);
                w.obj = NULL;
            }
            w.obj = next;
            if (next != NULL) {
                CObject_AddRefLink(next, lp);
            }
        } while (w.obj != NULL);
    }
    if (w.obj != NULL) {
        CObject_RemoveRefLink(w.obj, lp);
        w.obj = NULL;
    }
}

// === PARKED 2026-10-17: 87.5% (56/64), size-exact 256B. Gain came from
// hoisting the obj load into a pre-guard temp (`obj = arg0->unk0x64`) with
// `w.obj = obj` moved INSIDE the guard (matches want's store order, kills
// the alias reload). Do NOT pin obj to r3 and do NOT reassign arg0 to it:
// both collapse layout (30% or worse — the r3 pin sinks the obj store below
// the call setup; arg0 reassignment spills arg0 to r11 for the early
// block). Do NOT pin lp to r30 either (no effect on the call-arg choice).
// Residual: obj homes in r11 not r3 (lwz+cmpwi), first call uses mr r4,r9
// not r4,r30 (r9 still holds &w there; later calls correctly use r30 once
// r9 is clobbered by the const anchor), and the obj store sinks below the
// call setup. Single-pointer form (no wq) loses the addi/mr pair. Genuine
// allocator-choice wall — do not re-grind without a new lever.
// === PARKED (2026-10-01) ===
// 85.9% (55/64 instructions), object 256B == want 256B, size-exact.
// 55 of 64 words are byte-identical, including the whole 0x48 frame + 3-GPR /
// 2-FPR prologue, the entire loop body, the loop latch, the redundant
// post-loop `if (link.obj) RemoveRefLink(...)` block and the epilogue.
// The 9 residual diffs are all inside one 8-instruction window,
// 0x800419F4..0x80041A24 (the link-struct initialisation + the loop guard).
//
// WHAT IS ALREADY SOLVED (each was worth a large jump, all reproduced here):
//  * ngccc is ILP32 -> `void *` is 4 bytes; struct pads must be sized for
//    32-bit pointers or every displacement shifts (0x184 store cost 1 insn).
//  * the 32-byte `RefLink` local (pad0x0C[0x14]) is what produces frame 0x48
//    with Gsave 0x2c; a 12-byte struct gives 0x38 and stmw only r30.
//  * `while` must be `if (c) { do {...} while (c); }`; the `while` form loses
//    the loop-invariant `lfs f30` hoist out of the loop (2.4% -> 5.5% worse).
//  * `-fno-rerun-cse-after-loop` is load-bearing: it is what keeps the
//    post-loop `if (link.obj) RemoveRefLink(link.obj,&link); link.obj = 0;`
//    block alive.  Without it GCC proves the latch implies link.obj == 0 and
//    deletes the 6-word block (216B/18% vs 244B).
//  * `&w` must be held in a callee-saved register (r30), not rematerialised as
//    `addi r4, r1, 8` at each of the 5 call sites: that is what adds r29 to the
//    save set (stmw r29 rather than stmw r30) and forces the 0x48 frame.
//
// WHAT IS STILL WRONG AND WHY (the blocker, name it precisely):
// retail emits the two `link.next = 0` / `link.prev = 0` stores with a REGISTER
// base (`stw r0,8(r9)` / `stw r0,4(r9)`) yet still uses the just-stored
// `link.obj` value straight out of r3 for the guard and the first call
// (`stw r3,8(r1)` + `cmpwi r3,0`, no reload).  Plain C cannot produce both:
//  - frame-base stores (`w.next = 0;`) -> store-to-load forwarding works, the
//    guard uses r3, but reload.c folds the address back to `0xc(r1)`;
//  - register-base stores (`wq->next = 0;`, i.e. what retail needs) -> reload
//    cannot disambiguate MEM[r9+4]/MEM[r9+8] from MEM[.. + 0] (gcc 2.95
//    alias.c will not disambiguate two different constant offsets of the same
//    hard base), so it inserts `lwz r3, 8(r1)` and the load result is spilled
//    to r11 -> 5 of the 9 diffs.
//  Retail clearly ran with the frame-base form at alias-analysis time and had
//  local-alloc split the DECL-address pseudo into r9 + a copy in r30 later; I
//  could not get ngccc to split a frame-note pseudo.
// Remaining single-word items: `mr r4,r9` should be `mr r4,r30` for the first
// AddRefLink (r9 is call-clobbered so GCC reuses it before the first call), and
// the loop guard needs a dead `mr r3,r0` copy that retail's local-alloc
// emitted at both the guard and the latch.
// BONUS non-maskable diff found by hand (invisible to the 85.9%): the first
// guard's branch EXTENT.  Retail's `beq` at 0x80041A14 goes to 0x80041A20
// (re-tests link.obj); mine jumps straight to the epilogue (REL14 addend 0xe4)
// because ngccc jump-threaded the second test away.  Same instruction count,
// so this is a real 10th difference that want_got cannot show.
//
// NOT TRIED: (a) `volatile`-qualified link fields to pin the store addresses
// (would add volatile reloads elsewhere, likely a net loss);
// (b) a second pinned pointer (r10/r11) for the obj store so alias.c sees one
// base -- cannot help, the disambiguation failure is offset-vs-offset on one
// base; (c) hand-pinning r3 for the guard copy; (d) -mps-float / -O1 / -O3 and
// the remaining -fno-* flags (swept: -fno-schedule-insns, -fno-schedule-insns2,
// -fno-sched-interblock, -fno-sched-spec, -fno-expensive-optimizations,
// -fno-gcse, -fno-thread-jumps, -Os are all inert or worse here).
