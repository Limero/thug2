// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801193E0-0x80119470 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE50[];

void AddChecksum(CStruct *, s32, s32);

bool ScriptGetPlatform(void *arg0, CScript *arg1) {
    s32 var_r5;
    s32 temp_r0;

    var_r5 = 0;
    temp_r0 = *(s32 *)&lbl_802FFE50;
    switch (temp_r0) {
    case 1:
    case 2:
    case 3:
        var_r5 = QB_PS2;
        break;
    case 5:
        var_r5 = QB_NGC;
        break;
    case 4:
        var_r5 = QB_XBOX;
        break;
    case 7:
        var_r5 = QB_WIN32;
        break;
    }
    AddChecksum(arg1->unk0x18, QB_PLATFORM, var_r5);
    return true;
}