// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3CC4-0x800A3D34 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void fn_800A5B00(Unk_C8FEE62D *, CStruct *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_80301A78[];
void fn_800A3CC4(s32 *arg0, CStruct *arg1) {
    if ((s32) *arg0 != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)arg0), arg0);
        *arg0 = 0;
    }
    *arg0 = arg1;
    if (arg1 != 0) {
        CObject_AddRefLink(arg1, arg0);
    }
    fn_800A5B00(*(s32 *)lbl_80301A78, arg0);
}
