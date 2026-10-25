// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019B7C0-0x8019B834 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AAB7C[];
extern void fn_8019B768(void);
extern s32 Mth_Rnd(void);
void fn_8019B7C0(Unk_27F05558 *arg0) { s32 *var_r9; s32 var_ctr;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
    sprintf((char *)arg0 + 0x210, lbl_802AAB7C);
    var_ctr = 8;
    var_r9 = (char *)arg0 + 0x42C;
    do { *((s32 *)var_r9) = 0; var_r9 = (s32 *)((char *)var_r9 - 4); var_ctr -= 1; } while (var_ctr != 0);
    fn_8019B768();
    arg0->unk0x434 = Mth_Rnd();
}
