// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176FA8-0x801770D4 (300B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802A8E58;
extern f32 lbl_802A8E5C;
extern char lbl_80301A38[];
extern char lbl_80305EAC[];

typedef struct Node76A {
    char pad0x0[0xC];
    void *base;
    s32 unk0x10;
    struct Node76A *next;
    void *vobj;
} Node76A;

typedef struct {
    char pad0x0[0x70];
    s16 thisOff;
    s16 pad0x72;
    s32 (*fn)(void *);
} VTab76A;

typedef struct {
    char pad0x0[0x28];
    void *unk0x28;
    char pad0x2C[0x3F8];
    s32 unk0x424;
} Guard76A;

void fn_801AE118(void *, void *);
void *fn_800A200C(void *, s32);

void fn_80176FA8(void) {
    __ps_t buf[8];
    __ps_t *dst;
    Node76A *n;
    void *base;
    __ps_t *s;
    f32 fa;
    f32 fb;
    s32 i;

    {
        Guard76A *g = *(Guard76A **)lbl_80305EAC;
        if (g->unk0x424 == 0) {
            return;
        }
        fn_801AE118(g->unk0x28, 0);
    }
    n = fn_800A200C(*(void **)&lbl_80301A38, QB_RAILMANAGER);
    if (n != NULL) {
        fa = lbl_802A8E58;
        dst = buf;
        fb = lbl_802A8E5C;
        do {
            VTab76A *v;
            base = n->base;
            s = (__ps_t *)((char *)base + 0x78);
            for (i = 4; i != 0; i--) {
            }
            dst[0] = s[0];
            dst[1] = s[1];
            dst[2] = s[2];
            dst[3] = s[3];
            dst[4] = s[4];
            dst[5] = s[5];
            dst[6] = s[6];
            dst[7] = s[7];
            ((f32 *)buf)[3] = fa;
            ((f32 *)buf)[7] = fa;
            ((f32 *)buf)[11] = fa;
            buf[6] = ((__ps_t *)((char *)base + 88))[0];
            buf[7] = ((__ps_t *)((char *)base + 88))[1];
            ((f32 *)buf)[15] = fb;
            v = (VTab76A *)n->vobj;
            {
                void *vret = (void *)v->fn((char *)n + v->thisOff);
                if (vret != NULL) {
                    fn_801AE118(vret, dst);
                }
            }
            n = n->next;
        } while (n != NULL);
    }
}
