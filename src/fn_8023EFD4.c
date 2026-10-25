// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EFD4-0x8023F038 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802FFE98[];
extern s32 lbl_8030600C;
s32 fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_8023FB4C(void);
s32 fn_8023EF44(void);
s32 fn_8000F320(Unk_F12C5E01 *);
void fn_8023EFD4(void) {
    s32 temp_r30;

    if (lbl_8030600C == 0) {
        temp_r30 = *(s32 *)&lbl_802FFE98;
        fn_8000F2F8(temp_r30, fn_8023FB4C());
        Mem_Alloc2(0x10);
        lbl_8030600C = fn_8023EF44();
        fn_8000F320(*(s32 *)&lbl_802FFE98);
    }
}
