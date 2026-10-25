// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFEB8-0x800EFF44 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_800EFC84(void *, void *);
Unk_C7387A53 *fn_800EFBF4(void *);
void fn_800F1448(void *, void *, void *);
void *Mem_NewZero(s32);
s32 fn_800F13F4(void *, s32 *, s32);

void fn_800EFEB8(CStruct *arg0, s32 arg1, CStruct *arg2) {
    Unk_C7387A53 *node;
    s32 sp8;
    sp8 = arg1;
    node = (Unk_C7387A53 *)fn_800F13F4(arg0->unk0x4, &sp8, 1);
    if (node != 0) {
        fn_800EFC84(node, arg2);
        return;
    }
    node = fn_800EFBF4(Mem_NewZero(0x10));
    node->unk0xC = sp8;
    fn_800EFC84(node, arg2);
    fn_800F1448(arg0->unk0x4, &sp8, node);
}
