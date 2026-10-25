// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80254720-0x80254764 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;

register s32 r31_guard __asm__("r31");

extern void fn_80257CC4(void *arg0, s32 arg1);
extern s32 fn_8024EECC(void * arg0, s32 arg1, s32 arg2);

void fn_80254720(void *arg0) {
    register s32 a0 __asm__("r30");
    s32 lblv;
    a0 = (s32)arg0;
    fn_80257CC4((void *)a0, 0x20);
    lblv = lbl_803CA340;
    ((Unk_31DE137E *)a0)->unk0x1C = fn_8024EECC(lblv, 1, 0xB24);
}
