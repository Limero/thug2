// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010BBC4-0x8010BC58 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8010BABC(s32);
extern s32 GetStructure(s32, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
bool fn_8010BBC4(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_r3;

    temp_r3 = GetStructure(fn_8010BABC(arg0), 0);
    if (temp_r3 != 0) {
        if (GetStructure_2(temp_r3, arg2, arg1, 0) != 0) {
            return true;
        }
    }
    temp_r3 = GetStructure(QB_STANDARD_TERRAIN_DEFAULT, 0);
    if (temp_r3 != 0) {
        if (GetStructure_2(temp_r3, arg2, arg1, 0) != 0) {
            return true;
        }
    }
    return false;
}
