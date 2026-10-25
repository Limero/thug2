// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3610-0x800F3674 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029B488[];
extern char lbl_8029B560[];
void fn_800F3610(Unk_C7387A53 *arg0, s32 arg1) {
    volatile s32 *p = (volatile s32 *)((char *)arg0 + 0x38);
    arg0->unk0x50 = (s32)lbl_8029B488;
    p[5] = (s32)lbl_8029B560;
    *(s32 *)(((CStruct *)p)->unk0x10 + 0xC) = ((CStruct *)p)->unk0xC;
    *(s32 *)(((CStruct *)p)->unk0xC + 0x10) = ((CStruct *)p)->unk0x10;
    p[4] = (s32)p;
    p[3] = (s32)p;
    if (arg1 & 1) {
        Mem_Free();
    }
}
