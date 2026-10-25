// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C4734-0x800C47EC (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80299100;   /* 0.0f */

void fn_800C4734(Unk_C7387A53 *obj) {
    s32 *u = (s32 *)obj;
    f32 *f = (f32 *)obj;
    int cnt;
    if (u[0x32C / 4] == 0)
        return;
    cnt = u[0x1AC / 4];
    if (cnt-- == 0)
        return;
    {
    f32 zero = lbl_80299100;
    do {
        char *base;
        f32 dt;
        f32 *o;
        f32 pos;
        f32 vel;
        f32 ang;
        f32 d;
        f32 pos2;
        f32 t;
        base = *((char * *)&obj->unk0x2F0);
        dt = f[0x158 / 4];
        o = (f32 *)(base + cnt * 480);
        pos = o[8 / 4];
        vel = o[0xCC / 4];
        ang = o[0xF8 / 4];
        d = fabsf(-pos / (dt * vel));
        if (ang > d) {
            o[0xF4 / 4] = ang - d;
            ang = d;
        } else {
            o[0xF4 / 4] = zero;
        }
        pos2 = o[8 / 4];
        if (pos2 < zero) {
        } else {
            ang = -ang;
        }
        t = o[0xCC / 4] * ang;
        o[8 / 4] = t * f[0x158 / 4] + pos2;
        o[0xA4 / 4] = o[0xA4 / 4] + t;
        cnt--;
    } while (cnt != -1);
    }
}
