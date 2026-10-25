// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D008-0x8016D1A8 (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

s32 Script_GetInteger(s32, s32);
void *fn_800A398C(void *, s32);
s32 fn_80128D70(void *, char *, f32 *, s32);

extern char lbl_802A8B20[];
extern f32 lbl_802A8B30;
extern f32 lbl_802A8B34;
extern f32 lbl_802A8B38;
extern f32 lbl_802A8B3C;
extern void *lbl_80301A38;

typedef struct {
    f32 m[16];
    f32 p[4];
} Loc;

bool fn_8016D008(void *arg0, void *arg1) {
    Loc s;
    f32 c0;
    f32 c1;
    f32 *pp;
    f32 *mp;
    void *obj;
    s32 ctr;

    if (Script_GetInteger(QB_RESETCAMERATOVIEWEROBJECT, 0) != 0) {
        obj = fn_800A398C(lbl_80301A38, QB_VIEWER_CAM);
        if (obj != 0) {
            ctr = 4;
            do {
                ctr -= 1;
            } while (ctr != 0);
            mp = s.m;
            pp = s.p;
            c0 = lbl_802A8B30;
            c1 = lbl_802A8B34;
            s.m[1] = c1;
            s.m[0] = c0;
            mp[2] = c1;
            s.m[4] = c1;
            s.m[5] = c0;
            s.m[6] = c1;
            s.m[7] = c1;
            s.m[8] = c1;
            s.m[9] = c1;
            s.m[10] = c0;
            s.m[11] = c1;
            s.m[12] = c1;
            s.m[13] = c1;
            s.m[14] = c1;
            s.m[15] = c0;
            s.m[3] = c1;

            *(__ps_t *)((char *)obj + 0x78) = *(__ps_t *)&s.m[0];
            *(__ps_t *)((char *)obj + 0x80) = *(__ps_t *)&mp[2];
            *(__ps_t *)((char *)obj + 0x88) = *(__ps_t *)&s.m[4];
            *(__ps_t *)((char *)obj + 0x90) = *(__ps_t *)&s.m[6];
            *(__ps_t *)((char *)obj + 0x98) = *(__ps_t *)&s.m[8];
            *(__ps_t *)((char *)obj + 0xa0) = *(__ps_t *)&s.m[10];
            *(__ps_t *)((char *)obj + 0xa8) = *(__ps_t *)&s.m[12];
            *(__ps_t *)((char *)obj + 0xb0) = *(__ps_t *)&s.m[14];

            if (fn_80128D70(arg1, lbl_802A8B20, pp, 0) != 0) {
                s.p[0] += c1;
                s.p[1] += lbl_802A8B38;
                s.p[2] += lbl_802A8B3C;
                pp[3] = c0;
            } else {
                pp[0] = c1;
                pp[1] = lbl_802A8B38;
                pp[2] = lbl_802A8B3C;
                pp[3] = c0;
            }
            *(__ps_t *)((char *)obj + 0x58) = *(__ps_t *)&s.p[0];
            *(__ps_t *)((char *)obj + 0x60) = *(__ps_t *)&s.p[2];
        }
    }
    return true;
}
