// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B7F4-0x8007B848 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80295C18[];
extern void fn_8007B938(Unk_9994C3F5 *);
extern void fn_80058580(CStruct *, s32);
void fn_8007B7F4(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_80295C18;
    if ((s32) arg0->unk0x8 != 0) {
        fn_8007B938(arg0);
    }
    fn_80058580(arg0, arg1);
}
