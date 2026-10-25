// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D8484-0x800D8530 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_800F0838(s32 arg0, void *arg1);
s32 fn_800D81F0(Unk_87C37330 *arg0, CStruct *arg1, s32 arg2, void *arg3, s32 arg4);
void fn_800D68B8(Unk_87C37330 *arg0, s32 arg1);

void fn_800D8484(Unk_87C37330 *arg0, CStruct *arg1, s32 arg2) {
    f32 sp8[4];
    f32 sp18[4];
    s32 sp28;

    sp28 = 0;
    GetChecksum_2(arg1, QB_NAME, &sp28, 0);
    if (sp28 != 0) {
        fn_800F0838(sp28, sp8);
        *(__ps_t *)&sp18[0] = *(__ps_t *)&sp8[0];
        *(__ps_t *)&sp18[2] = *(__ps_t *)&sp8[2];
        if (fn_800D81F0(arg0, arg1, arg2, sp18, sp28) != 0) {
            fn_800D68B8(arg0, sp28);
            return;
        }
        arg0->unk0x138 = sp28;
    }
}
