// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EDB94-0x801EDC4C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 Tmr_GetTime();
extern f32 lbl_802ADAC4;
extern s32 lbl_80303150;
extern void fn_801EE5AC(Unk_C7387A53 * arg0);
extern void fn_801EDD7C(Unk_DB0E2BAB * arg0);
void fn_801EDB94(Unk_C7387A53 *arg0) {
    char *temp_r10;
    Unk_4C649A8C *temp_r31;
    __ps_t *base;

    temp_r10 = (char *)((Unk_71062261 *)arg0->unk0x24)->unk0x15BC;
    if ((((Unk_1D62F22E_2 *)temp_r10)->unk0x1C == 0) ||
        (*(f32 *)((char *)arg0->unk0xC + 0xBC) < lbl_802ADAC4)) {
        temp_r31 = temp_r10 + 0x84;
        if (temp_r31->unk0x4 != 1) {
            temp_r31->unk0x4 = 1;
            temp_r31->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
    }
    if (*(s32 *)((char *)((Unk_71062261 *)arg0->unk0x24)->unk0x15BC + 0xC4) == 0) {
        fn_801EE5AC(arg0);
    }
    fn_801EDD7C(arg0);
    base = (__ps_t *)arg0->unk0xC;
    base[13] = base[11];
    base[14] = base[12];
}
