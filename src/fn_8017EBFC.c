// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017EBFC-0x8017EC44 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80182FA8(Unk_C7387A53 *);
extern void *fn_80183050(CStruct *);
s32 fn_8017EBFC(s32 arg0) {
    s32 temp_r31;

    temp_r31 = arg0 + 0x54;
    if (fn_80182FA8(temp_r31) == 0) {
        return 0;
    }
    return *(s32 *)((char *)fn_80183050(temp_r31) + 0x10);
}
