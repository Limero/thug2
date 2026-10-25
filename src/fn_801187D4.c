// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801187D4-0x80118868 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F2BA8(s32, s32, s32, s32, s32, s32, s32, s32);
s32 fn_800F2ED4(CScript *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 GetText(CStruct *, void *, void *, void *);
extern s32 lbl_80301B48;
bool ScriptLoadSkeleton(CStruct *arg0) {
    struct { s32 sp8, spC, sp10, sp14; } s;
    s32 temp_r10;
    s32 temp_r29;

    temp_r29 = lbl_80301B48;
    GetText(arg0, QB_NAME, &s.sp10, 1);
    GetChecksum_2(arg0, 0, &s.sp14, 1);
    temp_r10 = fn_800F2ED4(temp_r29);
    s.sp8 = 0;
    s.spC = 0;
    fn_800F2BA8(temp_r29, s.sp10, 0, s.sp14, 0, 0, 0, temp_r10);
    return true;
}
