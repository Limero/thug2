// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002AE94-0x8002AEF4 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_8002AE84(Unk_C7387A53 *, s32);
s32 fn_8002AE7C(void);
void fn_8002BA5C(CStruct *, s32);
bool fn_8002AE94(Unk_C7387A53 *arg0) {
    s32 temp_r3;
    s32 var_r31;

    temp_r3 = fn_8002AE7C();
    for (var_r31 = 0; var_r31 < temp_r3; var_r31 += 1) {
        fn_8002BA5C(fn_8002AE84((void *)arg0, var_r31), 1);
    }
    return true;
}
