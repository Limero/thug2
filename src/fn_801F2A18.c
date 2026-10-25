// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F2A18-0x801F2A60 (72B). Byte-identical.
#include "types.h"

extern char lbl_803A3014[];
extern char lbl_802AE2DC[];
extern void sprintf(s32, ...);
extern s32 Script_GenerateCRC(s32);

void fn_801F2A18(s32 arg0, s32 arg1) {
    sprintf((s32)lbl_803A3014, (s32)lbl_802AE2DC, arg1);
    Script_GenerateCRC(lbl_803A3014);
}
