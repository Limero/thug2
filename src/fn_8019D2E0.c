// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D2E0-0x8019D32C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80009C00(CStruct *);
void fn_8019D2E0(CScript *arg0) {
    s32 *var_r31;
    s32 temp_r3;
    s32 var_r30;

    var_r30 = 4;
    var_r31 = (s32 *)((char *)arg0 + (s32)0x28);
    fn_80009C00(arg0->unk0x18);
    do {
        temp_r3 = *(s32 *)var_r31;
        var_r31 += 1;
        fn_80009C00(temp_r3);
        var_r30 -= 1;
    } while (var_r30 != 0);
}
