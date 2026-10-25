// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023FAC4-0x8023FB40 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_80306084[];
extern Unk_FFAD6788 * lbl_80306088;
void fn_8000F9C4(Unk_FFAD6788 *, Unk_C7387A53 *);
void fn_802408FC(void);
void fn_8024096C(void);
void fn_802409DC(void);
void fn_8023FAC4(void) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    fn_802408FC();
    fn_8024096C();
    fn_802409DC();
    fn_8000F9C4(*(s32 *)&lbl_802FFE98, lbl_80306088);
    temp_r11 = *(void * *)&lbl_80306084;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
    }
    lbl_80306088 = 0;
    *(void * *)&lbl_80306084 = NULL;
}
