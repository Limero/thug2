// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C780-0x8006C80C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80301430;
void fn_8006F3F4(s32, s32 *);
s32 fn_8006F338(s32, s32);
void fn_8006F324(s32);
void fn_8006C780(s32 arg0) {
    s32 sp8;
    Unk_73BE2E86 *temp_r30;
    Unk_73BE2E86 *var_r31;

    fn_8006F324(lbl_80301430);
    if ((var_r31 = (Unk_73BE2E86 *)fn_8006F338(lbl_80301430, 0)) != NULL) {
        do {
            temp_r30 = var_r31;
            var_r31 = (Unk_73BE2E86 *)fn_8006F338(lbl_80301430, 0);
            if (temp_r30->unk0x2A04 == arg0) {
                sp8 = (s32)temp_r30;
                fn_8006F3F4(lbl_80301430, &sp8);
                Mem_Free((s32)temp_r30);
            }
        } while (var_r31 != NULL);
    }
}
