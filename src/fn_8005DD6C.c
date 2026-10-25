// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DD6C-0x8005DDBC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 *lbl_80300DFC;
extern s32 lbl_803C9E18[];
s32 fn_8005DD6C(s32 arg0) {
    s32 *tbl = lbl_803C9E18;
    s32 *p = lbl_80300DFC;
    s32 count = 0;
    s32 i;
    for (i = 0xA; i != 0; i--) {
        s32 v = *p;
        p++;
        if (v >= 0) {
            if (count == arg0) {
                return tbl[v];
            }
            count++;
        }
    }
    return 0;
}
