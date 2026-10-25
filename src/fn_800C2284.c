// Promoted from src/wip — byte-identical match — hand reconstruction of the 480B-object
// angular integration loop (family: 0x800C2xxx — same skeleton as 800C70A4)
// family=m2c range=0x800C2284-0x800C2320 size=156B
// STATUS (2026-08-21): head restructured per the 800C4734/800C48A0 EXACTs:
// `if (cnt-- == 0) return;` early-return form puts the head decrement in the
// cmpwi->beqlr shadow; constants declared in the block AFTER the guards;
// bottom `cnt--; } while (cnt != -1);` (cmpwi/addi/bne).
#include "types.h"
#include "structs.h"
extern f32 lbl_80299048;   /* 0.5f */
extern f32 lbl_8029904C;   /* 628.3185f = 200*pi */
extern f32 lbl_80299050;   /* 314.1593f = 100*pi */
extern f32 lbl_80299054;   /* 0.0f */

void fn_800C2284(Unk_C7387A53 *obj) {
    s32 *u = (s32 *)obj;
    f32 *f = (f32 *)obj;
    int cnt;
    cnt = u[0x1AC / 4];
    if (cnt-- == 0)
        return;
    {
    f32 c1 = lbl_80299048;
    f32 c2 = lbl_8029904C;
    f32 c3 = lbl_80299050;
    f32 c4 = lbl_80299054;
    do {
        char *base = *((char * *)&obj->unk0x2F0);
        f32 dt = f[0x158 / 4];
        f32 *o = (f32 *)(base + cnt * 480);
        f32 pos = o[0xA4 / 4];
        f32 vel = o[8 / 4];
        f32 ang = o[0xC / 4];
        f32 nv = vel - dt * c1 * pos;
        f32 na = dt * nv + ang;
        *(volatile f32 *)&o[0xC / 4] = na;
        if (na > c2)
            na -= c3;
        else if (na < c4)
            na += c3;
        else
            continue; // in-range: skip the rewrite store entirely (bge->latch)
        *(volatile f32 *)&o[0xC / 4] = na;
        __asm__ volatile ("" ::: "memory");
    } while (cnt-- != 0);
    }
}
