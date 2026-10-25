// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003BD4C-0x8003BF64 (536B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_8029202C;
extern f32 lbl_80292038;
extern s32 lbl_803003E8;
extern char *lbl_803003F0;
s32 GetInteger(void *, s32, s32 *, s32);
s32 fn_80128C80(void *, s32, s32 *, s32);
s32 fn_80128978(void *, s32);
s32 fn_80128E04(void *, s32, s32 *, s32);
s32 fn_80053E7C(void *, void *);
s32 fn_8003ABA0(void *, s32);
void fn_80062528(s32, f32 *);
// STATUS 2026-10-02: 0.0% (m2c DIFF) -> 100% byte-exact, 0 emitted inline asm.
// Hand-rebuilt from want + the ADDRESS-ADJACENT promoted sibling src/fn_8003B9E0.c
// (AGENTS 6fn/6dc: solved src/ neighbour is the type+idiom oracle). It supplies
// `f32 sp8[4]` + a named `f32 *` base (split-base 6at-3) and fn_80062528's
// `void (s32, f32 *)` signature. Symbols: lbl_8029202C=1.0f, lbl_80292030=
// 0x4330000080000000 (the int->f64 pool), lbl_80292038=100.0f.
// Semantic fixes that mattered, in order of points:
//  1. L1 (6bc-1/6dh-2): pointer-valued global `lbl_803003F0` declared `extern char *`
//     and used BARE, replacing m2c's `*(s32 *)&lbl + 0x58` (which materialises the
//     full address). -> 6.4% -> 26.9%.
//  2. Locals from the real layout: `f32 sp8[4]` (was mega-merged `Unk_59AB5482`,
//     64 bytes) + `f32 vec[4]` + one out-param array -> object size-exact 536B.
//  3. Six missing/short prototypes (6de/6dg): GetInteger, fn_80128C80 (m2c called
//     it 3-arg; want passes 4 -> the `li r6,0` slot), fn_80053E7C x2.
//  4. `(s32*)lbl_8029202C` -> f32 store; m2c's `*(s32*)` for the 4th vector lane
//     would have cost an fctiwz/stfd/lwz/stw quadruple (6eh2 TELL 1).
//  5. Shared-exit LABEL (`ret1:`) instead of four textual `return 1`s. With the
//     returns written inline, cc1 crossjump-merged the TWO `fn_80062528` calls into
//     one shared `bl` at the function end; want keeps two `bl`s and shares only the
//     `li r3,1; b epi` block, which sits right after the FIRST call (6dp/6be block
//     placement). This was the last 69 points.
//  6. The three `(f32)(f64)sp28[k] / 100.0f` statements in slot order [0][1][2]
//     came out as want's stfs run [0x18][0x20][0x1c] first try (store-run
//     rotate-right, recipes 24/64).

bool fn_8003BD4C(void) {
    f32 sp8[4];
    f32 vec[4];
    s32 sp28[6];
    s32 temp_r3;
    f32 temp_f0;
    f32 *var_r9;
    s32 entry;
    var_r9 = sp8;
    temp_f0 = lbl_8029202C;
    var_r9[0] = temp_f0;
    var_r9[1] = temp_f0;
    var_r9[2] = temp_f0;
    var_r9[3] = temp_f0;
    temp_r3 = fn_80053E7C(var_r9, (void *) (lbl_803003F0 + 0x58));
    if (temp_r3 == 0) {
        sp28[0] = 0;
        if (fn_80128E04((void *) (lbl_803003F0 + 0x58), QB_BODY_SHAPE, &sp28[0], 0) == 0) { goto L2; }
        if (fn_80053E7C(var_r9, (void *) sp28[0]) == 0) { goto L2; }
    }
    fn_80062528(lbl_803003E8, var_r9);
ret1:
    return true;
L2:
    entry = fn_8003ABA0((void *) lbl_803003F0, QB_OBJECT_SCALING);
    if (entry == 0) { goto L0; }
    if (fn_80128978(entry, QB_USE_DEFAULT_SCALE) == 0) { goto L0; }
    GetInteger(entry, QB_USE_DEFAULT_SCALE, &sp28[1], 0);
    if (sp28[1] != 0) { goto L0; }
    if (fn_80128C80(entry, QB_X, &sp28[2], 0) == 0) { goto ret1; }
    if (fn_80128C80(entry, QB_Y, &sp28[3], 0) == 0) { goto ret1; }
    if (fn_80128C80(entry, QB_Z, &sp28[4], 0) == 0) { goto ret1; }
    vec[0] = (f32) (f64) sp28[2] / lbl_80292038;
    vec[1] = (f32) (f64) sp28[3] / lbl_80292038;
    vec[2] = (f32) (f64) sp28[4] / lbl_80292038;
    vec[3] = lbl_8029202C;
    fn_80062528(lbl_803003E8, vec);
    goto ret1;
L0:
    return false;
}
