// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011D788-0x8011D804 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8038C8C0[];
extern s32 lbl_80302CA4;
extern s32 lbl_80302CB0;
s32 fn_8011BC38();
void fn_8011D788(s32 arg0) {
    s32 temp_r3;
    Unk_76B26A14 *temp_r11;
    temp_r3 = fn_8011BC38();
    if (temp_r3 == 0) {
        lbl_80302CB0 = (arg0 != 0) ? 1 : 0;
        temp_r11 = (Unk_76B26A14 *)((char *)lbl_8038C8C0 + lbl_80302CA4 * 0xCB0);
        temp_r11->unk0xC98 = 0ULL;
        temp_r11->unk0xCA0 = 0ULL;
    }
}
