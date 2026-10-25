// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023CDCC-0x8023CE8C (192B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef struct { s32 w; u16 h; } pair_t;
extern s32 fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
extern s32 fn_80237454(Unk_673C6403 *, Unk_F5317C5D *, s32, s32, s32);
extern void fn_802451A4(Unk_F96D0DC8 *, void *, Unk_F96D0DC8 *);
s32 fn_8023CDCC(Unk_D329255D *arg0) {
    volatile pair_t sp8;
    pair_t sp16;
    Unk_897A0ACF *ptr;
    pair_t *t;
    pair_t *op;
    s32 tw;
    u16 th;
    fn_80240B0C((s32)&sp8, 0, 0, 0, 0, 0, 0);
    if (arg0->unk0x74 == 5) {
        if (arg0->unk0x64 != 0) {
            fn_802451A4(*((void * *)&arg0->unk0x64), arg0, (s32)&sp8);
            ptr = (pair_t *)&sp8;
        } else {
            return 0;
        }
    } else {
        t = (pair_t *)&sp8;
        sp8.w = arg0->unk0x4;
        t->h = arg0->unk0x8;
        __asm__("" : "+r"(t));
        ptr = t;
    }
    tw = sp8.w;
    op = &sp16;
    th = ptr->unk0x4;
    sp16.w = tw;
    sp16.h = th;
    return fn_80237454(arg0->unk0x0, op, 0, 0, 1);
}
