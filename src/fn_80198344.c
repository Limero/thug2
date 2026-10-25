// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198344-0x801983CC (136B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern char lbl_802AA7D8[];
extern char lbl_802AA808[];

void fn_801980C4(CScript *);
void CStruct_delete(CStruct *, s32);

void fn_80198344(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x24 = (s32)lbl_802AA7D8;
    fn_801980C4((s32)arg0);
    temp_r9 = (char *)arg0 + 0xC;
    temp_r9->unk0x14 = (s32)lbl_802AA808;
    *(s32 *)(temp_r9->unk0x10 + 0xC) =
        temp_r9->unk0xC;
    *(s32 *)(temp_r9->unk0xC + 0x10) =
        temp_r9->unk0x10;
    temp_r9->unk0xC = (s32)temp_r9;
    temp_r9->unk0x10 = (s32)temp_r9;
    CStruct_delete((s32)arg0 + 4, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
