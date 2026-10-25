// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195098-0x80195124 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012720C(s32, s32);
s32 fn_8004ADC8(s32, s32, s32, s32, s32);
extern char lbl_80300434[];
void fn_80195098(Unk_72E9CBBF *arg0) {
    char *var_r11;
    s32 var_ctr;
    void *var_r9;
    s32 one;

    var_ctr = 0x1E;
    arg0->unk0x4AC = 0;
    arg0->unk0x4B0 = 0;
    one = 1;
    var_r11 = (char *)arg0 + 0x4B4;
    var_r9 = (char *)arg0 + 0x7C;
    do {
        ((CStruct *)var_r9)->unk0x8 = one;
        *(s32 *)((char *)var_r9 - 0x8) = 0;
        *(s32 *)((char *)var_r9 - 0x4) = 0;
        ((CStruct *)var_r9)->unk0x0 = 0;
        *((s32 *)var_r11) = 0;
        var_r9 += 0x24;
        var_r11 += 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_8012720C(arg0->unk0x20, QB_SINGLE_COMBO_ADDED);
    fn_8004ADC8(*(s32 *)lbl_80300434, QB_TETRIS_TRICKS_MENU, 1, 1, 0);
}
