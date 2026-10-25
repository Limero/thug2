// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E2B8-0x8018E340 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
s32 fn_8009CF2C(CStruct *);
s32 fn_80198F7C(s32);
s32 fn_8018E2B8(Unk_C7387A53 *arg0) {
    if (((fn_8009CF2C(*(s32 *)&lbl_80305F9C) != 0) && (fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_NETGOALATTACK)) || (fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_NETLOBBY)) {
        return ((u32) *((u32 *)&arg0->unk0x70) >> 0x1CU) & 1;
    }
    return ((u32) *((u32 *)&arg0->unk0x70) >> 0x1DU) & 1;
}
