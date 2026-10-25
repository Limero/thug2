// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9388-0x801A9430 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *lbl_80305EAC;
extern s32 fn_801A92F4(s32 arg0, s32 arg1);
extern s32 fn_801FC0E0(void);
extern void fn_801FBF18(s32 arg0, s32 arg1);
extern s32 Mem_NewZero(s32 arg0);
extern s32 fn_801A82DC(Unk_C8FEE62D * arg0, s32 arg1);
extern void fn_801A9DE8(CStruct * arg0, s32 *arg1, s32 arg2);
extern s32 fn_801A9494(s32 arg0, s32 arg1, s32 arg2);
bool fn_801A9388(s32 arg0, s32 arg1) {
    s32 temp_r5;
    register s32 t __asm__("r4");

    if (fn_801A92F4(arg0, arg1) != 0) {
        return false;
    }
    if (((Unk_71062261 *)lbl_80305EAC)->unk0x388 == QB_LOAD_SK5ED_GAMEPLAY) {
        fn_801FBF18(fn_801FC0E0(), arg1);
    }
    temp_r5 = fn_801A82DC(Mem_NewZero(0x60), arg1);
    fn_801A9DE8(arg0 + 8, &arg1, temp_r5);
    t = arg1;
    fn_801A9494(arg0, t, (((CStruct *)arg0)->unk0x4 += 1, t));
    return true;
}
