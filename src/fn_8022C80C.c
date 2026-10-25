// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C80C-0x8022C83C (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022C80C(Unk_4E705049 *arg0, void *arg1) {
    if ((void *) arg0->unk0x10 == NULL) {
        arg0->unk0x10 = arg1;
    } else {
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x14) + 0x34) = arg1;
    }
    arg0->unk0x14 = arg1;
    *((u16 *)&arg0->unk0x18) = (u16) (*((u16 *)&arg0->unk0x18) + 1);
}
