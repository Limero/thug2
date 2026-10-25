// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002E050-0x8002E0F8 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80291A48[];
extern char lbl_802918F8[];
extern char lbl_80291A48[];
extern char lbl_80291AA8[];
void fn_8002E050(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x14 = (s32)lbl_80291A48;
    fn_80031FC4();
    temp_r9 = (char *)arg0 + 0x18;
    temp_r9->unk0x14 = (s32)lbl_802918F8;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x10) + 0xC) =  temp_r9->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0xC) + 0x10) =  temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    arg0->unk0x14 = (s32)lbl_80291AA8;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0xC) =  arg0->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x10) =  arg0->unk0x10;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}