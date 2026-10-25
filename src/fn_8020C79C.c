// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C79C-0x8020C878 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
// FLAG: (none — the m2c size-optimise flag measured 80.0% here; the default
// path measures 100.0%, so the draft carries no extra_cflags at all)
//
// Notes on the three load-bearing decisions (all verified against the DOL):
//  * the 8-iteration countdown is `while (0 != i--)` seeded with 8, i.e. the
//    loop body is peeled-free and the latch is `cmpwi; addi r,-1; bne`
//    (recipes 10556: `while (n-- != 0)` emits a 4-insn latch with a copy;
//    flipping the comparison's operand order gives retail's 3-insn form);
//  * the float stores are written in ASCENDING source order — ngccc permutes
//    a run of four same-base stores into 1,4,2,3, which is exactly what the
//    want shows (0x90, 0x9c, 0x94, 0x98);
//  * the two float pool reads must be declared `extern const f32`, otherwise
//    the scheduler parks `lfs f13` before the `li r0,0` and the tail swaps.
typedef struct Vec4_s {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Obj_8020C79C_s {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    char pad0x1C[0x74];
    f32 f90;
    char pad0x94[0x754];
    f32 f7E8;
    char pad0x7EC[0x1050];
    s32 v183C;
    s32 v1840;
    s32 v1844;
    s32 v1848;
    s32 v184C;
    s32 v1850;
    s32 v1854;
    s32 v1858;
    char pad0x185C[0x124];
    f32 f1980;
    char pad0x1984[0xB8];
    s32 v1A3C;
} Obj_8020C79C;

extern const f32 lbl_802AF4A0;
extern const f32 lbl_802AF4A4;
extern char lbl_802AF760[];
void fn_8009F53C(Obj_8020C79C *);
void fn_80105BF4(void *);
void fn_8010794C(void *);

void *fn_8020C79C(Obj_8020C79C *arg0) {
    char *p;
    s32 i;
    Vec4 *t9;
    Vec4 *t11;
    f32 f0;
    f32 f13;

    i = 8;
    p = (char *)arg0 + 0xB8;
    fn_8009F53C(arg0);
    arg0->unk0x18 = (s32)lbl_802AF760;
    while (0 != i--) {
        fn_8010794C(p + 0x20);
        p += 0xE0;
    }
    fn_80105BF4((char *)arg0 + 0x858);
    fn_8010794C((char *)arg0 + 0x1880);
    arg0->v183C = 0;
    arg0->unk0x4 = QB_WALK;
    t9 = (Vec4 *)((char *)arg0 + 0x90);
    arg0->v1840 = 0;
    t11 = (Vec4 *)((char *)arg0 + 0x1980);
    arg0->v1844 = 0;
    arg0->v1848 = 0;
    arg0->v184C = 0;
    arg0->v1850 = 0;
    arg0->v1854 = 0;
    arg0->v1858 = 0;
    f0 = lbl_802AF4A0;
    f13 = lbl_802AF4A4;
    arg0->f90 = f0;
    t9->y = f0;
    t9->z = f0;
    t9->w = f13;
    arg0->f1980 = f0;
    t11->y = f0;
    t11->z = f0;
    t11->w = f13;
    arg0->f7E8 = f0;
    arg0->v1A3C = 0;
    return arg0;
}
