// WIP DRAFT (non-matching) — hand-reconstructed from the retail bytes,
// replacing the 2026-09-15 m2c bulk-fill body (which was 4.12% DIFF).
// family=m2c range=0x80085394-0x8008569C size=776B
// FLAG: -Os -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (regalloc+frame+prologue-schedule):
//   best measured 15.98% masked (163/194 words differ) with the FLAG line
//   below, object 784B vs want 776B — up from 4.12% for the previous body.
//   Semantics, declared types, local frame offsets, the MMIO light FIFO
//   address/widths and the callee prototypes are all now retail-correct;
//   what is left is allocation/scheduling, see the residual list at the
//   bottom of this file.
// ---------------------------------------------------------------------------
// Retail facts this body encodes (verified instruction by instruction):
//   * frame 0xc8, saves f30/f31 (750.0f, 128.0f loaded once before the
//     do-while) + r23..r31; local area 0x08..0x93.
//   * locals: struct A @0x08 (0x20), struct B @0x28 (0x20), 7-float
//     projection @0x48 (GXGetProjectionv writes +0x00..+0x18), u32 @0x68,
//     4-byte colour @0x6C, compiler double temp @0x88.
//   * 0x86D3EFE6 = 750.0f and 0x43000000 = 128.0f are the .rodata2 floats
//     lbl_8029659C / lbl_802965A0 (0x86D3EFE6 is loaded with lis+ori+stw, so
//     A.f0 is written from an *integer* bit pattern, not an f32 literal).
//   * lbl_80366DC8 is a .bss float[4]; the three colour channels are
//     (s8)(lbl_80366DC8[i] * 128.0f) -> lfs/fmuls/fctiwz/stfd+lwz/stb.
//   * the light FIFO is 0xCC008000 + 0x800, written u8 0x10 / u16 0 /
//     u16 0x1025 / f32 (PE light block) — the m2c draft wrote 0xCC008000
//     three times as s8.
//   * lbl_80301430 is a 4-byte .data object used as a *value*
//     (lwz r3,0x1430(r30)), not a pointer to dereference.
//   * fn_8001f2d8 is deliberately left UNPROTOTYPED: WANT has
//     `crclr cr1eq` before that one `bl` and none before the other 22.
//   * the inner-loop record is 0x48 bytes: f32[3]@0, u32@0x10, s16@0x14,
//     s16@0x16, repeated three times.
// ---------------------------------------------------------------------------
extern s32 lbl_80301430;
extern f32 lbl_8029659C;
extern f32 lbl_802965A0;
extern f32 lbl_80366DC8[4];

void fn_8001f298(s32, s32, s32, s32, s32, s32, s32);
void fn_8006f324(s32);
void *fn_8006f338(s32, s32);
void fn_800231c4(void *, void *, s32, s32, s32, s32);
void fn_8001e6f0(s32, s32, s32, s32, s32);
void fn_8001faa4(s32, s32, s32, s32, s32);
void fn_8001e248(s32, s32, s32, s32, s32, s32, s32);
void fn_80020494(void *);
void fn_8001ef84(s32, s32 *);
void fn_8001efbc(s32, s32 *);
void fn_8001f0a0(s32, s32, u16);
void fn_8001f0f8(f32, f32, f32);
void fn_8001f1d4(s32);
void fn_8001f250(s16, s16);
void fn_8001f0f4(void);

typedef struct {
    s32 f0;
    s8 f4;
    s8 f5;
    s8 f6;
    s8 pad7[0x19];
} A_t;

typedef struct {
    s32 f0;
    s16 f4;
    s8 f6;
    s8 f7;
    s8 pad8[4];
    s8 fC;
    s8 fD;
    s8 fE;
    s8 fF;
    s16 f10;
    s8 pad12[4];
    s8 f16;
    s8 pad17[9];
} B_t;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 pad;
} Proj_t;

typedef struct {
    s8 r;
    s8 g;
    s8 b;
    s8 a;
    s8 pad[0x14];
} Color_t;

typedef struct {
    s32 arg0;
    Color_t col;
} Pair_t;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    s32 padC;
    s32 col0;
    s16 u0;
    s16 v0;
    f32 x1;
    f32 y1;
    f32 z1;
    s32 pad24;
    s32 col1;
    s16 u1;
    s16 v1;
    f32 x2;
    f32 y2;
    f32 z2;
    s32 pad3C;
    s32 col2;
    s16 u2;
    s16 v2;
} Elem_t;

typedef struct {
    s32 pad0[0x2A00];
    s32 count;
    s32 pad2A04[2];
    s32 idx;
    Elem_t e[1];
} Obj_t;

