// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127E38-0x80127E70 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void AddString(CStruct *, s32, void *);
void fn_80127618(CStruct *, s32, void *);
// AddComponent @ 0x80127E38
void AddComponent(CStruct *arg0, s32 arg1, s32 arg2, void *arg3) {
    if (arg2 == 3) {
        AddString(arg0, arg1, arg3);
        return;
    }
    fn_80127618(arg0, arg1, arg3);
}
