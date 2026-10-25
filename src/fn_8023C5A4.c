// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C5A4-0x8023C608 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802FFE98[];
extern s32 lbl_80306008;
s32 fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_8023FB4C(void);
s32 fn_8023C3AC(void);
s32 fn_8000F320(Unk_F12C5E01 *);
void fn_8023C5A4(void) {
    s32 temp_r30;

    if (lbl_80306008 == 0) {
        temp_r30 = *(s32 *)&lbl_802FFE98;
        fn_8000F2F8(temp_r30, fn_8023FB4C());
        Mem_Alloc2(0xD0);
        lbl_80306008 = fn_8023C3AC();
        fn_8000F320(*(s32 *)&lbl_802FFE98);
    }
}
