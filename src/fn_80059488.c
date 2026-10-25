// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059488-0x8005951C (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_80300478;
typedef struct S1C { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; } S1C;
extern S1C lbl_80364C38;
extern S1C lbl_80364C54[];
void fn_8007C144(void);
bool fn_80059488(void) {
    s32 idx;

    idx = lbl_80300478;
    if (idx >= 0) {
        lbl_80300478 = idx - 1;
        lbl_80364C38 = lbl_80364C54[idx];
        fn_8007C144();
        return true;
    }
    return false;
}
