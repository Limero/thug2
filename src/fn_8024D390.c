// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D390-0x8024D418 (136B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803CA324;
extern s32 lbl_803CA328;

// FLAG: -fno-schedule-insns
void fn_8024D390(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 flag;
    register s32 var_r9 __asm__("r9");
    register s32 fp;

    flag = lbl_803CA328;
    var_r9 = 1;
    if (flag == 0) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        if (arg0->unk0x10 != 0) {
            fp = lbl_803CA324;
            ((void (*)(void *))fp)((void *)arg0->unk0x10);
        }
        if (arg0->unk0x14 != 0) {
            fp = lbl_803CA324;
            ((void (*)(void *))fp)((void *)arg0->unk0x14);
        }
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
