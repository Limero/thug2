// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010C1C-0x80010CAC (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800107F0(void *, void *);
#include "structs.h"
#include "mem.h"
s32 fn_80010A68(s32, s32);
extern char lbl_80290648[];
extern char lbl_802906B8[];
void fn_80010C1C(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x80 = (s32)lbl_80290648;
    fn_800107F0(arg0->unk0x34, arg0);
    fn_80010A68((char *)arg0 + 0x60, 2);
    temp_r9 = (char *)arg0 + 0x48;
    temp_r9->unk0x14 = (s32)lbl_802906B8;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
