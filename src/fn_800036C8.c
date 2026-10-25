// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800036C8-0x800037F8 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 s;   /* +0x0  sin(angle)   */
    f32 c;   /* +0x4  cos(angle)   */
    f32 ds;  /* +0x8  d sin        */
    f32 dc;  /* +0xC  d cos        */
} sincos_ent;

extern sincos_ent lbl_80310AE0[0x77];

f32 sinf(f32);   /* sinf */
f32 cosf(f32);   /* cosf */

void fn_800036C8(void) {
    sincos_ent *e;
    s32 i;
    f32 angle;

    /* frame-shape pad only, see header: 32B of unused local space */
    volatile f64 pad0;
    volatile f64 pad1;
    volatile f64 pad2;
    volatile f64 pad3;

    /* pass 1: sin/cos of i * (pi/2) / 118 for i = 0..0x76 */
    e = lbl_80310AE0;
    for (i = 0; i <= 0x76; i++) {
        angle = (f32)(f64)(s32)i * 1.5707964f / 118.0f;
        e->s = sinf(angle);
        e->c = cosf(angle);
        e++;
    }

    /* pass 2: forward deltas, entry i - entry i+1 ... (i+1) - (i) */
    for (i = 0; i < 0x76; i++) {
        lbl_80310AE0[i].ds = lbl_80310AE0[i + 1].s - lbl_80310AE0[i].s;
        lbl_80310AE0[i].dc = lbl_80310AE0[i + 1].c - lbl_80310AE0[i].c;
    }

    /* pass 3: last entry wraps around to entry 0 (i == 0x76 here) */
    lbl_80310AE0[i].ds = lbl_80310AE0[0].s - lbl_80310AE0[i].s;
    lbl_80310AE0[i].dc = lbl_80310AE0[0].c - lbl_80310AE0[i].c;
}
