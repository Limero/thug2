// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003ED20-0x8003EDD0 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetFacePointsStruct(Unk_DB0E2BAB *, CStruct *);
void strcpy(s32, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetChecksum(CStruct *, s32);
void fn_8003ED20(s32 arg0, CStruct *arg1) {
    s32 spC;
    CStruct * volatile sp8;
    s32 *var_r31;
    u32 temp_r4;
    u32 var_r30;

    var_r30 = 0U;
    GetArray(arg1, QB_RAWTEXTUREDATA, (s32 *)&sp8, 1);
    var_r31 = arg0 + 0x40;
    while (var_r30 < (u32)sp8->unk0x4) {
        temp_r4 = var_r30;
        var_r30 += 1;
        *((s32 *)var_r31) = GetChecksum(sp8, temp_r4);
        var_r31 += 1;
        __asm__ volatile("" ::: "memory");
    }
    GetString(arg1, QB_OVERLAYTEXTURENAME, &spC, 1);
    strcpy(arg0 + 0x4460, spC);
    GetFacePointsStruct(arg0 + 8, arg1);
}
