// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9F2C-0x801B9FD0 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 ContainsFlag(CStruct * arg0, u32 arg1);
bool fn_801B9F2C(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    GetInteger(arg1, 0, &sp8, 1);
    if (ContainsFlag(arg1, QB_GRIND) != 0) {
        if (sp8 == 0) {
            arg0->unk0x24 &= QB_UNKNOWN_0xFFFFFF7F;
        } else {
            arg0->unk0x24 |= 0x80;
        }
    } else {
        if (sp8 == 0) {
            arg0->unk0x24 &= QB_UNKNOWN_0xFFFFFFBF;
        } else {
            arg0->unk0x24 |= 0x40;
        }
    }
    return true;
}
