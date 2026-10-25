// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A977C-0x801A97C4 (72B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 CStruct_dtor(CStruct *);
extern s32 fn_80126F88(Unk_80577C09 *, CStruct *);

void fn_801A977C(Unk_C7387A53 *arg0, CStruct *arg1) {
    CStruct_dtor(arg0->unk0x38);
    if (arg1 != 0) {
        fn_80126F88(arg0->unk0x38, arg1);
    }
}
