// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209D4C-0x80209DE4 (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80209C1C(Unk_8D6DF6EE * arg0, s32 arg1, s32 arg2, s32 arg3);

void fn_80209D4C(Unk_76553646 *arg0) {
    s32 *var_r31;
    s32 var_r29;

    if (((s32) arg0->unk0x12A8 != 0) && ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x20) + 0x80) != 0)) {
        fn_80209C1C(arg0, arg0->unk0x12A8, -5, 1);
        if ((s32) arg0->unk0x12AC != 0) {
            return;
        }
    }
    var_r29 = 0;
    if (var_r29 < (s32) arg0->unk0x127C) {
        var_r31 = (s32 *)((char *)arg0 + (s32)0x1280);
        do {
            fn_80209C1C(arg0, *(s32 *)((char *)var_r31), -1, 0);
            var_r29 += 1;
            var_r31 += 1;
        } while (var_r29 < (s32) arg0->unk0x127C);
    }
}
