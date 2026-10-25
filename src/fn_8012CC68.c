// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CC68-0x8012CC9C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803032A8[];
void fn_8012CC68(s32 arg0) {
    CStruct *var_r9;

    var_r9 = *(void * *)&lbl_803032A8;
    if (var_r9 != NULL) {
        do {
            if ((s32) var_r9->unk0x4 == arg0) {
                var_r9->unk0x4 = 0;
            }
            var_r9 = var_r9->unk0x5C;
        } while (var_r9 != NULL);
    }
}
