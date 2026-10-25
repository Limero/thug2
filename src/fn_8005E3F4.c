// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E3F4-0x8005E4B8 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8005DE84(void);
extern void AddChecksum(CStruct *, s32, s32);
// ScriptGetScreenMode @ 0x8005E3F4
bool ScriptGetScreenMode(void *arg0, CScript *arg1) {
    s32 var_r31;
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    var_r31 = 0;
    switch (fn_8005DE84()) {
    case 1:
        var_r31 = QB_SPLIT_VERTICAL;
        break;
    case 2:
        var_r31 = QB_SPLIT_HORIZONTAL;
        break;
    case 3:
        var_r31 = QB_SPLIT_QUARTERS;
        break;
    case 0:
        var_r31 = QB_ONE_CAMERA;
        break;
    case 4:
        var_r31 = QB_HORSE1;
        break;
    case 5:
        var_r31 = QB_HORSE2;
        break;
    }
    AddChecksum(temp_r30, QB_SCREEN_MODE, var_r31);
    return true;
}

