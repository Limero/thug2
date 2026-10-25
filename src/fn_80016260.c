// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016260-0x80016304 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void Mem_Free_3(void *);
extern char lbl_80290B68[];
extern char lbl_80290B80[];
void fn_80016260(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80290B68;
    if (arg0->unk0x70 != 0) {
        Mem_Free_3((void *)arg0->unk0x70);
        arg0->unk0x70 = 0;
    }
    if (arg0->unk0x78 != 0) {
        Mem_Free_3((void *)arg0->unk0x78);
        arg0->unk0x78 = 0;
    }
    arg0->unk0x14 = (s32)lbl_80290B80;
    *(s32 *)(arg0->unk0x10 + 0xC) = arg0->unk0xC;
    *(s32 *)(arg0->unk0xC + 0x10) = arg0->unk0x10;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

