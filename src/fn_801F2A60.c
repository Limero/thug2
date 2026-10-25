// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2A60-0x801F2AE0 (128B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_803A3078[];
extern char lbl_802AE24C[];
extern char lbl_802AE280[];
extern void sprintf(s32, ...);
extern s32 Script_GenerateCRC(s32);

s32 fn_801F2A60(Unk_7258DEBD *arg0, s32 arg1) {
    if (arg1 == 0) {
        sprintf((s32)lbl_803A3078, (s32)lbl_802AE24C, arg0->unk0x2C0);
    } else if (arg1 <= 1) {
        return 0;
    } else {
        sprintf((s32)lbl_803A3078, (s32)lbl_802AE280, arg0->unk0x2C0, arg1 - 2);
    }
    return Script_GenerateCRC(lbl_803A3078);
}
