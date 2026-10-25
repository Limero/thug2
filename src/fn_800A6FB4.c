// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A6FB4-0x800A7068 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
extern char lbl_80301A64[];
extern char lbl_80301A74[];
s32 fn_800120EC(s32, void *);
void CompactPool_Free(s32, void *);

void fn_800A6FB4(void *arg0) {
    s32 var_r31;

    var_r31 = *(s32 *)(lbl_80301A64 + (*(s32 *)lbl_80301A74 * 4));
    if ((var_r31 != 0) && (fn_800120EC(var_r31, arg0) != 0)) {
        CompactPool_Free(var_r31, arg0);
        return;
    }
    var_r31 = *(s32 *)(lbl_80301A64 + ((*(s32 *)lbl_80301A74 ^ 1) * 4));
    if ((var_r31 != 0) && (fn_800120EC(var_r31, arg0) != 0)) {
        CompactPool_Free(var_r31, arg0);
        return;
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}
