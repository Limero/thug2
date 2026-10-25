// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D3048-0x800D3124 (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 fn_8012570C(s32 arg0, s32 arg1);
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);

void fn_800D3048(Unk_C7387A53 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x38) = fn_8012570C(QB_ACCELCARROT, 1);
    GetFloat(arg1, QB_ACCELCARROT, (char *)arg0 + (s32)0x38, 0);
    *((f32 *)&arg0->unk0x3C) = fn_8012570C(QB_DECELCARROT, 1);
    GetFloat(arg1, QB_DECELCARROT, (char *)arg0 + (s32)0x3C, 0);
    *((f32 *)&arg0->unk0x40) = fn_8012570C(QB_SPEEDCARROT, 1);
    GetFloat(arg1, QB_SPEEDCARROT, (char *)arg0 + (s32)0x40, 0);
    *((f32 *)&arg0->unk0x44) = fn_8012570C(QB_ACCELCARROTFACTOR, 1);
    GetFloat(arg1, QB_ACCELCARROTFACTOR, (char *)arg0 + (s32)0x44, 0);
}
