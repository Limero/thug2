// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B80B8-0x800B8178 (192B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void CStruct_delete(CStruct *, s32);
extern char lbl_80298E98[];

void fn_800B80B8(s32 arg0, s32 arg1) {
    register s32 r31 asm("r31") = arg0;
    register s32 r30 asm("r30") = arg1;
    ((Unk_4A5A39DD *)r31)->unk0x18 = (s32)lbl_80298E98;
    if (((Unk_4A5A39DD *)r31)->unk0x64 != 0) {
        Mem_Free2(((Unk_4A5A39DD *)r31)->unk0x64);
    }
    if (((Unk_4A5A39DD *)r31)->unk0x90 != 0) {
        Mem_Free2(((Unk_4A5A39DD *)r31)->unk0x90);
    }
    if (((Unk_4A5A39DD *)r31)->unk0x98 != 0) {
        Mem_Free2(((Unk_4A5A39DD *)r31)->unk0x98);
    }
    if (((Unk_4A5A39DD *)r31)->unk0xA0 != 0) {
        Mem_Free2(((Unk_4A5A39DD *)r31)->unk0xA0);
    }
    if (((Unk_4A5A39DD *)r31)->unk0xDC != 0) {
        CStruct_delete(((Unk_4A5A39DD *)r31)->unk0xDC, 3);
    }
    if (((Unk_4A5A39DD *)r31)->unk0xE4 != 0) {
        CStruct_delete(((Unk_4A5A39DD *)r31)->unk0xE4, 3);
    }
    if (((Unk_4A5A39DD *)r31)->unk0xE0 != 0) {
        CStruct_delete(((Unk_4A5A39DD *)r31)->unk0xE0, 3);
    }
    fn_8009F558(r31, r30);
}
