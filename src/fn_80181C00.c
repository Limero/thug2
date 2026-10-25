// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80181C00-0x80181C78 (120B). Byte-identical.
#include "types.h"
#include "structs.h"

void *fn_80182F98(CStruct * arg0, s32 arg1);
s32 StrStr(u8 * arg0, u8 * arg1);

s32 fn_80181C00(Unk_FFAD6788 *arg0, void *arg1) {
    s32 var_r29;
    s32 var_r31;

    var_r29 = 0;
    var_r31 = 0;
    if (var_r29 < arg0->unk0x68) {
        do {
            if (StrStr((char *)fn_80182F98((char *)arg0 + 0x54, var_r31) + 0x1C, arg1) != 0) {
                var_r29 += 1;
            }
            var_r31 += 1;
        } while (var_r31 < arg0->unk0x68);
    }
    return var_r29;
}
