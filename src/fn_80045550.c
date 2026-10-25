// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80045550-0x800455A4 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80054FF8(void *);
void fn_8003F608(Unk_E2A1CCEB *, void *);
extern char lbl_80292718[];
void fn_80045550(Unk_20363668 *arg0, s32 arg1) {
    *((s32 *)&arg0->unk0x8) = (s32)lbl_80292718;
    if ((s32) arg0->unk0x194 != 0) {
        fn_80054FF8(arg0->unk0x194);
    }
    fn_8003F608(arg0, arg1);
}
