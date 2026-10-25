// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801348BC-0x80134970 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern s32 lbl_80303428;
extern void *lbl_80303418[];
extern s32 fn_800120EC(CStruct *, s32);
extern void CompactPool_Free(Unk_C8FEE62D *, s32 *);

void fn_801348BC(void *arg0) {
    s32 var_r31;

    var_r31 = (s32)lbl_80303418[lbl_80303428];
    if ((var_r31 != 0) && (fn_800120EC((void *)var_r31, arg0) != 0)) {
        CompactPool_Free((void *)var_r31, arg0);
        return;
    }
    var_r31 = (s32)lbl_80303418[lbl_80303428 ^ 1];
    if ((var_r31 != 0) && (fn_800120EC((void *)var_r31, arg0) != 0)) {
        CompactPool_Free((void *)var_r31, arg0);
        return;
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}
