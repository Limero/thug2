// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802099A0-0x80209A2C (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8020989C(Unk_59E38960 * arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_802099A0(Unk_90685748 *arg0) {
    s32 *var_r30;
    s32 var_r29;

    if (((arg0->unk0x1274 != 0)) && ((*(s32 *)(arg0->unk0x20 + 0x80) != 0))) {
        fn_8020989C((s32)arg0, arg0->unk0x1274, 1, arg0->unk0x1278);
    }
    for (var_r29 = 0; var_r29 < (arg0->unk0x1248); var_r29++) {
        fn_8020989C((s32)arg0, *(s32 *)((char *)arg0 + 0x124C + var_r29 * 4), 0, arg0->unk0x1278);
    }
}
