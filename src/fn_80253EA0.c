// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253EA0-0x80253EF0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"

register s32 r31_guard __asm__("r31");

extern void fn_80253060(void *arg0, s32 arg1, s32 arg2);

bool fn_80253EA0(Unk_65A9C034 *arg0, Unk_C8FEE62D *arg1) {
    register s32 a0 __asm__("r30");
    Unk_59E38960 *temp_r11;
    a0 = (s32)arg0;
    fn_80253060(arg0, arg1, 0);
    temp_r11 = *((void * *)&((Unk_C8FEE62D *)a0)->unk0x50);
    ((Unk_C8FEE62D *)a0)->unk0x18 = -1;
    temp_r11->unk0x28 = 0xFFFFFFFFFFFFFFFFULL;
    return false;
}
