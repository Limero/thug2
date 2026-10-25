// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BFDD8-0x800C0238 (1120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

/* ---- TRUE layout of the receiver. File-local on purpose: the shared
   Unk_B96D32C4 majority-votes 0x120/0x1330/0x1338/0x133C/0x1340 to s32 and
   0x2F0 to f32, which is wrong for every slot this function touches. ---- */
typedef struct {
    char pad0x0[0xC];
    char *unk0xC;
    char pad0x10[0x10];
    __ps_t q20[1];
    __ps_t q28[1];
    char pad0x30[0x30];
    s32 unk0x60;
    char pad0x64[0xC];
    __ps_t q70[1];
    __ps_t q78[1];
    __ps_t q80[1];
    __ps_t q88[1];
    __ps_t q90[1];
    __ps_t q98[1];
    __ps_t qA0[1];
    __ps_t qA8[1];
    __ps_t qB0[1];
    __ps_t qB8[1];
    __ps_t qC0[1];
    char pad0xC8[0x58];
    s32 unk0x120;
    char pad0x124[0x4];
    s32 unk0x128;
    char pad0x12C[0x8];
    f32 unk0x134;
    f32 unk0x138;
    f32 unk0x13C;
    f32 unk0x140;
    f32 unk0x144;
    f32 unk0x148;
    f32 unk0x14C;
    f32 unk0x150;
    f32 unk0x154;
    f32 unk0x158;
    char pad0x15C[0x50];
    s32 unk0x1AC;
    char pad0x1B0[0x140];
    char *unk0x2F0;
    char pad0x2F4[0x38];
    s32 unk0x32C;
    char pad0x330[0xFFC];
    f32 unk0x132C;
    f32 unk0x1330;
    char pad0x1334[0x4];
    f32 unk0x1338;
    f32 unk0x133C;
    f32 unk0x1340;
    char pad0x1344[0x10];
    s32 unk0x1354;
} Sim;

/* ---- TRUE layout of the object reached through Sim::unk0xC ---- */
typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x48];
    __ps_t p58[1];
    __ps_t p60[1];
    char pad0x68[0x8];
    __ps_t p70[1];
    __ps_t p78[1];
    __ps_t p80[1];
    __ps_t p88[1];
    __ps_t p90[1];
    __ps_t p98[1];
    __ps_t pA0[1];
    __ps_t pA8[1];
    __ps_t pB0[1];
    __ps_t pB8[1];
    __ps_t pC0[1];
    char pad0xC8[0x8];
    __ps_t pD0[1];
    __ps_t pD8[1];
    __ps_t pE0[1];
    __ps_t pE8[1];
    __ps_t pF0[1];
    __ps_t pF8[1];
    __ps_t p100[1];
    __ps_t p108[1];
} Comp;

extern f32 lbl_80298FB0;
extern f32 lbl_80298FB8;
extern f32 lbl_80298FBC;

f32 fn_800144C8(void);
f32 fn_80270FAC(f32);
void fn_800C1E60(Sim *);
void fn_800C2284(Sim *);
void fn_800C333C(Sim *);
void fn_800C37DC(Sim *);
void fn_800C3A24(Sim *);
void fn_800C3C00(Sim *);
void fn_800C4E78(Sim *);
void fn_800C70A4(Sim *);
void fn_800C7234(Sim *);
void fn_800C74E8(Sim *);
void fn_800C750C(Sim *);
void fn_800C7E68(Sim *);
void fn_800C7E6C(Sim *);
void fn_800C8390(Sim *);

