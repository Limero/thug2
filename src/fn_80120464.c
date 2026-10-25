// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120464-0x801204CC (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8011EC64(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5);
extern char lbl_8038F0C0[];
extern s32 lbl_8038F714[];
extern s32 lbl_8038F720[];
extern char lbl_8039D940[];
s32 memset(s32, s32, s32);
// PCMAudio_Init @ 0x80120464
void PCMAudio_Init(void) {
    memset((s32)lbl_8038F0C0, 0, 0x654);
    memset((s32)lbl_8039D940, 0, 0x194);
    fn_8011EC64(&lbl_8038F714[0], &lbl_8038F714[1], &lbl_8038F714[2], &lbl_8038F720[0], &lbl_8038F720[1], &lbl_8038F720[2]);
}
