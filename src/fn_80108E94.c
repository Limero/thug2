// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80108E94-0x80108F30 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CC44;
extern void fn_80006F58(CStruct *);
extern void fn_80108F30(Unk_3782B8FE *);
void *fn_80108E94(Unk_181A4304 *arg0, Unk_EA529D06 *arg1, f32 farg0) {
    s32 i;
    Unk_5EF41E38 *temp_r10;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f13;

    fn_80006F58(arg0);
    for (i = 0; i < 0x20; i++) {
        __asm__ volatile("" ::: "memory");
    }
    temp_r10 = (char *)arg0 + 0x620;
    for (i = 0; i < 0x20; i++) {
        __asm__ volatile("" ::: "memory");
    }
    ((__ps_t *)arg0)[0] = ((__ps_t *)arg1)[0];
    temp_f0 = 0.0f;
    arg0->unk0x8 = arg1->unk0x8;
    temp_f1 = lbl_8029CC44;
    arg0->unk0x10 = farg0;
    arg0->unk0x620 = temp_f0;
    ((Unk_4C649A8C *)temp_r10)->unk0xC = temp_f1;
    temp_r10->unk0x8 = temp_f0;
    temp_r10->unk0x4 = temp_f0;
    arg0->unk0x630 = temp_f0;
    fn_80108F30(arg0);
    return arg0;
}
