// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023FC44-0x802401C4 (1408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    s32 v00;
    s32 v04;
    s32 v08;
    s32 v0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    s32 v30;
    s32 v34;
    s32 v38;
    s32 v3C;
    s32 v40;
    s32 v44;
    s32 pad[9];
} MStats;

extern MStats lbl_80306018;
extern bool lbl_80306024;
extern char lbl_80306048[];
extern Unk_C8FEE62D *lbl_80306084;
extern Unk_C8FEE62D *lbl_80306088;
extern s32 lbl_80306090;
extern bool lbl_80306094;
typedef struct {
    char pad0x0[0x34];
    Unk_C8FEE62D *v34;
} Sub118;

typedef struct {
    char pad0x0[0x118];
    Sub118 *p118;
    Unk_C7387A53 *p11C;
} MMgr;

extern MMgr *lbl_802FFE98;

extern char lbl_802B0F94[];
extern char lbl_802B0FA4[];
extern char lbl_802B0FB4[];
extern char lbl_802B0FC4[];
extern char lbl_802B0FD0[];
extern char lbl_802B0FE0[];
extern char lbl_802B0FF0[];
extern char lbl_802B1004[];
extern char lbl_802B1018[];
extern char lbl_802B1028[];
extern char lbl_802B1038[];

extern s32 MemAvailable(Unk_C8FEE62D *);
extern s32 fn_800113E4(Unk_C7387A53 *);
extern s32 fn_8023FB5C(s32, s32);
extern void fn_8022EDDC(Unk_9994C3F5 *, Unk_DB0E2BAB *);
extern Unk_C8FEE62D **fn_80238964(void);
extern Unk_C8FEE62D **fn_80238970(void);
extern s32 fn_80235CB4(s32);
extern s32 fn_80240A4C(void);
extern s32 fn_80240A6C(void);
extern s32 fn_80240A8C(void);
extern s32 fn_80240AAC(void);
extern s32 fn_80240ACC(void);
extern s32 fn_80240AEC(void);

MStats *fn_8023FC44(MStats *arg0) {
    volatile double _dummy;
    Unk_C7387A53 *p;
    s32 lim;
    register s32 a __asm__("r30");
    s32 v4;
    s32 v4b;
    s32 b;

    if (lbl_80306094 != 0) {
        lbl_80306094 = 0;
        fn_8022EDDC(*fn_80238970(), (Unk_DB0E2BAB *)lbl_80306048);
    }
    p = lbl_802FFE98->p11C;
    a = p->unk0x34;
    lim = fn_8023FB5C((s32)lbl_802B0F94, -1);
    lim += ((*fn_80238964())->unk0x20 - 1) * 0x94D00;
    lbl_80306018.v08 = p->unk0x2C + MemAvailable(a);
    lbl_80306018.v08 -= fn_8023FB5C((s32)lbl_802B0FA4, -1);
    lbl_80306018.v08 -= lim;
    v4 = fn_8023FB5C((s32)lbl_802B0FB4, -1);
    lbl_80306018.v00 = lbl_80306088->unk0x20;
    v4b = lbl_80306088->unk0x2C + MemAvailable(lbl_80306084);
    lbl_80306018.v04 = v4b - v4;
    if (fn_800113E4(p) < lbl_80306018.v08 && fn_800113E4(p) < lim && lbl_80306018.v08 >= lim) {
        lbl_80306018.v08 = fn_800113E4(p);
        lbl_80306018.v0C = 1;
    } else {
        lbl_80306024 = 0;
    }
    lbl_80306018.v08 -= fn_8023FB5C((s32)lbl_802B0FC4, fn_80235CB4((s32)fn_80238964()));
    if (lbl_80306018.v08 > 0) {
        lbl_80306018.f10 = 1.0f - (float)(double)lbl_80306018.v08 / (float)(double)fn_8023FB5C((s32)lbl_802B0FD0, -1);
    } else {
        lbl_80306018.f10 = 1.0f;
    }
    lbl_80306018.f2C = lbl_80306018.f10;
    lbl_80306018.f18 = 1.0f - (float)(double)lbl_80306018.v04 / (float)(double)fn_8023FB5C((s32)lbl_802B0FE0, -1);
    if (lbl_80306018.f18 > lbl_80306018.f2C) {
        lbl_80306018.f2C = lbl_80306018.f18;
    }
    lbl_80306018.f14 = 2.0f - (float)(double)MemAvailable(lbl_802FFE98->p118->v34) / (float)(double)fn_8023FB5C((s32)lbl_802B0FF0, -1);
    if (lbl_80306018.f14 > lbl_80306018.f2C) {
        lbl_80306018.f2C = lbl_80306018.f14;
    } else {
        lbl_80306018.f14 = 0.0f;
    }
    a = fn_80240A4C();
    b = fn_80240A6C();
    lbl_80306018.f1C = (float)(double)lbl_80306018.v3C / (float)(double)((a - b) - fn_8023FB5C((s32)lbl_802B1004, -1));
    if (lbl_80306018.f2C < lbl_80306018.f1C) {
        lbl_80306018.f2C = lbl_80306018.f1C;
    }
    a = fn_80240A8C();
    b = fn_80240AAC();
    lbl_80306018.f20 = (float)(double)lbl_80306018.v40 / (float)(double)((a - b) - fn_8023FB5C((s32)lbl_802B1018, -1));
    if (lbl_80306018.f2C < lbl_80306018.f20) {
        lbl_80306018.f2C = lbl_80306018.f20;
    }
    a = fn_80240ACC();
    b = fn_80240AEC();
    lbl_80306018.f24 = (float)(double)lbl_80306018.v44 / (float)(double)((a - b) - fn_8023FB5C((s32)lbl_802B1028, -1));
    if (lbl_80306018.f2C < lbl_80306018.f24) {
        lbl_80306018.f2C = lbl_80306018.f24;
    }
    a = lbl_80306090;
    lbl_80306018.f28 = (float)(double)a / (float)(double)fn_8023FB5C((s32)lbl_802B1038, -1);
    if (lbl_80306018.f28 > lbl_80306018.f2C) {
        lbl_80306018.f2C = lbl_80306018.f28;
    }
    *arg0 = lbl_80306018;
    return arg0;
}
