// PARKED 2026-10-04: best body is 42.59% masked (31/54 words differ),
// SIZE-EXACT (216B == want 216B). Rebuilt from the want disassembly; the m2c
// draft was 352B (a 136B over-generation) and scored ~11%.
//
// SEMANTICS (want, 216B): `ScriptGetScreenElementDims(node, qb)` —
//   GetElement(&sp8, lbl_80300434, node, QB_ID, 1);          // 5 args, NOT 6
//   w = (s32)(obj->unk0x178 * fn_800422D8(&obj->unk0x88));
//   h = (s32)(obj->unk0x17C * fn_800422E0(&obj->unk0x88));
//   AddInteger(qb->unk0x18, QB_WIDTH,  w);                   // fn_80127684
//   AddInteger(qb->unk0x18, QB_HEIGHT, h);
//   if (sp8) { fn_8009DFC0(&sp8); sp8 = 0; }
//   return 1;
// `fctiwz f0` + `stfd f0,0x20(r1)` + `lwz r29,0x24(r1)` is ngccc's `(s32)`
// truncating cast of an f32 — no manual float-to-int code needed.
//
// WHAT ACTUALLY MOVED THE SCORE (all type/prototype fixes, no casts):
//   * GetElement is 5-arg, not 6. The m2c draft passed a 6th `0x80300000`;
//     that argument is a LITERAL in the want? No — it is ABSENT. The 6-arg
//     call makes ngccc materialise a dead 6th slot and the whole arg-setup
//     block slides. With 5 args the object is 216B (was 300B).
//   * Unk_C7387A53.unk0x88 / unk0x178 / unk0x17C are typed `s32` in
//     include/structs.h but the want loads them with `lfs` and
//     passes `&unk0x88` to the f32-returning fn_800422D8/422E0. Reading them
//     through `f32` LVALUES (`*(f32 *)&obj->unk0x178`,
//     `fn_800422D8((f32 *)&obj->unk0x88)`) is what removed the bogus
//     int->double conversion sequences (300B -> 216B) — same score as
//     re-typing the struct fields, but WITHOUT the collateral damage:
//     those three fields are POLYMORPHIC across the game. Re-typing
//     unk0x88 to f32 broke matched fn_80014D54 (`memcpy(arg0->unk0x84,
//     arg0->unk0x88, arg3)` — it is a POINTER there) and re-typing
//     unk0x17C to f32 broke matched fn_801BECBC (`if (arg0->unk0x17C == 0)`,
//     an integer compare; its object then failed tools/fix_fp_pool.py with
//     "cannot resolve original target for pool slot +0x0"). DO NOT re-type
//     these fields in the shared struct — go through f32 lvalues.
//   * `void * volatile sp8` is load-bearing: without volatile GCC hoists
//     `&sp8` into r31 for the whole function and never reloads it, whereas
//     the want re-reads `8(r1)` before every use. volatile forces the
//     reload web and keeps the object size-exact (35% -> 42.6%).
//   * `f32 px` split out for the FIRST multiply only: the want does
//     `lfs f31,0x178(r9)` BEFORE `bl fn_800422D8` and `fmuls f31,f31,f1`
//     after, i.e. the operand crosses the call in f31 (a callee-saved FPR).
//     Inlining it lets ngccc use a caller-saved FPR and drops the
//     `stfd f31`/`lfd f31` pair entirely. The second multiply is inlined
//     (f0) because the want reloads `lfs f0,0x17c(r9)` after its call.
//
// REMAINING WALL (31 diffs, two causes):
//   (a) `stmw r28,0x28(r1)` vs got's `stmw r27,0x24(r1)`: want keeps arg1
//       in r28, GCC picks r27. A `register CScript *qb __asm__("r28")` pin
//       does NOT fix it — pinning r28 pushes GCC to r27 anyway and costs 4
//       bytes (220B). Same class as recipes §6bw (arg-home register choice).
//   (b) the fctiwz scratch double lands at 0x18(r1) instead of want's
//       0x20(r1), which cascades every subsequent displacement. Padding the
//       frame with `volatile double _dummy` moves it but overshoots the
//       object to 224B; removing the `obj` local to force the reload web
//       also overshoots (224B). The 216B shape only exists in the exact
//       `obj` + `volatile sp8` + single-`px`-split configuration.
// Non-fixes tried: `volatile double _dummy` frame padding (224B), r28 arg
// pin (220B), dropping the obj local (224B), `f32 volatile px` (224B,
// 1.9%), splitting the `(s32)` cast into its own statement (no change).
//
// Verify: LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/score_wip.py 0x8004CEA4 src/wip/fn_8004CEA4.c
// WIP DRAFT (non-matching) — C body rebuilt from the want disassembly 2026-10-04
// family=m2c range=0x8004CEA4-0x8004CF7C size=216B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void *lbl_80300434;

void *GetElement(void *, void *, void *, s32, s32);
f32 fn_800422D8(f32 *);
f32 fn_800422E0(f32 *);
void fn_80127684(void *, s32, s32);
void fn_8009DFC0(void *);

bool ScriptGetScreenElementDims(void *arg0, CScript *arg1) {
    // volatile: the want re-reads 8(r1) before every use instead of keeping
    // &sp8 in a register across the function.
    void * volatile sp8;
    Unk_C7387A53 *obj;
    s32 w;
    s32 h;
    f32 px;

    GetElement(&sp8, lbl_80300434, arg0, QB_ID, 1);
    obj = sp8;
    // Unk_C7387A53.unk0x88/unk0x178/unk0x17C are read as f32 here but are
    // `s32` in the shared struct (fn_801BECBC compares unk0x17C against 0 as
    // an integer), so go through f32 lvalues rather than re-typing the struct.
    px = *(f32 *)&obj->unk0x178;
    w = (s32)(px * fn_800422D8((f32 *)&obj->unk0x88));
    h = (s32)(*(f32 *)&obj->unk0x17C * fn_800422E0((f32 *)&obj->unk0x88));
    fn_80127684(arg1->unk0x18, QB_WIDTH, w);
    fn_80127684(arg1->unk0x18, QB_HEIGHT, h);
    if (sp8 != NULL) {
        fn_8009DFC0(&sp8);
        sp8 = NULL;
    }
    return true;
}
