// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ADC54-0x800ADCD4 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_8030044C[];
void fn_8000F320(Unk_F12C5E01 *);
void fn_8000FF18(Unk_C6DE1362 *, s32);
s32 fn_8000F16C(Unk_4897C6F8 *);
void fn_80068528(CStruct *, s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_800ADC54(void) {
    s32 var_r3;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x118);
    fn_80068528(*(s32 *)&lbl_8030044C, 0x25800);
    var_r3 = fn_8000F16C(*(void * *)&lbl_802FFE98);
    if (var_r3 > 0x7FFC00) {
        var_r3 = 0x7FFC00;
    }
    fn_8000FF18(*(void * *)&lbl_802FFE98, var_r3 + QB_UNKNOWN_0xFFFE7000);
    fn_8000F320(*(void * *)&lbl_802FFE98);
}
