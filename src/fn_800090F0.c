// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800090F0-0x8000913C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8000901C(void *);
s32 fn_800090F0(Unk_DB0E2BAB *arg0, s32 arg1) {
    s32 val = fn_8000901C(arg0);
    s32 bit = 1 << (arg1 - 1);
    if (val & bit) {
        val |= -(1 << arg1);
    }
    return val;
}
