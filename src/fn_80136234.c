// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136234-0x80136280 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
void memset(s32, s32, s32);

void fn_80136234(s32 arg0, s32 arg1) {
    memset((s32)lbl_8039D940, 0, 0x194);
    *(s32 *)lbl_8039D940 = arg0;
    ((Unk_4C649A8C *)lbl_8039D940)->unk0x4 = arg1;
}