void fn_80085394(void) {
    A_t a;
    B_t b;
    Proj_t proj;
    Pair_t P;

    Obj_t *var_r29;
    Elem_t *var_r30;
    s32 var_r31;
    f32 temp_f30;
    f32 temp_f31;

    a.f0 = 0x86D3EFE6;
    b.fF = 0xFF;
    a.f5 = 1;
    a.f6 = 2;
    b.f4 = 0x61;
    b.f6 = 5;
    b.f10 = 0;
    b.fE = 0x80;
    a.f4 = 1;
    b.f0 = 0;
    b.f16 = 0;
    b.f7 = 0;
    b.fC = 0x80;
    b.fD = 0x80;
    fn_8001f298(1, 3, 1, 1, 5, 0x61, 2);
    fn_8006f324(lbl_80301430);
    var_r29 = fn_8006f338(lbl_80301430, 0);
    if (var_r29 != NULL) {
        temp_f30 = lbl_8029659C;
        temp_f31 = lbl_802965A0;
        do {
            if (var_r29->count >= 0) {
                b.f0 = var_r29->idx;
                fn_800231c4(&a, &b, 1, 1, 0, 0);
                var_r30 = var_r29->e;
                var_r31 = 0;
                fn_8001e6f0(0, 1, 4, 0, 0x7D);
                fn_8001faa4(0, 0x3C, 0x3C, 0x3C, 0x3C);
                fn_8001e248(4, 1, 1, 0, 0, 0, 2);
                fn_80020494(&proj);
                P.col.r = (s8)(lbl_80366DC8[0] * temp_f31);
                P.col.g = (s8)(lbl_80366DC8[1] * temp_f31);
                P.col.b = (s8)(lbl_80366DC8[2] * temp_f31);
                P.col.a = 0xFF;
                *(s8 *)0xCC008800 = 0x10;
                *(s16 *)0xCC008800 = 0;
                *(s16 *)0xCC008800 = 0x1025;
                P.arg0 = *(s32 *)&P.col;
                *(f32 *)0xCC008800 = proj.f14 * temp_f30 + proj.f18;
                fn_8001ef84(4, &P.arg0);
                P.arg0 = *(s32 *)&P.col;
                fn_8001efbc(4, &P.arg0);
                fn_8001f2d8(3, 9, 1, 0xB, 1, 0xD, 1);
                fn_8001f0a0(0x90, 6, (u16)((var_r29->count + 1) * 3));
                if ((var_r29->count + 1) > 0) {
                    do {
                        var_r31 += 1;
                        fn_8001f0f8(var_r30->x, var_r30->y, var_r30->z);
                        fn_8001f1d4(var_r30->col0);
                        fn_8001f250(var_r30->u0, var_r30->v0);
                        fn_8001f0f8(var_r30->x1, var_r30->y1, var_r30->z1);
                        fn_8001f1d4(var_r30->col1);
                        fn_8001f250(var_r30->u1, var_r30->v1);
                        fn_8001f0f8(var_r30->x2, var_r30->y2, var_r30->z2);
                        fn_8001f1d4(var_r30->col2);
                        fn_8001f250(var_r30->u2, var_r30->v2);
                        var_r30 += 1;
                    } while (var_r31 < (var_r29->count + 1));
                }
                fn_8001f0f4();
            }
            var_r29 = fn_8006f338(lbl_80301430, 0);
        } while (var_r29 != NULL);
    }
}

// ---------------------------------------------------------------------------
// Residual (masked 15.98%, object still 2 words long):
//   1. prologue: got `stwu -0xc0 / stmw r27,0x9c` vs want `-0xc8 / stmw r23,
//      0x94` — ngccc allocates 2 fewer callee-saved GPRs than the game
//      compiler and therefore an 8-byte-smaller frame.  Getting the local
//      area to the want's 0x8C *and* the double temp to 0x88 and the save
//      area to 0x94 simultaneously was not reachable: an array/`volatile
//      double` pad always lands BELOW the 4-byte scalars in ngccc's local
//      area and pushes arg0/colour up (probed pad sizes 0x00..0x30, as first
//      local and as last local).  Padding the *last* local (Color_t.pad)
//      is the only placement that keeps arg0@0x68 / colour@0x6C.
//   2. the 14-field initialiser block: same instruction SET, totally
//      different order.  WANT materialises all eight constants first
//      (lis/ori + 7 li) and then emits the 14 stores, reusing one register
//      per distinct value across stores and call args (49 li total);
//      ngccc re-materialises 1/5/0x61/2 a second time for the call args
//      (53 li).  Store order per recipes §4p/24/64 is a scheduler coin flip.
//   3. `addis r29,r3,1` + negative displacements (-0x5800/-0x57f4/-0x57f0)
//      for the 0x2A00/0x2A0C/0x2A10 object fields instead of WANT's plain
//      `lwz r0,0x2a00(r29)`; one CSE'd pseudo (doc 177 class).
//   4. MMIO: ngccc materialises 0xCC008800 into a register (`lis`+`ori`,
//      0(rX)) instead of WANT's `lis 0xCC01` + `-0x8000(rX)` displacement
//      form.  An `extern s8 lbl_CC008800[]` DOES give the displacement form
//      (worth +1 instruction; 14.4% vs 15.98% masked under the
//      final flags) but there is no ELF symbol at 0xCC008800, so it would
//      break the link at promote time — deliberately not used.
//   5. one extra `addi`/`mr` in the colour block and one missing `sth`
//      (WANT has 4: B.f4, B.f10, light 0, light 0x1025).
// Ruled out: -O/-O1/-O2/-O3, -Os, -fno-sched-interblock, -fno-sched-spec,
// -fno-gcse, -fno-schedule-insns2 and all -Os combinations (best is
// -Os -fno-schedule-insns); 6- vs 7-arg fn_8001f298 (want's r9 = 0 from the
// B.f0 store, not a 7th `li`); arg0/colour declaration order, merged
// Loc_t object, and every 4-byte pad size 0x00..0x30 in four positions.
