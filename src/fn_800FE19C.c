// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FE19C-0x800FE1CC (48B). Byte-identical.
#include "types.h"
#include "structs.h"

u16 fn_800FE19C(Unk_9994C3F5 *arg0, s32 idx) {
    void *node = *((void * *)&arg0->unk0x8);
    if (((Unk_6E48A312 *)node)->unk0xA == 0)
        return ((u16 *)*((void * *)&((Unk_6E48A312 *)node)->unk0xC))[idx * 5];
    return ((u16 *)*((void * *)&((Unk_6E48A312 *)node)->unk0xC))[idx * 4];
}
