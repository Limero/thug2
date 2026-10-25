// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 4.2% while git revision fd28c841b scores 8.9%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 12 distinct committed bodies.
//
// REBUILT 2026-10-06. The restored body above
// had no `#include` line and no `family=` marker, so it could not compile at
// all (it uses u32/f32/NULL) — i.e. its sweep verdict was FAIL, not 8.9%.
// This is a semantic re-decode off the retail listing (tmp_bundles/8003BAAC.md)
// with the real types and named constants:
//
//   * PROTOTYPE: retail's prologue is `mr r30,r4 ; mr r31,r5`, i.e. r4 and r5
//     are the two LIVE parameters and r3 is never read (its first use is
//     `lwz r3,0x3f0(r29)`).  The old two-parameter body therefore put the
//     third argument in the wrong register.  Signature is
//     (unused, ctx, id) -> s32.
//   * The `fn_8003AB44` result is CHAINED straight into `fn_80128E04` as its
//     first argument (retail sets only r4/r5/r6 after the `bl`; r3 carries the
//     return), so the call is nested.  The old body dropped it and passed the
//     unused context slot instead.
//   * CONSTANTS: 0x8029201C = 1.0f, 0x80292028 = 100.0f, both registered in
//     .rodata2 (defined by src/r2d_80292014.c).  Referenced as symbols, not as
//     raw address literals (the old `*(f32 *)0x80292028` compiles to a load
//     from address 0).  The `xoris` + 0x80292020 double magic on sp20/24/28 is
//     GCC 2.95's s32->f32 conversion, so the three scale factors are plain
//     `(f32)field / 100.0f`.
//   * HASHES resolved via qb_constants.h: 0x5A96985D = QB_USE_DEFAULT_SCALE,
//     0x7323E97C = QB_X, 0x0424D9EA = QB_Y, 0x9D2D8850 = QB_Z,
//     0x20D9AC2F = QB_NONLOCAL_BONES.
//   * Semantics: gated on QB_USE_DEFAULT_SCALE presence; read the X/Y/Z scale
//     percentages; fetch the QB_NONLOCAL_BONES table; for every entry whose
//     checksum id is NOT found again in the QB_NONLOCAL_BONES table, scale its
//     4-float vector by (factor/100) and write it back.  v[3] is initialised
//     to 1.0f before the loop (the homogeneous component).
//
// PARKED 2026-10-06: register-allocation pivot not reachable from this body.
// The outer loop index and the QB_NONLOCAL_BONES table pointer share one
// callee-saved register in retail (r30) — the retail compiler computes
// `next = i + 1` early (0x8003BC10, before r30 is overwritten by the table
// pointer at 0x8003BCC8) and restores it with `mr r30,r27` at the latch;
// ngccc colours the two independently, which rotates r23..r31 and the
// f30/f31 homes and shifts every following word.  Also unverified without a
// compiler run: the `fn_8003ABA0` / `fn_8003AB44` callee register sets and
// the exact `stfs`/`fmuls` interleave of the three scale statements.
// WANT vs GOT differ in register colouring / statement interleave, not in
// semantics or types.  Best body above.
// family=m2c range=0x8003BAAC-0x8003BD4C size=672B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

/* QB lookup table: only +4 (the entry count) is read here. */
typedef struct {
    char pad0x00[4];
    u32 count;
} Node;

extern char lbl_803003F0[];   /* profile / script context root */
extern char lbl_803003EC[];   /* nonlocal-bones helper handle */
extern f32 lbl_8029201C;      /* 1.0f   */
extern f32 lbl_80292028;      /* 100.0f */

s32 fn_8003ABA0(s32, s32);
void *fn_8003AB44(s32, s32);
void fn_80128E04(void *, void *, void *, s32);
s32 fn_80128978(s32, s32);
s32 fn_80128228(s32, s32, s32 *, s32);
s32 fn_80128C80(s32, s32, s32 *, s32);
Node *fn_801259C8(s32, s32);
s32 fn_801294BC(Node *, s32);
s32 fn_80037BF0(s32, s32, void *);
s32 fn_80037C40(s32, s32, void *, s32);

s32 fn_8003BAAC(s32 arg0, s32 arg1, s32 arg2) {
    Vec4 v;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    Node *list;
    Node *found;
    s32 id;
    s32 next;
    s32 i;
    s32 j;
    s32 flag;

    sp18 = fn_8003ABA0(*(s32 *)lbl_803003F0, arg1);
    if (sp18 == 0) {
        if (arg2 != 0) {
            fn_80128E04(fn_8003AB44(*(s32 *)lbl_803003F0, arg2), (void *)arg1, &sp18, 0);
        }
        if (sp18 == 0) {
            return 0;
        }
    }
    if (fn_80128978(sp18, QB_USE_DEFAULT_SCALE) == 0) {
        return 0;
    }
    fn_80128228(sp18, QB_USE_DEFAULT_SCALE, &sp1C, 0);
    if (sp1C != 0) {
        return 0;
    }
    if (fn_80128C80(sp18, QB_X, &sp20, 0) == 0) {
        return 0;
    }
    if (fn_80128C80(sp18, QB_Y, &sp24, 0) == 0) {
        return 0;
    }
    if (fn_80128C80(sp18, QB_Z, &sp28, 0) == 0) {
        return 0;
    }
    list = fn_801259C8(arg1, 0);
    if (list == 0) {
        return 0;
    }
    v.w = lbl_8029201C;
    i = 0;
    while ((u32)i < list->count) {
        id = fn_801294BC(list, i);
        next = i + 1;
        flag = 1;
        fn_80037BF0(*(s32 *)lbl_803003EC, id, &v);
        v.x = v.x * ((f32)sp20 / lbl_80292028);
        v.y = v.y * ((f32)sp24 / lbl_80292028);
        v.z = v.z * ((f32)sp28 / lbl_80292028);
        found = fn_801259C8(QB_NONLOCAL_BONES, 0);
        if (found != 0) {
            j = 0;
            while ((u32)j < found->count) {
                if (fn_801294BC(found, j) == id) {
                    flag = 0;
                }
                j += 1;
            }
        }
        fn_80037C40(*(s32 *)lbl_803003EC, id, &v, flag);
        i = next;
    }
    return 0;
}

// NOTE (2026-10-06) — build/verify status:
//  * `arg0` is intentionally unused; it must stay in the prototype so the two
//    live parameters land in r4/r5 like retail.
//  * `next` mirrors retail's EARLY `addi r27,r30,1` (before the loop index's
//    register is reused for the QB_NONLOCAL_BONES table pointer); dropping it
//    for a plain `i++` latch is the alternative if this stays parked.
//  * If the three scale statements mis-schedule, the retail order is
//    (v.x, v.y, v.z) with each factor converted and divided BEFORE its
//    multiply — keep the parentheses so the fdivs is not folded into the fmul.
//  * No inline __asm__; no other file touched; nothing registered.
