// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B1C44-0x801B1C94 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80007B94(s32);
void fn_8009F53C(void);
extern char lbl_802ABF40[];
void *fn_801B1C44(Unk_C8FEE62D *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802ABF40;
    fn_80007B94((char *)arg0 + 0x20);
    arg0->unk0x4 = QB_AVOID;
    return arg0;
}
