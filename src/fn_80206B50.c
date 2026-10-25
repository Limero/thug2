// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206B50-0x80206BA8 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void CStruct_delete(CStruct *, s32);
extern char lbl_802AF3D8[];
void fn_80206B50(Unk_709BED05 *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x18 = (s32)lbl_802AF3D8;
    v = arg0->unk0xA6C;
    if (v != 0) {
        CStruct_delete(v, 3);
    }
    fn_8009F558(arg0, arg1);
}
