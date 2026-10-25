// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FF9E0-0x800FFA18 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
u16 fn_800FF9E0(Unk_9994C3F5 *arg0, s32 arg1) {
    void *tbl = *((void * *)&arg0->unk0x8);
    return (((Unk_6E48A312 *)tbl)->unk0xA != 0)
        ? *(u16 *)(((Unk_6E48A312 *)tbl)->unk0xC + arg1 * 8 + 2)
        : *(u16 *)(((Unk_6E48A312 *)tbl)->unk0xC + arg1 * 0xA + 2);
}