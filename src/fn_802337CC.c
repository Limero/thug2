// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802337CC-0x8023389C (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_80238964();
u8 *fn_80238970();

/* 6-byte word/halfword pair copied out of the entity at +0x3524 */
struct SB {
    s32 w;
    u16 h;
    u16 _ph;
};

void fn_80238784(__ps_t *, u8 *, struct SB *, f32 *);

s32 fn_802337CC(CStruct *arg0, f32 farg) {
    struct { struct SB sb; __ps_t c0; __ps_t c1; f32 spT[3]; __ps_t spA[2]; } all;
    struct SB *psb;
    f32 x;
    Unk_BE7EBD4F *t = (Unk_BE7EBD4F *)fn_80238964();

    psb = &all.sb;
    {
        s32 w = t->unk0x3524;
        u16 h = t->unk0x3528;
        psb->w = w;
        psb->h = h;
    }
    fn_80238784(&all.spA[0], fn_80238970(), psb, &all.spT[0]);
    *(volatile __ps_t *)&all.c0 = all.spA[0];
    *(volatile __ps_t *)&all.c1 = all.spA[1];
    x = *((f32 *)&arg0->unk0x0);
    if ((x > ((f32 *)&all.c0)[0] + farg) && (x < (((f32 *)&all.c0)[0] + all.spT[0]) - farg)) {
        f32 y = *((f32 *)&arg0->unk0x8);
        if ((y > ((f32 *)&all.c1)[0] + farg) && (y < (((f32 *)&all.c1)[0] + all.spT[2]) - farg)) {
            return 1;
        }
    }
    return 0;
}
