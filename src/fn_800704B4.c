// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800704B4-0x80070570 (188B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80294D70[];
extern char lbl_80294D74[];
s32 fn_80128294(s32, s32, s32, s32);
bool fn_800704B4(Unk_B9B1CE48 *arg0, s32 arg1) {
    u32 sp8;

    sp8 = 0;
    fn_80128294(arg1, (s32)lbl_80294D70, &sp8, 0);
    arg0->unk0x10 = (u8) ((Unk_E01B0030 *)&sp8)->unk0x3;
    arg0->unk0x11 = (s8) (sp8 >> 8U);
    arg0->unk0x12 = (s8) (sp8 >> 0x10U);
    arg0->unk0x13 = (s8) (sp8 >> 0x18U);
    sp8 = -1U;
    fn_80128294(arg1, (s32)lbl_80294D74, &sp8, 0);
    arg0->unk0x14 = (u8) ((Unk_E01B0030 *)&sp8)->unk0x3;
    arg0->unk0x15 = (s8) (sp8 >> 8U);
    arg0->unk0x16 = (s8) (sp8 >> 0x10U);
    arg0->unk0x17 = (s8) (sp8 >> 0x18U);
    return true;
}
