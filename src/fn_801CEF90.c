// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CEF90-0x801CF038 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 ContainsFlag(CStruct *, s32);
s32 fn_801CEF90(Unk_1E29BE92 *arg0, CStruct *arg1) {
    s32 var_r3;

    if (ContainsFlag(arg1, QB_BACKSIDE) != 0) {
        if (*(s32 *)(arg0->unk0x15BC + 0x34) != 0) {
            var_r3 = arg0->unk0x424 == 0;
            return var_r3;
        }
        var_r3 = 0;
        if (arg0->unk0x424 != 0) {
            var_r3 = 1;
        }
        return var_r3;
    }
    if (ContainsFlag(arg1, QB_FRONTSIDE) != 0) {
        if (*(s32 *)(arg0->unk0x15BC + 0x34) == 0) {
            var_r3 = arg0->unk0x424 == 0;
            return var_r3;
        }
        var_r3 = 0;
        if (arg0->unk0x424 != 0) {
            var_r3 = 1;
        }
        return var_r3;
    }
    return 1;
}
