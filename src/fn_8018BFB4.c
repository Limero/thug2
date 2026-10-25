// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BFB4-0x8018C054 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
void fn_8018BFB4(Unk_C7387A53 *arg0) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_UNLIMITED_TIME, &sp8, 0);
    if (sp8 != 1) {
        arg0->unk0x54 = 0x78;
        if (GetInteger(arg0->unk0x20, QB_TIME, &spC, 0) != 0) {
            arg0->unk0x54 = spC;
        }
        arg0->unk0x70 = (s32) (arg0->unk0x70 & QB_UNKNOWN_0xFFF7FFFF);
        arg0->unk0x54 = (s32) ((arg0->unk0x54 * 0x3E8) + 0x14);
    }
}
