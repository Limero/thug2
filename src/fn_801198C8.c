// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801198C8-0x80119934 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80302C40[];

s32 fn_8011A95C(void *, s32, s32 *);

bool fn_801198C8(void *arg0, s32 arg1) {
    CStruct *var_r9;

    if (fn_8011A95C(arg0, arg1, 0) != 0) {
        return false;
    }
    var_r9 = *(void * *)&lbl_80302C40;
    while (var_r9 != NULL) {
        if (*(s32 *)var_r9 == arg1) {
            return false;
        }
        var_r9 = *((void * *)&var_r9->unk0x10);
    }
    return true;
}
