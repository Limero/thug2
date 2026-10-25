// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD374-0x801CD414 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AD950[];
extern void fn_80105C34(void *, s32);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801CD374(CScript *arg0, s32 arg1) {
    s32 *p;
    s32 var_r30;

    arg0->unk0x18 = (s32)lbl_802AD950;
    fn_80105C34((char *)arg0 + 0x578, 2);
    p = (s32 *)((char *)arg0 + 0x3CC);
    if (*p != 0) {
        CObject_RemoveRefLink(*p, p);
        *p = 0;
    }
    var_r30 = 0;
    p = (s32 *)((char *)arg0 + 0x218);
    if (*p != 0) {
        CObject_RemoveRefLink(*p, p);
        *p = var_r30;
    }
    p = (s32 *)((char *)arg0 + 0x158);
    if (*p != 0) {
        CObject_RemoveRefLink(*p, p);
        *p = var_r30;
    }
    fn_8009F558(arg0, arg1);
}
