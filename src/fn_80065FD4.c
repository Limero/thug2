// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80065FD4-0x80066028 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80294100[];
void fn_80065FD4(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r10;

    arg0->unk0x14 = (s32)lbl_80294100;
    temp_r10 = arg1 & 1;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0xC) =  arg0->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x10) =  arg0->unk0x10;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (temp_r10 != 0) {
        Mem_Free(arg0);
    }
}
