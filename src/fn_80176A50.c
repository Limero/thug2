// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176A50-0x80176AE8 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000F2F8(Unk_9F352E7C *, void *);
s32 fn_8000F320(Unk_F12C5E01 *);
s32 fn_800101A0(void *, void *);
s32 fn_80010258(void *);
s32 fn_802198F4(void *);
extern char lbl_802FFE98[];
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
bool ScriptInitSkaterHeaps(CStruct *pParams, CScript *pScript) {
    s32 var_r31;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
    if ((s32) *(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x5C) == QB_FREESKATE2P) {
        var_r31 = 2;
    } else {
        var_r31 = fn_802198F4(*(s32 *)&lbl_80305F9C);
    }
    if (var_r31 > 1) {
        fn_80010258(*(s32 *)&lbl_802FFE98);
        fn_800101A0(*(s32 *)&lbl_802FFE98, var_r31);
    }
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    return true;
}
