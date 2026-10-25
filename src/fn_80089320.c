// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80089320-0x80089358 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80066E68(Unk_C8FEE62D *);
extern char lbl_80296910[];
extern char lbl_80296928[];
void fn_80089320(Unk_C8FEE62D *arg0) {
    arg0->unk0x20 = (s32)lbl_80296910;
    arg0->unk0x8 = (s32)lbl_80296928;
    fn_80066E68(arg0);
}