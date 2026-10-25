// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80108F54-0x80108F94 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80302BE0;
extern s32 fn_800FB5B8(CStruct *, Unk_BAC887D8 *, Unk_5CB48605 *);
void fn_80108F54(Unk_3782B8FE *arg0, s32 arg1) {
    s32 var_r5;
    char *temp_r4;

    var_r5 = arg0->unk0xC68;
    arg0->unk0x63C = 1;
    temp_r4 = (char *)arg0 + 0x18;
    if (var_r5 == 0) {
        var_r5 = lbl_80302BE0;
    }
    fn_800FB5B8(arg0, temp_r4, var_r5);
}
