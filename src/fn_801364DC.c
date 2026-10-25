// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801364DC-0x80136510 (52B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_8039D940[];

void fn_801364DC(void) {
    Unk_31DE137E *vt = &lbl_8039D940;
    void (*fn)(s32) = *(void (**)(s32))((char *)vt + 4);
    fn(vt->unk0x18C);
}
