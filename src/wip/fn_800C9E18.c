// PARKED 2026-10-17: 68.8% NEAR size-exact (re-verified). Residual is a
// frame-layout wall, not scheduling: want hides 8 dead bytes at 0x48..0x50
// (uniform +8 local shift, frame 0x70 both). Dummy/volatile/struct-pad levers
// all worse (25–58%, stmw/frame regressions); dead-hole source unknown.
// Body below is the best measured shape; do not re-grind without a new
// frame-hole lever.
// WIP DRAFT — rewritten 2026-10-15 from want (protos + c54 FPR + dummy).
// Best 68.8% NEAR size-exact (was m2c DIFF). Residual is a uniform +8 shift
// of all locals (want sp8 at r1+8, got +0x10; frame 0x70 both): want hides
// 8 dead bytes at 0x48..0x50. Tried: dummy-last (DIFF, stmw r27 + sp8 at
// +0x18), end volatile pads (58.4%), 800E9C84-style frame struct with
// internal pad[8] (58.4%, stmw r27 — struct base perturbs regalloc).
// Source of want's dead 8B still unknown (no >8-arg call for outgoing area).
// 2026-10-17: volatile-arrays + dummy-last hypothesis (volatiles allocate
// first in decl order, so volatile sp8/sp18/sp28/sp38/sp3C/sp40/sp44 with the
// dummy last should put the dummy at the 0x48 hole and keep sp8@8) measured
// 25.0% DIFF, 304B (1 word short): volatile addressing kills all three base
// homes (direct r1+disp everywhere, no r29/r27/r28) and drops to stmw r27.
// Reverted; the hole is not a volatile tail.
// Re-measured 2026-10-15: want keeps THREE vector base pointers in saved
// regs (r29=sp8@8 computed pre-call1, r27=sp18@0x18, r28=sp28@0x28) and its
// first sp8 store is DIRECT (`stfs f0,8(r1)`, rest via r29) — suggests an
// explicit sp8-base pointer variable with mixed direct/based stores. No-dummy
// variant puts scalars exactly (sp38@0x38..sp44@0x44) but loses frame/stmw
// (0x68/r27: arg0 in r27, sp8 has no base); dummy-first keeps 0x70/stmw r26
// but shifts all locals +8. Neither reaches want's [dead 0..8][live 8..0x48]
// [dead 0x48..0x50]; volatile-double-last blows up (gap + stmw r27).
// family=m2c range=0x800C9E18-0x800C9F4C size=308B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80299350;
extern f32 lbl_80299354;

s32 GetChecksum_2(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetVector(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetArray(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetStructure_2(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetFloat(CStruct *arg0, s32 arg1, f32 *arg2, s32 arg3);
void fn_800CA534(void *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, void *arg5, void *arg6, f32 arg7);

s32 fn_800C9E18(void *arg0, CStruct *arg1) {
    volatile double _dummy;
    f32 sp8[4];
    f32 sp18[4];
    f32 sp28[4];
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    f32 sp44;
    f32 c54;

    GetChecksum_2(arg1, QB_BONE, &sp38, 1);
    sp8[0] = lbl_80299350;
    sp8[1] = lbl_80299350;
    sp8[2] = lbl_80299350;
    c54 = lbl_80299354;
    sp8[3] = c54;
    GetVector(arg1, QB_OFFSET, sp8, 0);
    GetArray(arg1, QB_COMPONENTS, &sp3C, 1);
    GetStructure_2(arg1, QB_PARAMS, &sp40, 1);
    GetVector(arg1, QB_VEL, sp18, 1);
    GetVector(arg1, QB_ROTVEL, sp28, 1);
    sp44 = c54;
    GetFloat(arg1, QB_OBJECT_VEL_FACTOR, &sp44, 0);
    fn_800CA534(arg0, sp38, sp3C, sp40, sp18, sp28, sp8, sp44);
    return 1;
}
