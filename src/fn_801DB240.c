// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801DB240-0x801DB310 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD604;
extern f32 lbl_802AD608;
extern f32 fn_8012570C(s32 arg0, s32 arg1);
extern s32 fn_801DB310(Unk_7258DEBD * arg0, f32 farg0, f32 farg1);
void fn_801DB240(Unk_C7387A53 *arg0) {
    volatile __ps_t pa;
    volatile __ps_t pb;
    __ps_t *base;
    f32 t;
    Unk_DF2324A8 *p;
    register void *p2 __asm__("r9");
    p = *((void * *)&arg0->unk0xC);
    base = &pa;
    pa = p->unk0x58;
    base[1] = p->unk0x60;
    t = fn_8012570C(QB_SKATER_SIDE_COLLIDE_LENGTH, 1);
    if (fn_801DB310(arg0, lbl_802AD604, t) != 0) {
        if (fn_801DB310(arg0, lbl_802AD608, t) != 0) {
            p2 = *((void * *)&arg0->unk0xC);
            ((Unk_DF2324A8 *)p2)->unk0x58 = pa;
            ((Unk_DF2324A8 *)p2)->unk0x60 = base[1];
        }
    } else {
        if (fn_801DB310(arg0, lbl_802AD608, t) != 0) {
            if (fn_801DB310(arg0, lbl_802AD604, t) != 0) {
                p2 = *((void * *)&arg0->unk0xC);
                ((Unk_DF2324A8 *)p2)->unk0x58 = pa;
                ((Unk_DF2324A8 *)p2)->unk0x60 = base[1];
            }
        }
    }
}
