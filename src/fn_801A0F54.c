// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A0F54-0x801A0FA0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002DCCC(Unk_C8FEE62D *);
extern char lbl_802AB1D0[];
void *fn_801A0F54(Unk_C8FEE62D *arg0) {
    fn_800AB0F0();
    arg0->unk0x14 = (s32)lbl_802AB1D0;
    fn_8002DCCC((char *)arg0 + 0x40);
    arg0->unk0x3C = 0;
    return arg0;
}
