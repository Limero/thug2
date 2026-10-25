// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CDC5C-0x800CDCD8 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8010631C(void *);
void fn_8009F558(Unk_C8FEE62D *, void *);
extern char lbl_802997C8[];
void fn_800CDC5C(CScript *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    arg0->unk0x18 = (s32)lbl_802997C8;
    if ( arg0->unk0x1C != NULL) {
        fn_8010631C(arg0->unk0x1C);
        temp_r11 = arg0->unk0x1C;
        if (temp_r11 != NULL) {
            temp_r9 = ((Unk_C7387A53 *)temp_r11)->unk0xC;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
    }
    fn_8009F558(arg0, arg1);
}
