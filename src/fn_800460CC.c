// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800460CC-0x8004631C (592B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

extern const f32 lbl_80292804;
extern char lbl_80292808[];
extern char lbl_8029280C[];

s32 fn_80060F44(s32, s32);
s32 GetChecksum_3(void *, s32);
void *fn_8005F258(void *);
f32 fn_80045870(f32, f32, f32, f32, f32);

typedef struct {
    f32 vmin[4];
    f32 vmax[4];
    f32 bm[4];
    f32 bx[4];
    f32 mn[4];
    f32 mx[4];
} Frame_t;

typedef struct {
    s32  unk0x000;
    char pad0x004[0x174];
    f32  unk0x178;
    f32  unk0x17C;
    char pad0x180[0x330];
    s32  unk0x4B0;
    f32  unk0x4B4;
    char pad0x4B8[0xA0];
    f32  unk0x558;
    f32  unk0x55C;
    f32  unk0x560;
    f32  unk0x564;
    f32  unk0x568;
} Obj_t;

void fn_800460CC(Obj_t *arg0) {
    Frame_t fr;
    register f32 *pvmin __asm__("r29");
    f32 *pbm;
    f32 *pbx;
    f32 *pv;
    f32 one;
    register f32 nx __asm__("fr10");
    register f32 ny __asm__("fr9");
    register f32 nz __asm__("fr11");
    f32 dx;
    f32 dy;
    f32 dz;
    f32 half;
    f32 res;
    f32 zero;
    f32 a0;
    f32 a1;
    f32 a2;
    f32 b0;
    f32 b1;
    f32 b2;
    s32 i;
    char *node;
    __ps_t *p;

    pvmin = fr.vmin;
    i = 0;
    while (i < arg0->unk0x4B0) {
        node = (char *)arg0 + 0x1A0 + i * 0x20;
        pbm = fr.bm;
        pbx = fr.bx;
        one = lbl_80292804;
        if (*(s32 *)(node - 0x10) != 0) {
            p = (__ps_t *)fn_8005F258(fn_80060F44(*(s32 *)((char *)GetChecksum_3(*(s32 *)(node - 0x10), QB_MODEL) + 0x210), 0));
            nx = *(f32 *)node;
            ny = *(f32 *)(node + 4);
            nz = *(f32 *)(node + 8);
            *(__ps_t *)pbm = p[0];
            *(__ps_t *)(pbm + 2) = p[1];
            *(__ps_t *)pbx = p[2];
            *(__ps_t *)(pbx + 2) = p[3];
            a0 = nx + pbm[0];
            b0 = nx + pbx[0];
            a1 = ny + pbm[1];
            a2 = nz + pbm[2];
            fr.mn[0] = a0;
            fr.mn[1] = a1;
            fr.mn[2] = a2;
            fr.mn[3] = one;
            b1 = ny + pbx[1];
            b2 = nz + pbx[2];
            fr.mx[0] = b0;
            fr.mx[1] = b1;
            fr.mx[2] = b2;
            fr.mx[3] = one;
            if (i == 0) {
                *(__ps_t *)((char *)fr.vmin + 0) = *(__ps_t *)((char *)fr.mn + 0);
                *(__ps_t *)((char *)pvmin + 8) = *(__ps_t *)((char *)fr.mn + 8);
                *(__ps_t *)&fr.vmax[0] = *(__ps_t *)&fr.mx[0];
                *(__ps_t *)&fr.vmax[2] = *(__ps_t *)&fr.mx[2];
            } else {
                if (a0 < fr.vmin[0]) {
                    fr.vmin[0] = a0;
                }
                if (a1 < fr.vmin[1]) {
                    fr.vmin[1] = a1;
                }
                if (a2 < pvmin[2]) {
                    pvmin[2] = a2;
                }
                if (fr.mx[0] > fr.vmax[0]) {
                    fr.vmax[0] = fr.mx[0];
                }
                if (fr.mx[1] > fr.vmax[1]) {
                    fr.vmax[1] = fr.mx[1];
                }
                if (fr.mx[2] > fr.vmax[2]) {
                    fr.vmax[2] = fr.mx[2];
                }
            }
        }
        i = i + 1;
    }
    dx = fr.vmax[0] - fr.vmin[0];
    dz = fr.vmax[2] - pvmin[2];
    dy = fr.vmax[1] - fr.vmin[1];
    res = fn_80045870(arg0->unk0x178, arg0->unk0x17C, arg0->unk0x4B4, ((dx > dz) ? dx : dz), dy);
    zero = *(f32 *)lbl_8029280C;
    half = *(f32 *)lbl_80292808;
    pv = (f32 *)((char *)arg0 + 0x558);
    arg0->unk0x558 = -(fr.vmax[0] + fr.vmin[0]) * half;
    arg0->unk0x568 = res;
    pv[3] = zero;
    pv[1] = -(fr.vmax[1] + fr.vmin[1]) * half;
    pv[2] = -(fr.vmax[2] + pvmin[2]) * half;
}
