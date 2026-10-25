// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80244BC4-0x80244E24 (608B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_80238964(void);
extern void *fn_802380EC(s32 map, s32 x, s32 y);
extern s32 fn_802432A0(Unk_9994C3F5 * item);
extern void *fn_802416F8(void);
extern s32 fn_80241700(Unk_C7387A53 * obj);
extern s32 fn_802417A8(u8 * a, u8 * b);
extern s32 fn_80244A20(Unk_C7387A53 * a, Unk_4A174A22 * b, s32 c);
extern void fn_80244924(Unk_5AA7B5D7 * a);
extern s32 fn_80238970(void);
extern void fn_80238784(void *out, u8 * mgr, f32 * area, void *outsz);
extern s32 fn_801FC0E0(void);
extern s32 fn_801FAA9C(f32 x, f32 y, f32 x2, f32 y2);

struct bc4_fr {
    f32 pos[2];
    f32 pos2[2];
    f32 sz_w;
    f32 pad1C;
    f32 sz_h;
    f32 pad24;
    f32 rc[4];
};

bool fn_80244BC4(Unk_BE1656AE *arg0, Unk_ECD1B899 *arg1) {
    struct bc4_fr fr;
    s32 min = 0;
    s32 si;
    s32 sj;
    s32 ai;
    s32 aj;
    Unk_C7387A53 *item;
    Unk_C7387A53 *item2;
    Unk_1D62F22E *sobj;
    Unk_C7387A53 *obj;
    s32 map;
    s32 hash;
    s32 val;
    __ps_t *dst;
    u16 half;
    s32 first;

    first = ((Unk_8C3FE072_4 *)arg1)->unk0x0;
    half = ((Unk_8C3FE072_4 *)arg1)->unk0x4;
    *(s32 *)((char *)arg0 + 1) = first;
    *(u16 *)((char *)arg0 + 5) = half;
    map = fn_80238964();
    for (si = *(u8 *)arg1; si < *(u8 *)arg1 + arg1->unk0x3; si++) {
        for (sj = arg1->unk0x2; sj < arg1->unk0x2 + arg1->unk0x5; sj++) {
            if ((item = (void *)fn_802380EC(map, si, sj)) != NULL) {
                do {
                    fn_802432A0(item);
                    sobj = fn_802416F8();
                    hash = sobj->unk0x34;
                    val = *((s8 *)&sobj->unk0x1);
                    if (hash != QB_RISER_BELOW) {
                        if (hash == QB_RISER_FLOOR) {
                            val += 1;
                        }
                    } else {
                        val += 0xF;
                    }
                    if (val < min) {
                        min = val;
                    }
                    item = *((void * *)&item->unk0xC);
                } while (item != NULL);
            }
        }
    }
    min = -min;
    for (ai = *(u8 *)arg1; ai < *(u8 *)arg1 + arg1->unk0x3; ai++) {
        for (aj = arg1->unk0x2; aj < arg1->unk0x2 + arg1->unk0x5; aj++) {
            item2 = (void *)fn_802380EC(map, ai, aj);
            if (item2 != NULL) {
                do {
                    fn_802432A0(item2);
                    obj = fn_802416F8();
                    if ((fn_80241700(obj) == 0) && (fn_802417A8(obj, arg1) != 0) &&
                        (obj->unk0x34 != QB_RISER_BELOW) &&
                        (fn_80244A20(arg0, obj, min) == 0)) {
                        fn_80244924(arg0);
                        return false;
                    }
                    item2 = *((void * *)&item2->unk0xC);
                } while (item2 != NULL);
            }
        }
    }
    dst = (__ps_t *)&fr.pos[0];
    fn_80238784(&fr.rc[0], fn_80238970(), arg1, &fr.sz_w);
    dst[0] = *(__ps_t *)&fr.rc[0];
    dst[1] = *(__ps_t *)&fr.rc[2];
    fn_801FC0E0();
    arg0->unk0x10 = fn_801FAA9C(fr.pos[0], ((f32 *)dst)[2], fr.pos[0] + fr.sz_w, ((f32 *)dst)[2] + fr.sz_h);
    return true;
}
