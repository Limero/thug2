// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155D6C-0x80155DB8 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 fn_80198F7C(void *);
extern char lbl_80305EC0[];
bool ScriptGetGameMode(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_80198F7C(*(s32 *)&lbl_80305EC0);
    AddChecksum(arg1->unk0x18, QB_GAMEMODE, temp_r5);
    return true;
}
