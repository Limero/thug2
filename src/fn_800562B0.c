// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800562B0-0x80056308 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void strcpy(s32);
void fn_800562B0(Unk_CFB386B2 *arg0, s32 arg1, s32 arg2) {
    Unk_4E705049 *temp_r9;

    strcpy((char *)arg0 + 0x164);
    arg0->unk0x1E4 = arg2;
    arg0->unk0x278 = 1;
    temp_r9 = arg0->unk0x284;
    ((s32 (*)(void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18);
}
