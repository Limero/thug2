// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FE1CC-0x800FE204 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
u16 fn_800FE1CC(Unk_9994C3F5 *arg0, s32 arg1) {
    char *p = *((char * *)&arg0->unk0x8);
    return ((Unk_21634967 *)p)->unk0xA != 0
               ? *(u16 *)((arg1 << 3) + (s32) * (char **)((char *)p + 0xC) + 2)
               : *(u16 *)(arg1 * 10 + (s32) * (char **)((char *)p + 0xC) + 2);
}