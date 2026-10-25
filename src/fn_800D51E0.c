// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D51E0-0x800D521C (60B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800D51E0(Unk_FCBBC883 *arg0) {
    void *p = *((void * *)&arg0->unk0xC);
    volatile __ps_t t[2];
    __ps_t *tp;
    f32 f;

    tp = (__ps_t *)t;
    __asm__("" : "+r"(tp));
    f = *((f32 *)&arg0->unk0x1E8);
    t[0] = ((Unk_DF2324A8 *)p)->unk0x58;
    tp[1] = ((Unk_DF2324A8 *)p)->unk0x60;
    *(f32 *)((char *)&t[0] + 4) = f;
    ((Unk_DF2324A8 *)p)->unk0x58 = t[0];
    ((Unk_DF2324A8 *)p)->unk0x60 = tp[1];
}
