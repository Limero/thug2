// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF320-0x801BF398 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AC50C;
extern f32 lbl_802AC510;
void fn_801BF320(Unk_B90C3F2D *arg0, __ps_t *arg1) {
    f32 c1;
    f32 c2;

    arg1[0] = arg0->unk0x48;
    c1 = lbl_802AC50C;
    arg1[1] = arg0->unk0x50;
    arg1[2] = arg0->unk0x58;
    c2 = *(volatile f32 *)&lbl_802AC510;
    {
        f32 *p;

        arg1[3] = arg0->unk0x60;
        arg1[4] = arg0->unk0x68;
        *(volatile __ps_t *)&arg1[5] = arg0->unk0x70;
        *(volatile f32 *)&((Unk_9BAABABE *)arg1)->unk0x30 = c1;
        p = (f32 *)((char *)arg1 + (s32)0x30);
        *(volatile f32 *)&p[2] = c1;
        *(volatile f32 *)&p[1] = c1;
        p[3] = c2;
    }
    ((Unk_9BAABABE *)arg1)->unk0x40 = arg0->unk0x38;
    ((Unk_9BAABABE *)arg1)->unk0x48 = arg0->unk0x40;
    ((Unk_9BAABABE *)arg1)->unk0x50 = arg0->unk0x34;
    ((Unk_9BAABABE *)arg1)->unk0x54 = arg0->unk0x114;
}
