// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800150EC-0x80015154 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: global-node list walk — scans a linked list head at lbl_803C9C38
// (sdata global), calls fn_80013180 on each live node, 0x10-iteration cap
// (16-slot polling loop). EXACT via raw-lit→symbol patch (doc-51).
// Suggested rename: PollGlobalNodeList.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_803C9C38[];
void fn_80013180(Unk_DB0E2BAB *);
void fn_800150EC(void) {
    s32 temp_r0;
    s32 var_r30;
    void *var_r31;

    var_r31 = NULL;
    var_r30 = 0x10;
    do {
        temp_r0 = *(s32 *)((char *)var_r31 + (s32)(s32)lbl_803C9C38);
        if (temp_r0 != 0) {
            fn_80013180(temp_r0);
        } else {
            Mem_Alloc2(0x104);
            *(s32 *)((char *)var_r31 + (s32)(s32)lbl_803C9C38) = fn_80014B40();
        }
        var_r31 += 4;
        var_r30 -= 1;
    } while (var_r30 != 0);
}
