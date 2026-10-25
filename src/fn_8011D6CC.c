// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D6CC-0x8011D74C (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038C8C0[];
extern s32 lbl_80302CC0;
s32 fn_8011BC38();
// ClearPlaylist @ 0x8011D6CC
void ClearPlaylist(s32 arg0) {
    s32 temp_r3;
    Unk_76B26A14 *temp_r9;

    temp_r3 = fn_8011BC38();
    if (temp_r3 == 0) {
        lbl_80302CC0 = temp_r3;
        temp_r9 = (char *)lbl_8038C8C0 + arg0 * 0xCB0;
        temp_r9->unk0xC88 = 0ULL;
        temp_r9->unk0xC90 = 0ULL;
        temp_r9->unk0xC98 = 0ULL;
        temp_r9->unk0xCA8 = 1;
        temp_r9->unk0xC80 = temp_r3;
        temp_r9->unk0xCA0 = 0ULL;
    }
}
