// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0520-0x801F0610 (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801F0520(Unk_C9CA854A *arg0, s32 *arg1, CStruct *arg2) {
    s32 v = arg0->unk0x1C;
    switch ((u32)v) {
        case QB_MANUAL:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0x70;
            arg2->unk0x4 = arg0->unk0x74;
            break;
        case QB_LIP:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0x150;
            arg2->unk0x4 = arg0->unk0x154;
            break;
        case QB_SLIDE:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0xE0;
            arg2->unk0x4 = arg0->unk0xE4;
            break;
        case QB_SKITCH:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0x1C0;
            arg2->unk0x4 = arg0->unk0x1C4;
            break;
        case QB_GRIND:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0xE0;
            arg2->unk0x4 = arg0->unk0xE4;
            break;
        case QB_NOSEMANUAL:
            *arg1 = 2;
            *(s32 *)arg2 = arg0->unk0x70;
            arg2->unk0x4 = arg0->unk0x74;
            break;
        default:
            *arg1 = 0;
            break;
    }
}
