// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BDF64-0x800BE010 (172B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetVector(CStruct * arg0, s32 arg1, CStruct * arg2, s32 arg3);
extern void fn_800BA64C(Unk_60E57DDC * arg0);
bool fn_800BDF64(Unk_B950D1C2 *arg0, CStruct *arg1) {
    __ps_t spA[2];
    Unk_073F5245 *temp_r9;

    if (GetVector(arg1, QB_VEL, &spA[0], 0) != 0) {
        temp_r9 = arg0->unk0xC;
        arg0->unk0x128 = spA[0];
        arg0->unk0x130 = spA[1];
        temp_r9->unk0xB8 = spA[0];
        temp_r9->unk0xC0 = arg0->unk0x130;
    }
    if (GetVector(arg1, QB_ROTVEL, &spA[0], 0) != 0) {
        arg0->unk0x148 = spA[0];
        arg0->unk0x150 = spA[1];
    }
    fn_800BA64C(arg0);
    return true;
}
