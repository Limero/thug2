// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012AF84-0x8012B1C0 (572B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef union {
    f32 f;
    s32 i;
} F32I;

typedef struct {
    u32 hi:9;
    u32 ty:7;
    u32 lo:16;
} FLAGS;

typedef union {
    FLAGS f;
    u32 w;
} HEAD;

typedef struct {
    HEAD h;
    s32 pad4;
    F32I v;
} OBJ;

typedef struct {
    char p0[2];
    u8 ty;
    char p3[9];
    F32I v;
} TMP;

s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void *fn_80124FDC(Unk_C71E6DE1 *);
void *fn_80128F94(Unk_9D4ED6AF *);
s32 fn_80128EF4(s32);
s32 fn_80128F44(s32);
void *fn_80125000(Unk_C71E6DE1 *);
s32 CreateString(char *);
s32 fn_8012935C(Unk_F8A5095F *, s32);
s32 fn_801293FC(CStruct *, s32);
f32 fn_80129420(CStruct *, s32);
s32 GetChecksum(CStruct *, s32);
s32 fn_801294E0(CStruct *, s32);
s32 fn_80129504(CStruct *, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_8012954C(CStruct *, s32);
s32 fn_8003E7CC(s32);
void fn_8012AF84(TMP *arg0, s32 arg1, OBJ *arg2, s32 arg3) {
    Unk_C71E6DE1 *p;
    Unk_C71E6DE1 *p2;
    s32 q;

    arg2->h.f.ty = arg0->ty;
    switch ((s32)arg2->h.f.ty) {                   
    case 1:
        arg2->v.i = fn_801293FC(arg0, arg1);
        return;
    case 2:
        arg2->v.f = fn_80129420(arg0, arg1);
        return;
    case 13:
        arg2->v.i = GetChecksum(arg0, arg1);
        return;
    case 10:
        if (arg3 != 0) {
            arg2->h.f.ty = 0x14;
            arg2->v.i = fn_80129528(arg0, arg1);
            return;
        }
        q = CStruct_new(8);
        q = CStruct_ctor(q);
        arg2->v.i = q;
        fn_80126FF4((Unk_80577C09 *)q, fn_80129528(arg0, arg1));
        return;
    case 12:
        if (arg3 != 0) {
            arg2->h.f.ty = 0x15;
            arg2->v.i = fn_8012954C(arg0, arg1);
            return;
        }
        q = fn_8003E7CC(0xC);
        q = (s32)fn_80128F94((Unk_9D4ED6AF *)q);
        arg2->v.i = q;
        fn_80126E28((Unk_5AA7B5D7 *)q, fn_8012954C(arg0, arg1));
        return;
    case 3:
        arg2->v.i = CreateString((char *)fn_8012935C(arg0, arg1));
        return;
    case 6:
        p = (Unk_C71E6DE1 *)fn_801294E0(arg0, arg1);
        q = fn_80128F44(0x10);
        arg2->v.i = (s32)fn_80124FDC((Unk_C71E6DE1 *)q);
        *(f32 *)&((Unk_C71E6DE1 *)arg2->v.i)->unk0x4 = *(f32 *)&p->unk0x4;
        *(f32 *)&((Unk_C71E6DE1 *)arg2->v.i)->unk0x8 = *(f32 *)&p->unk0x8;
        *(f32 *)&((Unk_C71E6DE1 *)arg2->v.i)->unk0xC = *(f32 *)&p->unk0xC;
        return;
    case 5:
        p2 = (Unk_C71E6DE1 *)fn_80129504(arg0, arg1);
        q = fn_80128EF4(0xC);
        arg2->v.i = (s32)fn_80125000((Unk_C71E6DE1 *)q);
        *(f32 *)&((Unk_C71E6DE1 *)arg2->v.i)->unk0x4 = *(f32 *)&p2->unk0x4;
        *(f32 *)&((Unk_C71E6DE1 *)arg2->v.i)->unk0x8 = *(f32 *)&p2->unk0x8;
        return;
    default:
        arg2->v.i = 0;
        arg2->h.f.ty = 0;
        return;
    }
}
