// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FF9B0-0x800FF9E0 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
u16 fn_800FF9B0(Unk_9994C3F5 *arg0, s32 arg1) {
    register void *t __asm__("r10");
    t = *((void * *)&arg0->unk0x8);
    if (((Unk_6E48A312 *)t)->unk0xA == 0) {
        return *(u16 *)(*((u16 * *)&((Unk_6E48A312 *)t)->unk0xC) + arg1 * 5);
    }
    return *(u16 *)(*((u16 * *)&((Unk_6E48A312 *)t)->unk0xC) + arg1 * 4);
}