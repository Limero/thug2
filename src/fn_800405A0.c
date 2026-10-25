// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800405A0-0x80040734 (404B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    u8 r, g, b, a;
} Rgba;

typedef struct {
    f32 alpha;
    char pad0x04[0x14];
    f32 pos_x;
    f32 pos_y;
    char pad0x20[0xC];
    f32 scale_x;
    f32 scale_y;
    char pad0x34[0x8];
    f32 angle;
    Rgba rgba;
} SetProps;

typedef struct {
    char pad0x88[0x88];
    SetProps sp;
} Obj;

void fn_8012772C(CStruct *, s32, f32);
void fn_80127A18(CStruct *, s32, f32, f32);
void fn_80127AAC(CStruct *, s32, void *);
void fn_80126A30(void *);
void *fn_80128F94(void);
void fn_80129068(void *, s32, s32);
void fn_80129260(void *, s32, s32);
void fn_80128FB4(void *, s32);
void fn_8003E7CC(s32);
s32 fn_80042110(Obj *);
void AddInteger(CStruct *, s32, s32);
extern f32 lbl_8029232C;
extern f32 lbl_80292330;

void fn_800405A0(Obj *arg0, CStruct *arg1) {
    SetProps *s = &arg0->sp;
    SetProps *t;
    Rgba sp8;
    Rgba *p = &sp8;

    fn_8012772C(arg1, QB_ALPHA, s->alpha);
    sp8 = s->rgba;
    fn_8003E7CC(0xC);
    {
        void *c = fn_80128F94();
        fn_80129068(c, 4, 1);
        fn_80129260(c, 0, sp8.r);
        fn_80129260(c, 1, sp8.g);
        fn_80129260(c, 2, ((u8 *)&sp8)[2]);
        fn_80129260(c, 3, ((u8 *)&sp8)[3]);
        fn_80127AAC(arg1, QB_RGBA, c);
        fn_80126A30(c);
        if (c != 0) {
            fn_80128FB4(c, 3);
        }
    }
    if (s->scale_x == s->scale_y) {
        fn_8012772C(arg1, QB_SCALE, s->scale_x);
    } else {
        fn_80127A18(arg1, QB_SCALE, s->scale_x, s->scale_y);
    }
    t = &arg0->sp;
    fn_80127A18(arg1, QB_POS, t->pos_x, t->pos_y);
    fn_8012772C(arg1, QB_ROT_ANGLE, (t->angle * lbl_8029232C) / lbl_80292330);
    if (fn_80042110(arg0) != 0) {
        AddInteger(arg1, QB_EVENTS_BLOCKED, 1);
    } else {
        AddInteger(arg1, QB_EVENTS_BLOCKED, 0);
    }
}
