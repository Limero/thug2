// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D1458-0x801D16C0 (616B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

s32 Tmr_GetTime(void);
void fn_8020C54C(void *, s32);
void fn_800AA068(void *);
void fn_801F1340(void *, s32);

extern f32 lbl_802AD3E4;
extern f32 lbl_802AD3E8;
extern s32 lbl_80303150;

typedef struct {
    char pad0x58[0x58];
    __ps_t f58;
    __ps_t f60;
    __ps_t f68;
    __ps_t f70;
} Vec7;

typedef struct {
    char pad0[4];
    s32 unk4;
    s32 unk8;
} Sub;

typedef struct {
    char pad0x00[0x1C];
    s32 unk0x1C;
    char pad0x20[0x58];
    Sub unk78;
    char pad0x84[0x90];
    Sub unk114;
    Sub unk120;
    Sub unk12C;
    Sub unk138;
} SubBC;

typedef struct {
    char pad0x00[0x13F0];
    f32 unk0x13F0;
} SubAC;

typedef struct {
    char pad0x00[0x1C];
    s32 unk0x1C;
    char pad0x20[4];
    s32 unk0x24;
} SubA8;

typedef struct {
    char pad0x00[0x0C];
    Vec7 *unk0x0C;
    char pad0x10[0x88];
    s32 unk0x98;
    s32 unk0x9C;
    char pad0xA0[0x1F8];
    __ps_t f298;
    __ps_t f2A0;
    char pad0x2A8[0xC4];
    f32 unk0x36C;
    char pad0x370[0x88];
    s32 unk0x3F8;
    s32 unk0x3FC;
    char pad0x400[0x11A0];
    char *unk0x15A0;
    char pad0x15A4[4];
    SubA8 *unk0x15A8;
    SubAC *unk0x15AC;
    char pad0x15B0[0xC];
    SubBC *unk0x15BC;
} Arg0;

void fn_801D1458(Arg0 *arg0, s32 arg1) {
    Sub *sub;
    Vec7 *v, *w;
    s32 st;
    f32 t;

    if (arg0->unk0x15BC->unk0x1C != arg1) {
        arg0->unk0x98 = lbl_80303150 + Tmr_GetTime();
        arg0->unk0x9C = arg0->unk0x15BC->unk0x1C;
    }
    if (arg0->unk0x15BC->unk0x1C == 3) {
        if (arg1 != 3) {
            if (!(*(f32 *)&arg0->f298 == lbl_802AD3E4 &&
                  *((f32 *)&arg0->f298 + 1) == lbl_802AD3E4 &&
                  *(f32 *)&arg0->f2A0 == lbl_802AD3E4)) {
                v = arg0->unk0x0C;
                v->f58 = arg0->f298;
                v->f60 = arg0->f2A0;
                w = arg0->unk0x0C;
                w->f68 = w->f58;
                w->f70 = w->f60;
            }
        }
    }
    if (arg1 != 3) {
        f32 *p = (f32 *)&arg0->f298;
        f32 k = lbl_802AD3E4;
        f32 j = lbl_802AD3E8;
        p[0] = k;
        p[1] = k;
        p[2] = k;
        p[3] = j;
    }
    if (arg1 != 0) {
        fn_8020C54C(arg0->unk0x15AC, 1);
    }
    if (arg0->unk0x15BC->unk0x1C == 4 && arg1 != 4) {
        s32 z = 0;
        sub = (Sub *)((char *)arg0->unk0x15BC + 0x78);
        if (sub->unk4 != 0) {
            sub->unk4 = z;
            sub->unk8 = lbl_80303150 + Tmr_GetTime();
        }
        arg0->unk0x15A8->unk0x24 = z;
    }
    st = arg0->unk0x15BC->unk0x1C;
    if (st == 1) {
        if (arg1 != 1) {
            s32 y = 0;
            arg0->unk0x3FC = lbl_80303150 + Tmr_GetTime();
            {
                Sub *s2 = (Sub *)((char *)arg0->unk0x15BC + 0x114);
                if (s2->unk4 != 0) {
                    s2->unk4 = y;
                    s2->unk8 = lbl_80303150 + Tmr_GetTime();
                }
            }
            sub = (Sub *)((char *)arg0->unk0x15BC + 0x12C);
            if (sub->unk4 != 0) {
                sub->unk4 = y;
                sub->unk8 = lbl_80303150 + Tmr_GetTime();
            }
            sub = (Sub *)((char *)arg0->unk0x15BC + 0x138);
            if (sub->unk4 != 0) {
                sub->unk4 = y;
                sub->unk8 = lbl_80303150 + Tmr_GetTime();
            }
        }
    } else if (arg1 == 1) {
        if (st != 2) {
            arg0->unk0x3F8 = lbl_80303150 + Tmr_GetTime();
        }
        t = lbl_802AD3E4;
        arg0->unk0x15AC->unk0x13F0 = t;
        fn_800AA068(arg0->unk0x15A0 + 0xB8);
        fn_800AA068(arg0->unk0x15A0 + 0x124);
        arg0->unk0x36C = t;
    }
    fn_801F1340(arg0->unk0x15BC, arg1);
    arg0->unk0x15A8->unk0x1C = arg1;
}
