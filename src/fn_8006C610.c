// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C610-0x8006C694 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
extern s32 fn_8006F19C(s32);
extern s32 fn_8006F1B0(s32, s32);
extern void fn_8006F26C(s32, s32 *);
extern void fn_80083460(void);
extern char lbl_80301434[];

void fn_8006C610(void) {
    s32 sp8;
    s32 temp_r30;
    s32 var_r31;
    s32 temp_r29;
    fn_8006F19C(*(s32 *)lbl_80301434);
    var_r31 = fn_8006F1B0(*(s32 *)lbl_80301434, 0);
    if (var_r31 != 0) {
        do {
            temp_r30 = var_r31;
            var_r31 = fn_8006F1B0(*(s32 *)lbl_80301434, 0);
            temp_r29 = *(s32 *)lbl_80301434;
            sp8 = temp_r30;
            fn_8006F26C(temp_r29, &sp8);
            Mem_Free(temp_r30);
        } while (var_r31 != 0);
    }
    fn_80083460();
}
