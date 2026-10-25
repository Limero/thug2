// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D6E4-0x8022D76C (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8022DC74(Unk_C7387A53 *, u32);
void *fn_8022DDB8(void *, CStruct *, s32);
void fn_80240ED8(s32 *, s32, s32);
void fn_80240F28(CStruct *, s32, s32);
void fn_8022E000(CStruct *, CStruct *);

void *fn_8022D6E4(Unk_C7387A53 *arg0, void *arg1, s32 arg2) {
    CStruct *node;

    node = fn_8022DDB8(arg0, fn_8022DC74(arg0, QB_SK4ED_GAP_10X10), 0);
    fn_80240ED8(node, arg1, 1);
    fn_80240F28(node, arg2, 1);
    node->unk0x4 |= 0x40;
    fn_8022E000(arg0, node);
    return node;
}
