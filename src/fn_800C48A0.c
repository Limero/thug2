// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C48A0-0x800C494C (172B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80299108;   /* 0.0f */

void fn_800C48A0(Unk_C7387A53 *obj) {
    s32 *u = (s32 *)obj;
    f32 *f = (f32 *)obj;
    int cnt;
    if (u[0x32C / 4] == 0)
        return;
    cnt = u[0x1AC / 4];
    if (cnt-- == 0)
        return;
    {
    f32 zero = lbl_80299108;
    do {
        char *base;
        f32 dt;
        f32 *o;
        f32 pos;
        f32 vel;
        f32 ang;
        f32 d;
        f32 n;
        f32 t;
        base = *((char * *)&obj->unk0x2F0);
        o = (f32 *)(base + cnt * 480);
        if (o[0xF4 / 4] != zero) {
            pos = o[8 / 4];
            dt = f[0x158 / 4];
            vel = o[0xCC / 4];
            d = fabsf(-pos / (dt * vel));
            ang = o[0xF4 / 4];
            if (ang > d)
                ang = d;
            n = ang;
            if (pos < zero) {
            } else {
                n = -n;
            }
            t = vel * n;
            o[8 / 4] = pos + t * dt;
            o[0xA4 / 4] = o[0xA4 / 4] + t;
        }
        cnt--;
    } while (cnt != -1);
    }
}
