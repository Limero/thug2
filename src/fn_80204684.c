// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204684-0x80204718 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_802AF03C;
extern char lbl_802AF070[];

void fn_8009F53C(void *);

typedef struct {
    s32 f00;
    u32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    void *f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38[28];
    f32 fA8;
    s32 fAC;
    s32 fB0;
    s32 fB4;
    s32 fB8;
    f32 fBC;
    s32 fC0;
    u32 fC4;
    s32 fC8;
} Obj4684;

void *fn_80204684(Obj4684 *arg0) {
    f32 f;

    fn_8009F53C(arg0);
    f = lbl_802AF03C;
    arg0->f18 = lbl_802AF070;
    arg0->f04 = 0x1859F772;
    arg0->f20 = 0;
    arg0->f28 = 0;
    arg0->f2C = 0;
    arg0->fA8 = f;
    arg0->fAC = 0;
    arg0->fB4 = 0;
    arg0->fB8 = 0;
    arg0->fC0 = 0;
    arg0->f30 = 0;
    arg0->fBC = f;
    arg0->f34 = 0;
    arg0->fC4 = 0x1CA1FF20;
    arg0->fC8 = 1;
    return arg0;
}
