// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024CA4-0x80024D00 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800551D4(void *);
void fn_80024740(Unk_9994C3F5 *, void *);
extern char lbl_80291448[];
void fn_80024CA4(CStruct *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80291448;
    if ((s32) arg0->unk0xC != 0) {
        fn_800551D4(arg0->unk0xC);
        arg0->unk0xC = 0;
    }
    fn_80024740(arg0, arg1);
}
