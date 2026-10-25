// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004FF24-0x80050068 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* fn_800422D8 / fn_800422E0 are 8-byte leaf accessors: they return the f32 at
   +0x2C / +0x30 of their argument (the "scale" of a COM). */
typedef struct Com {
    char pad0x0[0x2C];
    f32 scaleX;
    f32 scaleY;
} Com;

float fn_800422D8(Com *);
float fn_800422E0(Com *);
void fn_8003F710(void *, f32 *, f32 *);
void fn_8003F740(void *, void *, void *);

/* the object both `arg1` and `arg0->pCom` point at: its COM sits at +0x88,
   its x/y translation floats at +0x178/+0x17C (fn_8003F710/740 also read
   +0xE8/+0xEC and +0x170/+0x174 of the same object). */
typedef struct Obj {
    char pad0x0[0x88];
    Com com;
    char pad0xBC[0xBC];
    f32 posX;
    f32 posY;
} Obj;

/* the owner: same object type reachable through +0x1AC */
typedef struct Ctl {
    char pad0x0[0x1AC];
    Obj *pCom;
} Ctl;

extern f32 lbl_80292CA8;
extern f32 lbl_80292CAC;

void fn_8004FF24(Ctl *arg0, Obj **arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 v[5];   /* fn_8003F740 writes v[0],v[1] (r1+8, r1+0xC); the want's local
                   area is 0x1C bytes, so the original held them in a 5-float
                   buffer — recipes §6w-104 (stack gap => array buffer) */
    f32 one;
    f32 half;
    f32 posX;
    f32 posY;

    fn_8003F710(*arg1, arg2, arg3);
    *arg2 *= fn_800422D8(&arg0->pCom->com);
    *arg3 *= fn_800422E0(&arg0->pCom->com);
    posX = (*arg1)->posX;
    *arg4 = posX * fn_800422D8(&(*arg1)->com) * fn_800422D8(&arg0->pCom->com);
    posY = (*arg1)->posY;
    *arg5 = posY * fn_800422E0(&(*arg1)->com) * fn_800422E0(&arg0->pCom->com);
    fn_8003F740(*arg1, &v[0], &v[1]);
    one = lbl_80292CA8;
    half = lbl_80292CAC;
    *arg2 -= (v[0] + one) * *arg4 * half;
    *arg3 -= (v[1] + one) * *arg5 * half;
}
