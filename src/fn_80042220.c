// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042220-0x800422D4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 *lbl_80303280[];
extern s32 lbl_80303290;
s32 fn_800120EC(s32, void *);
void CompactPool_Free(s32, void *);
void fn_80042220(void *arg0) {
    s32 var_r31;

    var_r31 = (s32)lbl_80303280[lbl_80303290];
    if (var_r31 != 0) {
        if (fn_800120EC(var_r31, arg0) != 0) {
            CompactPool_Free(var_r31, arg0);
            return;
        }
    }
    var_r31 = (s32)lbl_80303280[(lbl_80303290 ^ 1)];
    if (var_r31 != 0) {
        if (fn_800120EC(var_r31, arg0) != 0) {
            CompactPool_Free(var_r31, arg0);
            return;
        }
    }
    if (arg0 != 0) {
        Mem_Free2(arg0);
    }
}
