// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003F754-0x8003F80C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8004195C(void *, void *);

/* The want addresses arg0+0xD0 and arg0+0x88, each +0x18/+0x1C, as f32 pairs
   (stfs/lfs at +0xE8/+0xEC and +0xA0/+0xA4) — not the s32 pair CScript
   declares at those member offsets. */
typedef struct {
    char pad0x0[0x18];
    f32 f18;
    f32 f1C;
} F32Pair;

// CScreenElement_SetPos @ 0x8003F754
void CScreenElement_SetPos(Unk_C7387A53 *arg0, f32 farg0, f32 farg1, s32 arg1) {
    volatile double _dummy;
    volatile double _dummy2;
    F32Pair *p1;
    F32Pair *p2;

    p1 = (F32Pair *)((char *)arg0 + 0xD0);
    if ((p1->f18 != farg0) || (p1->f1C != farg1)) {
        p1->f18 = farg0;
        p1->f1C = farg1;
        arg0->unk0xC |= 0x400;
        fn_8004195C(arg0, p1);
    }
    if (arg1 != 0) {
        p2 = (F32Pair *)((char *)arg0 + 0x88);
        if ((p2->f18 != farg0) || (p2->f1C != farg1)) {
            p2->f18 = farg0;
            p2->f1C = farg1;
            arg0->unk0xC |= 0x400;
        }
    }
}
