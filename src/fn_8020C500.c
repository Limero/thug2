// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C500-0x8020C54C (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009F054(void *, u32, s32, f32);
extern f32 lbl_802AF3D0[];
s32 fn_8020C500(Unk_90685748 *arg0) {
    s32 temp_r9;

    temp_r9 = arg0->unk0x13FC + 1;
    arg0->unk0x13FC = temp_r9;
    if (temp_r9 > 3) {
        fn_8009F054(arg0->unk0xC, QB_SKATERSTARTINGRUN, 0,
                    lbl_802AF3D0[0]);
    }
}
