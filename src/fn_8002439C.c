// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002439C-0x8002448C (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} q4;

typedef struct {
    char pad0x0[0x8];
    void *vtable;
    char pad0xC[0x4C];
    q4 qb;                            /* +0x58 = (0,0,0,1) */
    q4 qa;                            /* +0x68 = (0,0,0,1) */
    f32 f78, f7C, f80, f84, f88, f8C, f90, f94;
    f32 f98, f9C, fA0, fA4, fA8, fAC, fB0, fB4;
    char pad0xB8[0xC];
    f32 fC4, fC8, fCC;
} Obj;

extern char lbl_80291348[];
extern f32 lbl_80291320;             /* 1.0f    */
extern f32 lbl_80291324;             /* 0.0f    */
extern f32 lbl_80291328;             /* 12.0f   */
extern f32 lbl_8029132C;             /* 12000.0f */
void fn_8009E004(Obj *);
f32 fn_8005E1DC(void);
void fn_800244BC(Obj *, f32);

void *fn_8002439C(Obj *arg0) {
    volatile double _dummy;
    f32 t31;
    f32 t0;
    f32 t12;
    f32 t13;
    s32 i;
    q4 *qa;
    q4 *qb;

    fn_8009E004(arg0);
    i = 4;
    arg0->vtable = lbl_80291348;
    do {
        i--;
    } while (i != 0);
    t31 = lbl_80291320;
    arg0->fCC = t31;
    fn_800244BC(arg0, fn_8005E1DC());
    *(volatile f32 *)&arg0->f78 = t31;
    t0 = lbl_80291324;
    t12 = lbl_80291328;
    t13 = lbl_8029132C;
    arg0->fC4 = t12;
    arg0->fC8 = t13;
    arg0->f7C = t0;
    arg0->f80 = t0;
    arg0->f84 = t0;
    arg0->f88 = t0;
    arg0->f8C = t31;
    arg0->f90 = t0;
    arg0->f94 = t0;
    arg0->f98 = t0;
    arg0->f9C = t0;
    arg0->fA0 = t31;
    arg0->fA4 = t0;
    arg0->fA8 = t0;
    arg0->fAC = t0;
    arg0->fB0 = t0;
    arg0->fB4 = t31;
    qa = &arg0->qa;
    arg0->qa.x = t0;
    qa->y = t0;
    qa->z = t0;
    qa->w = t31;
    qb = &arg0->qb;
    arg0->qb.x = t0;
    qb->y = t0;
    qb->z = t0;
    qb->w = t31;
    return arg0;
}
