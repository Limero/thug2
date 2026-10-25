// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022CF44-0x8022CFF8 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
extern char lbl_80305FE0[];
extern char lbl_80305FF0[];
s32 fn_800120EC(s32, void *);
void CompactPool_Free(s32, void *);

void fn_8022CF44(void *arg0) {
    s32 var_r31;

    var_r31 = *(s32 *)(lbl_80305FE0 + (*(s32 *)lbl_80305FF0 * 4));
    if ((var_r31 != 0) && (fn_800120EC(var_r31, arg0) != 0)) {
        CompactPool_Free(var_r31, arg0);
        return;
    }
    var_r31 = *(s32 *)(lbl_80305FE0 + ((*(s32 *)lbl_80305FF0 ^ 1) * 4));
    if ((var_r31 != 0) && (fn_800120EC(var_r31, arg0) != 0)) {
        CompactPool_Free(var_r31, arg0);
        return;
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}
