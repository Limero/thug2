// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B98B4-0x801B9970 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct * ctx, s32 hash, s32 *out, s32 flag);
extern s32 GetStructure_2(CStruct * ctx, s32 hash, s32 * out, s32 flag);
extern s32 fn_801B3220(Unk_C7387A53 * obj, s32 * a, s32 * b, Unk_C8FEE62D * c);

bool fn_801B98B4(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 z;

    z = 0;
    spC = z;
    sp8 = z;
    GetChecksum_2((void *)arg1, 0, &sp8, 1);
    if (sp8 == arg0->unk0x28) {
        return true;
    }
    GetChecksum_2((void *)arg1, 0x9D670B9, &spC, 0);
    sp10 = z;
    if (arg1 != 0) {
        GetStructure_2(arg1, QB_STATEPARAMS, &sp10, 0);
    }
    if (fn_801B3220(arg0, sp8, spC, sp10) == 0) {
        return false;
    }
    return true;
}
