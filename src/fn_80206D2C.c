// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206D2C-0x80206DE4 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802FFE50[];

s32 GetStructure_2(CStruct *arg0, s32 hash, s32 *out, s32 flag);

s32 fn_80206D2C(void *unused, CStruct *arg1) {
    s32 sp8 = 0;
    s32 plat = *(s32 *)&lbl_802FFE50;

    if (plat == 4) {
        if (GetStructure_2(arg1, QB_XBOX_TRIGGER, &sp8, 0) == 0) {
            GetStructure_2(arg1, QB_TRIGGER, &sp8, 1);
        }
    } else if (plat == 5) {
        if (GetStructure_2(arg1, QB_NGC_TRIGGER, &sp8, 0) == 0) {
            GetStructure_2(arg1, QB_TRIGGER, &sp8, 1);
        }
    } else {
        GetStructure_2(arg1, QB_TRIGGER, &sp8, 1);
    }
    return sp8;
}
