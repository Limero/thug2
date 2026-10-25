// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081110-0x80081238 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct VT81110 {
    char pad_0x128[0x128];
    s16 off_0x128;
    char pad_0x12A[2];
    s32 (*getCount)(void *);
    s16 off_0x130;
    char pad_0x132[2];
    void (*setup)(void *, void *);
    char pad_0x138[0x08];
    s16 off_0x140;
    char pad_0x142[2];
    void (*teardown)(void *, void *);
} VT81110;

typedef struct OBJ81110 {
    char pad_0x14[0x14];
    struct VT81110 *vt;
    char pad_0x18[0x18];
    s32 unk0x30;
    char pad_0x34[4];
    f32 c38;
    f32 c3C;
    f32 c40;
} OBJ81110;

typedef struct VEC81110 {
    f32 x;
    f32 y;
    f32 z;
} VEC81110;

typedef struct ELEM81110 {
    f32 x;
    f32 y;
    f32 z;
    char pad_C[4];
} ELEM81110;

void *Mem_Alloc(s32);
void Mem_Free(void *);

void fn_80081110(OBJ81110 *arg0, VEC81110 *arg1) {
    VT81110 *vt;
    s32 count;
    s32 n;
    void *buf;
    s32 i;
    ELEM81110 *p;
    f32 lo0, lo1, lo2;
    f32 sc0, sc1, sc2;

    if (arg0->unk0x30 == 0) {
        vt = arg0->vt;
        count = vt->getCount((char *)arg0 + vt->off_0x128);
        buf = Mem_Alloc(count * 0x10);
        i = count - 1;
        /* i == -1 is exactly count == 0, but testing i (not count) makes
           ngccc emit the guard as cmpwi/addi/beq instead of cmpwi/beq/addi */
        if (i != -1) {
            while (0 != i--) {
            }
        }
        vt = arg0->vt;
        vt->setup((char *)arg0 + vt->off_0x130, buf);
        if (count > 0) {
            n = count;
            p = (ELEM81110 *)buf;
            lo0 = arg0->c38;
            sc0 = arg1->x;
            lo1 = arg0->c3C;
            sc1 = arg1->y;
            lo2 = arg0->c40;
            sc2 = arg1->z;
            do {
                p->x = (p->x - lo0) * sc0 + lo0;
                p->y = (p->y - lo1) * sc1 + lo1;
                p->z = (p->z - lo2) * sc2 + lo2;
                p = (ELEM81110 *)((char *)p + 0x10);
            } while (--n);
        }
        vt = arg0->vt;
        vt->teardown((char *)arg0 + vt->off_0x140, buf);
        Mem_Free(buf);
    }
    *(__ps_t *)((char *)arg0 + 0x48) = *(__ps_t *)((char *)arg1 + 0);
    *(__ps_t *)((char *)arg0 + 0x50) = *(__ps_t *)((char *)arg1 + 8);
}
