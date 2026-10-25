// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1A08-0x800A1A84 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80009C00(CStruct *);
void fn_800A3680(Unk_C7387A53 *, void *);
extern char lbl_80297CB8[];
void fn_800A1A08(Unk_C7387A53 *arg0, s32 arg1) {
    void *temp_r11;
    Unk_4E705049 *temp_r9;

    arg0->unk0x2C = (s32)lbl_80297CB8;
    if ( arg0->unk0x4C != NULL) {
        fn_80009C00(arg0->unk0x4C);
        temp_r11 = arg0->unk0x4C;
        if (temp_r11 != NULL) {
            temp_r9 = ((CScript *)temp_r11)->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
        }
    }
    fn_800A3680(arg0, arg1);
}
