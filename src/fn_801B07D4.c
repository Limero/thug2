// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B07D4-0x801B0874 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80128610(s32, s32, s32, s32);
extern char lbl_802ABD98[];
s32 fn_801B04AC(s32, s32);
s32 fn_80129528(s32, s32);
void fn_801B07D4(CStruct *arg0, CStruct *arg1) {
    void *sp8;
    s32 t_r11;
    s32 t_r30;
    s32 i;

    sp8 = NULL;
    fn_80128610(arg1, (s32)lbl_802ABD98, &sp8, 0);
    t_r11 = arg0->unk0x4;
    if (t_r11 == (s32)((CStruct *)sp8)->unk0x4) {
        for (i = 0; i < (s32)arg0->unk0x4; i++) {
            t_r30 = arg0->unk0x8 + i * 0x14;
            fn_801B04AC(t_r30, fn_80129528(sp8, i));
        }
    }
}
