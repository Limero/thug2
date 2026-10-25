// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059404-0x80059488 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { s32 f0, f4, f8, fc, f10, f14, f18; } Rec;
extern Rec lbl_80364C38;
extern Rec lbl_80364C54[];
extern s32 lbl_80300478;
void fn_80059404(void) {
    s32 i = lbl_80300478 + 1;
    lbl_80300478 = i;
    if (i <= 3) {
        lbl_80364C54[i] = lbl_80364C38;
    } else {
        lbl_80300478 = i - 1;
    }
}
