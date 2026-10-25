// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800599B0-0x80059A30 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803008A0;
extern s32 lbl_803008A4;
extern s32 lbl_803008A8;
extern s32 lbl_803008AC;
extern s32 lbl_803008B0;
extern CStruct * lbl_803008B4;
void Mem_Free_3(s32);
void CStruct_delete(CStruct *, s32);
void fn_800599B0(void) {
    if (lbl_803008A0 != 0) {
        Mem_Free_3(lbl_803008A0);
        lbl_803008A0 = 0;
    }
    lbl_803008A4 = 0;
    lbl_803008A8 = 0;
    lbl_803008AC = 0;
    lbl_803008B0 = 0;
    if (lbl_803008B4 != 0) {
        CStruct_delete(lbl_803008B4, 3);
        lbl_803008B4 = 0;
    }
}
