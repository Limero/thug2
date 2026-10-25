// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135C80-0x80135D00 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern bool lbl_8039D508;
extern char lbl_8039D50C[];
extern s32 lbl_8039DAD0;
void audioDecode(void);
s32 VAUDDecode(s32, void *, s32, s32, s32, s32);
// AUDSimpleAudioDecode @ 0x80135C80
bool AUDSimpleAudioDecode(Unk_897A0ACF *arg0, s32 arg1) {
    s32 *temp_r9;
    s32 var_r6;
    u16 temp_r4;

    temp_r9 = *(s32 * *)&lbl_8039D50C;
    var_r6 = 3;
    if (temp_r9 != NULL) {
        var_r6 = *((s32 *)temp_r9);
    }
    temp_r4 = arg0->unk0x4;
    if (VAUDDecode(lbl_8039DAD0, (char *)arg0 + temp_r4, arg1 - temp_r4, var_r6, (s32)audioDecode, 0) == 0)
        return false;
    lbl_8039D508 = 1;
    return true;
}
