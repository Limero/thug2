// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AEA14-0x800AEBCC (440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
extern f32 lbl_8029864C;
extern f32 lbl_80298650;
extern f32 lbl_80298654;
#include "qb_constants.h"

typedef struct {
    char _p0[0x10];
    s16 vtoff;
    s32 vtfp;
    char _p1[0x28];
    s32 flags;
} Vtbl_t;

typedef struct {
    char _p0[0x30];
    s32 unk0x30;
    char _p1[0x14];
    s32 unk0x48;
} Node_t;

typedef struct {
    char _p0[0x18];
    Vtbl_t *unk0x18;
    char _p1[0x1F4];
    Node_t *unk0x210;
    char _p2[0x28];
    s32 unk0x23C;
} Model_t;

typedef struct {
    char _p0[0x58];
    __ps_t pair0x58;
    __ps_t pair0x60;
    char _p1[0x18];
    char _blk0xD0[0x50];
} Ent_t;

void *GetChecksum_3(s32, s32);
s32 fn_800B6570(s32);
s32 fn_8009F498(s32);
s32 fn_80060DE4(s32);
s32 fn_8005B5FC(s32, f32, f32);
s32 fn_800B48AC(s32);
s32 fn_800C9780(s32);
s32 fn_8005FD68(s32, void *, s32, s32);
void *fn_800B7D4C(void *, void *);

void *fn_800AEA14(s32 unused0, void *arg1) {
    volatile __ps_t spbuf[8];
    __ps_t *sp;
    __ps_t *src;
    Node_t *node;
    char *r29;
    Model_t *m;
    Model_t *cs;
    Ent_t *e;
    s32 skel;
    s32 ctr;
    s32 flag;

    e = (Ent_t *)arg1;
    m = (Model_t *)GetChecksum_3((s32)arg1, QB_MODEL);
    if (m != NULL) {
        if (((Node_t *)m->unk0x210)->unk0x48 & QB_UNKNOWN_0x20000000) {
            return (void *)m->unk0x210;
        }
        if (m->unk0x23C != 0) {
            r29 = (char *)fn_8009F498(fn_800B6570((s32)m));
            m = (Model_t *)GetChecksum_3((s32)r29, QB_MODEL);
            node = m->unk0x210;
            fn_8005B5FC(fn_80060DE4((s32)node), lbl_8029864C, lbl_80298650);
            fn_800B48AC((s32)m);
            skel = (s32)GetChecksum_3((s32)arg1, QB_SKELETON);
            sp = (__ps_t *)spbuf;
            src = (__ps_t *)((char *)e + 0xD0);
            {
                register s32 spb __asm__("r27");
                spb = (s32)sp;
                ctr = 4;
                do {
                } while (--ctr != 0);
                flag = 1;
                __asm__("xori %0,%0,1" : "+r"(flag));
                sp[0] = src[0];
                sp[1] = src[1];
                sp[2] = src[2];
                sp[3] = src[3];
                sp[4] = src[4];
                sp[5] = src[5];
                sp[6] = src[6];
                sp[7] = src[7];
                spbuf[6] = e->pair0x58;
                spbuf[7] = e->pair0x60;
                fn_8005FD68((s32)node, (void *)spb, flag, fn_800C9780(skel));
            }
            ((Ent_t *)r29)->pair0x58 = e->pair0x58;
            ((Ent_t *)r29)->pair0x60 = e->pair0x60;
        } else {
            if (fn_80060DE4((s32)m->unk0x210) != 0) {
                fn_8005B5FC(fn_80060DE4((s32)m->unk0x210), lbl_80298654, lbl_80298650);
                fn_800B48AC((s32)m);
            }
            ((s32 (*)(void *))m->unk0x18->vtfp)((char *)m + m->unk0x18->vtoff);
        }
    }
    cs = (Model_t *)GetChecksum_3((s32)arg1, QB_CUTSCENEUPDATE);
    if (cs != NULL) {
        cs = (Model_t *)fn_800B7D4C((void *)cs, (void *)((char *)arg1 + 0xD0));
    }
    return (void *)cs;
}
