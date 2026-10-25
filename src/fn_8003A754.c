// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A754-0x8003A7A4 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_ctor(void *);
extern char lbl_80291F88[];
void *fn_8003A754(CStruct *arg0) {
    fn_8009E004();
    arg0->unk0x8 = (s32)lbl_80291F88;
    CStruct_ctor((char *)arg0 + 0x58);
    arg0->unk0x60 = 0;
    arg0->unk0x64 = 0;
    return arg0;
}
