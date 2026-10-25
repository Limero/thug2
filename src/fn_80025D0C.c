// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80025D0C-0x80025D50 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80362CC0[];
extern void fn_80025EA8(char *, void *, void *);
void fn_80025D0C(CStruct *arg0, s32 arg1) {
    s32 sp8;

    sp8 = arg1;
    arg0->unk0x10 = arg0->unk0x10 + 1;
    fn_80025EA8(lbl_80362CC0, &sp8, arg0);
}
