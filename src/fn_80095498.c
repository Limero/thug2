// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80095498-0x800954EC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037B5E8[];
s32 fn_8001D424(void *);
void fn_80095498(s32 arg0, s32 arg1) {
    char *base;
    if (arg1 == 0xFFFF && arg0 != 0) {
        base = lbl_8037B5E8;
        fn_8001D424(base + 0x1C8);
        fn_8001D424(base + 0x1D8);
    }
}
