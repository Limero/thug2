// WIP DRAFT (non-matching) - hand semantic reconstruction.
// Walks a singly-linked node list hanging off arg0->unk0x10 and calls
// fn_800645D8(node, arg1) on every node whose 0x10000 flag bit is set.
// family=m2c range=0x80068B58-0x80068C28 size=208B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS 2026-10-04: 28.9%, size 188B vs want 208B (5 words short).
// The m2c husk scored 3.5%. Four semantic fixes are already in and all are
// load-bearing:
//   * the link cells are a distinct 8-byte-ish type: a `Link68B58` whose
//     `unk0x4 == -1` means "dead", and the node is the link MINUS 0xC
//     (`addi r31, r9, -0xc`). Declaring the node/link split this way is what
//     produces the `cmpwi r0,-1 / bne / li r9,0` idiom twice (head + latch)
//     instead of a fused test.
//   * the loop latch is the m2c two-step (`var_r0 = NULL; if (lnk) var_r0 =
//     lnk - 0xC; var_r31 = var_r0;`), which is what yields the
//     `or. r31, r0, r0` bottom-test + `bne` back-edge. Collapsing it to
//     `node = lnk ? lnk - 0xC : NULL` drops the `or.`.
//   * `sp8` (r1+8) is written EVERY iteration with the constant 0x10000 but is
//     never read: it is a dead volatile store, so `volatile s32 sp8` is the
//     only way to keep it (a plain local is deleted, costing the frame 8 bytes).
//   * the 0x10000 mask must be a named `s32 mask` local, not a literal, so the
//     constant is hoisted into a callee-saved register (retail: `lis r28,1`).
//
// PARKED 2026-10-04 - remaining blocker is REGISTER ASSIGNMENT, not semantics:
// retail uses FOUR callee-saved regs (r28 = hoisted mask, r29 = arg0,
// r30 = arg1, r31 = node) and copies BOTH incoming args up front
// (`mr r29,r3 ; mr r30,r4 ; lwz r9,0x10(r29)`); the draft only needs three
// (r29 = arg1, r30 = mask, r31 = node) and emits `lwz r9,0x10(r3)` before the
// arg1 copy. arg0 has no live use inside the loop in EITHER version, so
// whether ngccc sinks it into r29/r30 or gives it a callee-saved reg comes
// down to allocator ordering that no source spelling tried here steers:
//   - `mask` as a plain local / const / literal / `volatile` (all 4 tried),
//   - explicit `Root68B58 *self = arg0;` plus a use inside the loop,
//   - an `if/else` and a `while` loop shape for the head test,
//   - the m2c `var_cr*` boolean temporaries for the flag test.
// All land between 5.8% and 30.8% with the same 5-word shortfall. This is the
// same class as the fn_800A95EC PS register-pinning park: it needs asm, which
// is out of scope. Best body preserved below.
typedef struct Link68B58 { char pad0[4]; s32 unk0x4; } Link68B58;
typedef struct Node68B58 { char pad0[0x18]; Link68B58 *unk0x18; char pad1[0x110]; s32 unk0x128; } Node68B58;
typedef struct Holder68B58 { char pad0[0xC]; Link68B58 *unk0xC; } Holder68B58;
typedef struct Root68B58 { char pad0[0x10]; Holder68B58 *unk0x10; } Root68B58;
void fn_800645D8(Node68B58 *, void *);
void fn_80068B58(Root68B58 *arg0, void *arg1) {
    volatile s32 sp8;
    s32 mask = 0x10000;
    Link68B58 *lnk;
    Node68B58 *var_r31;
    Node68B58 *var_r0;
    s32 flag;

    if (arg0->unk0x10 != NULL) {
        lnk = arg0->unk0x10->unk0xC;
        if (lnk->unk0x4 == -1) { lnk = NULL; }
        var_r31 = NULL;
        if (lnk != NULL) { var_r31 = (Node68B58 *)((char *)lnk - 0xC); }
        if (var_r31 != NULL) {
            do {
                sp8 = mask;
                flag = 1;
                if (!(var_r31->unk0x128 & mask)) { flag = 0; }
                if (flag != 0) { fn_800645D8(var_r31, arg1); }
                lnk = var_r31->unk0x18;
                if (lnk->unk0x4 == -1) { lnk = NULL; }
                var_r0 = NULL;
                if (lnk != NULL) { var_r0 = (Node68B58 *)((char *)lnk - 0xC); }
                var_r31 = var_r0;
            } while (var_r31 != NULL);
        }
    }
}
