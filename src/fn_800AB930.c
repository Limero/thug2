// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB930-0x800AB990 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800ADCD4(Unk_4A70D538 *);
s32 fn_800AB930(Unk_4A70D538 *arg0) {
    s32 var_r30;

    if ((s32) arg0->unk0x34B8 != 0) {
        var_r30 = 0;
        if ((fn_800ADCD4(arg0) != 0) && ((s32) arg0->unk0x3460 != 0)) {
            var_r30 = 1;
        }
        return var_r30;
    }
    return 0;
}
