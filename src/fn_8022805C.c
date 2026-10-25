// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022805C-0x80228140 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
s32 fn_80198B10(s32);
void fn_801989CC(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_801745B4(s32);
void fn_801738A4(Unk_839CD594 *, Unk_C8FEE62D *, s32, s32);

bool fn_8022805C(u8 **arg0) {
    s8 b;
    s32 mgr;

    b = *(s8 *)*arg0;
    mgr = *(s32 *)&lbl_80305EAC;
    if ((b > 0) && (fn_80198B10(*(s32 *)&lbl_80305EC0) == 0)) {
        fn_801989CC(*(s32 *)&lbl_80305EC0, b);
        Script_RunScript(QB_CHOOSETEAMMESSAGE, 0, 0, 0, 0);
        if (fn_801745B4(mgr) != 0) {
            Script_RunScript(QB_PREPARESKATERFORMOVE, 0, fn_801745B4(mgr), 0, 0);
            fn_801738A4(mgr, fn_801745B4(mgr), 0, 0);
        }
    } else {
        fn_801989CC(*(s32 *)&lbl_80305EC0, b);
    }
    return true;
}
