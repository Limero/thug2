// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80245410-0x80245500 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_802445E8(Unk_6E48A312 *, s32, s32, s32, Unk_EA529D06 *, f32);
void fn_80245318(void *, Unk_F96D0DC8 *);
void fn_801F96B4(Unk_C7387A53 *, void *, void *, f32);
void fn_801F9734(Unk_C7387A53 *, void *, void *, f32);

void fn_80245410(Unk_09BB4394 *arg0, void *arg1, f32 farg0, s32 arg2) {
    __ps_t sp8[2];
    Unk_C8FEE62D *walker;
    u32 x;
    u32 y;
    Unk_EA529D06 *spp;
    x = ((u32)(arg0->unk0x7 + arg0->unk0x9)) >> 1;
    y = ((u32)(arg0->unk0x8 + arg0->unk0xA)) >> 1;
    walker = *((s32 * *)&arg0->unk0xC);
    if (walker != NULL) {
        do {
            spp = sp8;
            __asm__("" : "+r"(spp));
            ((Unk_EA529D06 *)sp8)->unk0x0 = ((__ps_t *)arg1)[0];
            spp->unk0x8 = ((__ps_t *)arg1)[1];
            fn_802445E8((s32)walker, x, arg2, y, spp, farg0);
            walker = *((s32 * *)&walker->unk0x18);
        } while (walker != NULL);
    }
    fn_80245318(sp8, arg0);
    walker = *((s32 * *)&arg0->unk0x10);
    if (walker != NULL) {
        do {
            fn_801F96B4(walker, sp8, arg1, farg0);
            fn_801F9734(walker, sp8, arg1, farg0);
            walker = *((s32 * *)&walker->unk0x4);
        } while (walker != NULL);
    }
}
