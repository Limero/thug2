// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008D904-0x8008D93C (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80296DB8[];
extern char lbl_80296DD0[];
void fn_80066BEC(void);
void fn_8008D904(Unk_C8FEE62D *arg0) {
    arg0->unk0x20 = (s32)lbl_80296DB8;
    arg0->unk0x8 = (s32)lbl_80296DD0;
    fn_80066BEC();
}