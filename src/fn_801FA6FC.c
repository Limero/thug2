// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA6FC-0x801FA74C (80B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_801F9B90(Unk_C7387A53 * arg0, void *arg1);
extern void *fn_801FB248(Unk_C7387A53 * arg0);

s32 fn_801FA6FC(Unk_C7387A53 *arg0, Unk_C7387A53 *arg1, void *arg2) {
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = fn_801F9B90(arg1, arg2);
    var_r3 = 0;
    if (temp_r3 != 0) {
        *(s32 *)((char *)fn_801FB248((void *)arg0) + 0xC) = temp_r3;
        var_r3 = 1;
    }
    return var_r3;
}
