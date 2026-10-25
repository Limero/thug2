// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033B98-0x80033BFC (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005527C(void *);
void fn_80033560(Unk_C8FEE62D *, void *);
extern char lbl_80291D60[];
void fn_80033B98(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80291D60;
    if ((s32) arg0->unk0x1C != 0) {
        fn_8005527C(*((void * *)&arg0->unk0x1C));
        arg0->unk0x1C = 0;
    }
    arg0->unk0x18 = 0;
    fn_80033560(arg0, arg1);
}
