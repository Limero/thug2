// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FFD8C-0x801FFE70 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
extern s32 fn_80128978(s32 arg0, s32 arg1);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);

void fn_801FFD8C(CScript *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp;

    if (fn_80128978(arg1, QB_UNKNOWN_0x0431C185) != 0) {
        GetChecksum_2(arg1, QB_UNKNOWN_0x0431C185, &sp8, 1);
        temp = fn_800A398C(lbl_80301A38, sp8);
        arg0->unk0x1C = temp;
        arg0->unk0x20 = GetChecksum_3(temp, QB_VEHICLE);
    }
    GetFloat(arg1, QB_UNKNOWN_0x9213625F, (char *)arg0 + 0xA4, 0);
    GetFloat(arg1, QB_UNKNOWN_0x14849B6D, (char *)arg0 + 0x98, 0);
    GetFloat(arg1, QB_UNKNOWN_0xBD3D3CA9, (char *)arg0 + 0x9C, 0);
    GetFloat(arg1, QB_ANGLE, (char *)arg0 + 0xA0, 0);
}
