// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E984-0x8007E9E8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802962C8[];
void fn_8007EC7C(void *);
void fn_80093F48(s32, s32);
void fn_8005EF24(Unk_C8FEE62D *, s32);
void fn_8007E984(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_802962C8;
    fn_8007EC7C(arg0);
    if (arg0->unk0x30 != 0) {
        fn_80093F48(arg0->unk0x30, 3);
        arg0->unk0x30 = 0;
    }
    fn_8005EF24(arg0, arg1);
}
