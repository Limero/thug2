// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FFAB8-0x800FFB58 (160B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800FFAB8(Unk_397FCF61 *arg0, CStruct *arg1, Unk_EA529D06 *arg2) {
    volatile __ps_t sp8[2];
    volatile __ps_t *pv;
    if ((*((f32 *)&arg1->unk0x0) != arg0->unk0x50) ||
        (*((f32 *)&arg1->unk0x4) != arg0->unk0x54) ||
        (*((f32 *)&arg1->unk0x8) != arg0->unk0x58)) {
        return;
    }
    pv = sp8;
    sp8[0] = arg2->unk0x0;
    pv[1] = arg2->unk0x8;
    sp8[0] = __builtin_ps_mul(sp8[0], arg0->unk0x10);
    pv[1] = __builtin_ps_mul(pv[1], arg0->unk0x18);
    {
        void *vt = arg0->unk0xC;
        ((void (*)(void *, void *))((Unk_B79F8E21 *)vt)->unk0xCC)(
            (char *)arg0 + ((Unk_B79F8E21 *)vt)->unk0xC8, (void *)pv);
    }
}