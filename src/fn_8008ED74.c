// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008ED74-0x8008EDAC (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80296E68[];
extern char lbl_80296E80[];
void fn_800670E0(void);
void fn_8008ED74(Unk_C8FEE62D *arg0) {
    arg0->unk0x20 = (s32)lbl_80296E68;
    arg0->unk0x8 = (s32)lbl_80296E80;
    fn_800670E0();
}