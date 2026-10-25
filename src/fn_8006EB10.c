// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006EB10-0x8006EB68 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301438;
void fn_8006F8C8(s32 arg0);
s32 fn_8006F8DC(s32 arg0, s32 arg1);
void fn_80087010(void);
s32 fn_8006EB10(s32 arg0) {
    s32 v;

    v = lbl_80301438;
    if (v != 0) {
        fn_8006F8C8(v);
        while ((v = fn_8006F8DC(lbl_80301438, 0)) != 0) {
            fn_80087010();
        }
    }
    return v;
}
