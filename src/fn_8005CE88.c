// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CE88-0x8005CECC (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Wrapper: r = fn_8005CCFC(); return r ? fn_8005C070(r, arg2) : 0.
// Suggested rename: GetResultOrCall
#include "types.h"
extern s32 fn_8005CCFC(void);
extern s32 fn_8005C070(s32, s32);
s32 fn_8005CE88(void *arg0, void *arg1, s32 arg2) {
    s32 r = fn_8005CCFC();
    if (r != 0)
        return fn_8005C070(r, arg2);
    return 0;
}