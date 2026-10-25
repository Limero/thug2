// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D9B0-0x8002DA0C (92B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"

void Mem_NewZero(s32);
s32 fn_8002CB04(void);
void fn_8002D9B0(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2) {
    char *var_r31;
    s32 var_r30;

    var_r31 = (char *)arg0 + 4;
    var_r30 = 0x32;
    do {
        Mem_NewZero(0x16C);
        *(s32 *)var_r31 = fn_8002CB04();
        var_r30 -= 1;
        var_r31 += 4;
    } while (var_r30 != 0);
    arg0->unk0xD8 = arg2;
    arg0->unk0xD4 = arg1;
}
