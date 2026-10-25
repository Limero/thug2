// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE3D0-0x800DE4BC (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_8002464C(void *, void *);
void fn_80024668(void *, void *);
typedef struct {
    char pad0[0xC];
    __ps_t *c;
    char pad10[0xC];
    void *e;
} Obj_800DE3D0;
void fn_800DE3D0(Obj_800DE3D0 *arg0) {
    __ps_t sp8[10];
    __ps_t *s;
    __ps_t *d2;
    __ps_t *c2;
    s32 ctr;

    sp8[0] = arg0->c[11];
    sp8[1] = arg0->c[12];
    s = arg0->c + 15;
    d2 = &sp8[2];
    ctr = 4;
    do {
    } while (--ctr != 0);
    sp8[2] = s[0];
    sp8[3] = s[1];
    sp8[4] = s[2];
    sp8[5] = s[3];
    sp8[6] = s[4];
    sp8[7] = s[5];
    sp8[8] = s[6];
    sp8[9] = s[7];
    c2 = arg0->c;
    c2[26] = sp8[2];
    c2[27] = sp8[3];
    c2[28] = sp8[4];
    c2[29] = sp8[5];
    c2[30] = sp8[6];
    c2[31] = sp8[7];
    c2[32] = sp8[8];
    c2[33] = sp8[9];
    fn_8002464C(arg0->e, sp8);
    fn_80024668(arg0->e, d2);
}
