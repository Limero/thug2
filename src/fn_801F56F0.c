// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F56F0-0x801F576C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
extern Unk_71062261 *lbl_80305EAC;
extern s32 fn_801F46B0(Unk_13D0EFB0 * arg0);
void fn_801F56F0(Unk_6D855448 *arg0) {
    if (fn_801F46B0(arg0->unk0xAC00) == 1 || fn_801F46B0(arg0->unk0xAC00) == 2) {
        register Unk_71062261 *eac __asm__("r11");
        eac = lbl_80305EAC;
        if (eac->unk0x388 != -QB_UNKNOWN_0x174B47CA) {
            ((Unk_C7387A53 *)arg0->unk0xAC08)->unk0x94 = 0;
        } else {
            ((Unk_C7387A53 *)arg0->unk0xAC08)->unk0x94 = 1;
        }
    } else {
        ((Unk_C7387A53 *)arg0->unk0xAC08)->unk0x94 = 1;
    }
}
