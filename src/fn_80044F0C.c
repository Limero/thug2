// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044F0C-0x80044F60 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80054FB8(void *);
void fn_8003F608(Unk_E2A1CCEB *, void *);
extern char lbl_80292668[];
void fn_80044F0C(Unk_4313CFEA *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80292668;
    if ((s32) arg0->unk0x198 != 0) {
        fn_80054FB8(arg0->unk0x198);
    }
    fn_8003F608(arg0, arg1);
}
