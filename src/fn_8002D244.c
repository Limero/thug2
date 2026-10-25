// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D244-0x8002D2A0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_803003AC[];
void fn_80010544(s32, s32, s32);
void fn_8002D14C(Unk_FFAD6788 *, s32);
void fn_8002D244(void) {
    if ((s32) *(s32 *)&lbl_803003AC != 0) {
        fn_8002D14C(*(s32 *)&lbl_803003AC, 3);
    }
    *(s32 *)&lbl_803003AC = 0;
    fn_80010544(*(s32 *)&lbl_802FFE98, QB_ANIMHEAP, 1);
}
