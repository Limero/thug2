// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80132010-0x801320EC (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012F024(Unk_651D75B3 *);
void fn_800A473C(void *, void *, void *);
typedef struct {
    unsigned int top : 4;
    unsigned int rest : 28;
} BitF4;
bool fn_80132010(Unk_651D75B3 *arg0, s32 *arg1) {
    s32 temp_r9;
    s32 temp_r9_2;
    s32 temp_r10;
    s32 var_r8;
    if ((s32) arg0->unk0xA4 == 3) {
        temp_r9 = arg0->unk0xA8;
        if ((temp_r9 != 0) && ((s32) *arg1 == temp_r9)) {
            fn_8012F024(arg0);
        }
    }
    var_r8 = 0;
    while (var_r8 < (s32) arg0->unk0x38) {
        Unk_C7387A53 *temp_r11 = (Unk_C7387A53 *)(var_r8 * 0x2C + arg0->unk0x94);
        temp_r10 = temp_r11->unk0x28;
        if ((s32)(temp_r10 & QB_UNKNOWN_0xF0000000) == QB_UNKNOWN_0x30000000) {
            temp_r9_2 = temp_r11->unk0x20;
            if ((temp_r9_2 != 0) && ((s32) *arg1 == temp_r9_2)) {
                ((BitF4 *)&temp_r11->unk0x28)->top = 0;
            }
        }
        var_r8 += 1;
    }
    if ((s32) arg0->unk0xE0 != 0) {
        fn_800A473C((void *)arg0->unk0xE0, arg1, arg0);
    }
    return true;
}