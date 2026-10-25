// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192118-0x801921C0 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_8019B728(Unk_31DE137E * arg0, s32 arg1);
void fn_80192118(CStruct *arg0) {
    s32 temp_r30;

    temp_r30 = *(s32 *)((char *)(*(void * *)&lbl_80305EAC) + 0x370);
    if (fn_8019B728(temp_r30, 1) != 0) {
        arg0->unk0x78 = 1;
        arg0->unk0x7C = 1;
        arg0->unk0x80 = 1;
    } else if (fn_8019B728(temp_r30, 2) != 0) {
        arg0->unk0x7C = 1;
        arg0->unk0x80 = 1;
    } else if (fn_8019B728(temp_r30, 3) != 0) {
        arg0->unk0x80 = 1;
    }
    arg0->unk0x70 = (s32) (arg0->unk0x70 | QB_UNKNOWN_0x20000000);
}
