// WIP DRAFT (non-matching) — hand-reconstructed 2026-10-05 from the DOL disasm.
// family=hand range=0x800AB528-0x800AB604 size=220B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05.  Score 4.5% (m2c skeleton) -> 40.0% (this body), masked
// and TRUE agree (no internal branches in this function).  got=212B want=220B.
//
// WHAT WAS FIXED (this is the whole reason the old draft scored 4.5%):
// Unk_6849630D declares every 0x347x..0x34Dx member as s32, so the m2c body's
// plain `arg0->unk0x3478 = temp_f13;` compiled to fctiwz + stw (int truncation)
// instead of the original `stfs`.  All float members must go through
// `*(f32 *)((char *)arg0 + 0xNNNN) = x;` (the idiom used by the promoted
// sibling src/fn_800ABAB0.c).  The three .rodata2 constants are
// lbl_80298540[0]=1.0f, lbl_80298544[0]=0.0f, lbl_80298548[0]=-1.0f
// (src/r2d_80298540.c), so the m2c "temp_f0/temp_f12/temp_f13" names map to
// a=0.0f, b=1.0f, c=-1.0f exactly as below.  The two tail calls are
// CStruct_ctor(CStruct_new(8)) (0x80019D08 / 0x80126EAC), NOT the 4-arg
// CStruct_new the m2c body guessed from stale register liveness.
//
// After that fix the STORE ORDER IS EXACT: all 29 stores appear in the same
// order as the original (34D8, 3478, 34A8, 34AC, 34D0, 34C8, 34CC, 4, 3470,
// 346C, C, 10, 14, 18, 2054, 345C, 3460, 347C, 3484, 3488, 348C, 3494, 34A0,
// 34A4, 3474, 50, 34B0, 34B4, 34C0), and words 0x60..0x98 are byte-identical.
//
// RESIDUE (all of it register-allocation/scheduling, no C lever found):
//  1. The original has THREE live zero registers — `li r11,0` / `li r0,0` /
//     `li r12,0` — with r11 feeding 0x34A8+0x34A0 and r12 feeding
//     0x34AC+0x34A4.  ngccc emits a single `li r0,0` for this body, which is
//     exactly the 2 missing words (212 vs 220 B).  Micro-tests ruled out the
//     source-level explanations: (a) two/three `s32` locals initialised to 0
//     and used for those 4 stores collapse into ONE pseudo (CSE merges the
//     constants) even with 20 intervening stores; (b) writing the four fields
//     as float `0.0f` makes GCC load a pool float (lfs) instead of `li`+`stw`;
//     (c) chained assignment / comma expressions behave like (a).  So the
//     extra `li`s are reload's scratch-register choice for constant stores,
//     i.e. allocator territory (recipes §CR-field / local-alloc rule).
//     CROSS-REF: the very same "want has more zero registers than got" symptom
//     WAS solved on fn_8004DF00 (promoted 2026-10-05) by declaring the
//     out-slot pair as an address-taken initialised aggregate
//     (`f32 just[2] = {0, 0};` -> `li r9,0` + `li r10,0`).  Measured here:
//     `s32 zero[2] = {0, 0};` whose elements are only READ is NOT enough —
//     without an address-taken object ngccc folds the elements back to one
//     constant and the body stays at 40.0%.  Something in the original must
//     keep two independent zero pseudos live across this store block.
//  2. The pre-reload scheduler hoists `stfs f0,0x3474` and `stw r0,0x34C0`
//     into the early cluster (just after 0x3478) where the original keeps them
//     at 0xA4/0xB4.  Verified source-order driven, not a search artefact:
//     moving those two statements early in the source (V1/V2/V3) drops the
//     score to 21.8/18.2/21.8 and moving the 34D0/34C8/34CC group before
//     34A8/34AC (V4) leaves it at 40.0 — the scheduler reorders regardless.
//  3. f12/f13 are swapped relative to the original (got: b->f12, c->f13;
//     want: b->f13, c->f12) and the first two `lis` are issued a/b instead of
//     b/a.  Pure local-alloc.
//
// NEXT: needs the source construct (if any) that makes reload keep a second
// and third zero register alive across this store block; until then this is
// the documented local-alloc wall, so it is parked rather than permuted.
#include "types.h"
#include "structs.h"
CStruct *CStruct_new(s32);
CStruct *CStruct_ctor(CStruct *);
extern char lbl_80298730[];
extern f32 lbl_80298540[1];
extern f32 lbl_80298544[1];
extern f32 lbl_80298548[1];
void *fn_800AB528(Unk_6849630D *arg0) {
    f32 a = lbl_80298544[0];
    f32 b = lbl_80298540[0];
    f32 c = lbl_80298548[0];
    arg0->unk0x34D8 = (s32)lbl_80298730;
    *(f32 *)((char *)arg0 + 0x3478) = b;
    arg0->unk0x34A8 = 0;
    arg0->unk0x34AC = 0;
    arg0->unk0x34D0 = 0;
    *(f32 *)((char *)arg0 + 0x34C8) = a;
    *(f32 *)((char *)arg0 + 0x34CC) = c;
    arg0->unk0x4 = 0;
    arg0->unk0x3470 = 0;
    arg0->unk0x346C = 0;
    arg0->unk0xC = 0;
    arg0->unk0x10 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x18 = 0;
    arg0->unk0x2054 = 0;
    arg0->unk0x345C = 0;
    arg0->unk0x3460 = 0;
    arg0->unk0x347C = 0;
    *(f32 *)((char *)arg0 + 0x3484) = a;
    *(f32 *)((char *)arg0 + 0x3488) = a;
    *(f32 *)((char *)arg0 + 0x348C) = a;
    *(f32 *)((char *)arg0 + 0x3494) = a;
    arg0->unk0x34A0 = 0;
    arg0->unk0x34A4 = 0;
    *(f32 *)((char *)arg0 + 0x3474) = a;
    arg0->unk0x50 = 0;
    arg0->unk0x34B0 = 0;
    arg0->unk0x34B4 = 0;
    arg0->unk0x34C0 = 0;
    arg0->unk0x34D4 = (s32)CStruct_ctor(CStruct_new(8));
    return arg0;
}
