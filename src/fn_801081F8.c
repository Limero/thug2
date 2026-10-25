// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801081F8-0x80108230 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302BDC;
extern s32 fn_800FB1A8(void *, Unk_C27060C6 *, Unk_5CB48605 *);
void fn_801081F8(Unk_F98363B0 *arg0) {
    s32 var_r5;
    char *temp_r4;

    var_r5 = arg0->unk0x1A40;
    temp_r4 = (char *)arg0 + 0x30;
    if (var_r5 == 0) {
        var_r5 = lbl_80302BDC;
    }
    fn_800FB1A8(arg0, temp_r4, var_r5);
}