void fn_800BFDD8(Sim *arg0) {
    Comp *o;
    Comp *o1;
    Comp *o2;
    Comp *o3;
    Comp *o4;
    f32 *pa;
    f32 *pb;
    f32 dt;
    f32 z;
    f32 zu;
    f32 c;
    s32 n;
    s32 w;
    s32 i;
    register s32 v __asm__("r11");
    s32 off;
    s32 cond;

    arg0->unk0x128 = 0;
    if (arg0->unk0x1354 == 0) {
        fn_800C7234(arg0);
    } else {
        fn_800C74E8(arg0);
    }
    if (arg0->unk0x60 == 0) {
        o = (Comp *) arg0->unk0xC;
        o->pD0[0] = o->p78[0];
        o->pD8[0] = o->p80[0];
        o->pE0[0] = o->p88[0];
        o->pE8[0] = o->p90[0];
        o->pF0[0] = o->p98[0];
        o->pF8[0] = o->pA0[0];
        o->p100[0] = o->pA8[0];
        o->p108[0] = o->pB0[0];
        fn_800C37DC(arg0);
        if (arg0->unk0x32C != 0) {
            v = arg0->unk0x1AC;
            if (0 != v--) {
                zu = lbl_80298FB0;
                off = v * 0x1E0;
                do {
                    *(f32 *) ((char *) (off + (s32) arg0->unk0x2F0) + 8) = zu;
                    off -= 0x1E0;
                } while (0 != v--);
            }
        }
        fn_800C2284(arg0);
        fn_800C750C(arg0);
        fn_800C7E68(arg0);
        fn_800C7E6C(arg0);
    } else {
        dt = fn_800144C8();
        cond = arg0->unk0x134 > 0.0f;
        if (cond != 0) {
            arg0->unk0x134 = arg0->unk0x134 - dt;
        }
        if (arg0->unk0x1330 != 0.0f) {
            arg0->unk0x1330 = arg0->unk0x1330 - dt;
            if (arg0->unk0x1330 <= 0.0f || (u32) arg0->unk0x120 > 1U) {
                arg0->unk0x1330 = 0.0f;
                arg0->unk0x132C = 1.0f;
            }
        }
        if (dt >= lbl_80298FB8) {
            w = (s32) fn_80270FAC(dt / lbl_80298FBC);
            if (w > 6) {
                w = 6;
            }
            arg0->unk0x158 = dt / (f32) (f64) w;
            n = w;
        } else {
            arg0->unk0x158 = dt;
            n = 1;
        }
        i = n;
        if (0 != i--) {
            z = 0.0f;
            pa = (f32 *) ((char *) arg0 + 0x138);
            c = 1.0f;
            pb = (f32 *) ((char *) arg0 + 0x148);
            do {
                fn_800C1E60(arg0);
                arg0->unk0x138 = z;
                pa[1] = z;
                pa[2] = z;
                pa[3] = c;
                arg0->unk0x148 = z;
                pb[1] = z;
                pb[2] = z;
                pb[3] = c;
                v = arg0->unk0x1AC;
                if (0 != v--) {
                    zu = lbl_80298FB0;
                    off = v * 0x1E0;
                    do {
                        *(f32 *) ((char *) (off + (s32) arg0->unk0x2F0) + 0xA4) = zu;
                        off -= 0x1E0;
                    } while (0 != v--);
                }
                if (arg0->unk0x1354 == 0) {
                    fn_800C4E78(arg0);
                    v = (arg0->unk0x128 != 0) ||
                        ((*(s32 *) ((char *) arg0->unk0xC + 0xC) & 1) != 0);
                    if (v != 0) {
                        return;
                    }
                }
                fn_800C333C(arg0);
                v = (arg0->unk0x128 != 0) ||
                    ((*(s32 *) ((char *) arg0->unk0xC + 0xC) & 1) != 0);
                if (v != 0) {
                    return;
                }
                fn_800C37DC(arg0);
                fn_800C3A24(arg0);
                fn_800C3C00(arg0);
                if (arg0->unk0x120 != 0) {
                    arg0->unk0x1338 = z;
                } else {
                    arg0->unk0x1338 = arg0->unk0x1338 + arg0->unk0x158;
                }
                if (arg0->unk0x120 != 0) {
                    arg0->unk0x133C = z;
                } else if (arg0->unk0x1340 > z) {
                    arg0->unk0x133C = z;
                } else {
                    arg0->unk0x133C = arg0->unk0x133C + arg0->unk0x158;
                }
            } while (0 != i--);
        }
        if (arg0->unk0x1354 == 0) {
            fn_800C8390(arg0);
            o1 = (Comp *) arg0->unk0xC;
            o1->p58[0] = arg0->q20[0];
            o1->p60[0] = arg0->q28[0];
            o2 = (Comp *) arg0->unk0xC;
            o2->pB8[0] = arg0->qB0[0];
            o2->pC0[0] = arg0->qB8[0];
            o3 = (Comp *) arg0->unk0xC;
            o3->p78[0] = arg0->q70[0];
            o3->p80[0] = arg0->q78[0];
            o3->p88[0] = arg0->q80[0];
            o3->p90[0] = arg0->q88[0];
            o3->p98[0] = arg0->q90[0];
            o3->pA0[0] = arg0->q98[0];
            o3->pA8[0] = arg0->qA0[0];
            o3->pB0[0] = arg0->qA8[0];
            o4 = (Comp *) arg0->unk0xC;
            o4->pD0[0] = o4->p78[0];
            o4->pD8[0] = o4->p80[0];
            o4->pE0[0] = o4->p88[0];
            o4->pE8[0] = o4->p90[0];
            o4->pF0[0] = o4->p98[0];
            o4->pF8[0] = o4->pA0[0];
            o4->p100[0] = o4->pA8[0];
            o4->p108[0] = o4->pB0[0];
            fn_800C70A4(arg0);
            fn_800C750C(arg0);
            fn_800C7E68(arg0);
            fn_800C7E6C(arg0);
        }
    }
}
