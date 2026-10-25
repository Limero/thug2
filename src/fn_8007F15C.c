// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F15C-0x8007F214 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct { f32 a; f32 b; f32 c; f32 d; } S4;

extern __ps_t lbl_80377A20[4];
extern f32 lbl_8029625C;
extern bool lbl_80377A40;
void fn_800071D4(s32);

s32 fn_8007F15C(Unk_9994C3F5 *arg0) {
    S4 a;
    S4 b;
    S4 *pa;
    S4 *pb;
    s32 temp_r3;
    f32 f;

    temp_r3 = arg0->unk0x8;
    if (temp_r3 != 0) {
        return temp_r3 + 0x10;
    }
    if (lbl_80377A40 == 0) {
        fn_800071D4((s32)lbl_80377A20);
        lbl_80377A40 = 1;
    }
    pa = &a;
    f = lbl_8029625C;
    pb = &b;
    pa->a = f;
    pa->b = f;
    pa->c = f;
    pa->d = f;
    pb->a = f;
    pb->b = f;
    pb->c = f;
    pb->d = f;
    lbl_80377A20[1] = *(__ps_t *)((char *)pa + 8);
    lbl_80377A20[0] = *(__ps_t *)pa;
    lbl_80377A20[2] = *(__ps_t *)pb;
    lbl_80377A20[3] = *(__ps_t *)((char *)pb + 8);
    return (s32)lbl_80377A20;
}
