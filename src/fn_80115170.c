// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80115170-0x801153BC (588B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct CStruct CStruct;
typedef struct { char pad0x00[0x18]; s32 unk0x18; } Sc;
typedef struct {
    char pad0x00[2];
    u8 type;
    char pad0x03;
    s32 count;
} Arr;
typedef struct {
    char pad0x00[4];
    f32 a;
    f32 b;
    f32 c;
} V3;
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetArray(s32 arg0, s32 arg1, void *arg2, s32 arg3);
void *fn_801259C8(s32 arg0, s32 arg1);
s32 GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_8012954C(s32 arg0, s32 arg1);
s32 fn_80129528(s32 arg0, s32 arg1);
s32 fn_801293FC(s32 arg0, s32 arg1);
f32 fn_80129420(s32 arg0, s32 arg1);
void fn_8012772C(s32 arg0, s32 arg1);
s32 GetChecksum(s32 arg0, s32 arg1);
void AddChecksum(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8012935C(s32 arg0, s32 arg1);
void AddString(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80129504(s32 arg0, s32 arg1);
s32 fn_801294E0(s32 arg0, s32 arg1);
void fn_80127A18(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void fn_8012788C(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
void AddInteger(s32 arg0, s32 arg1, s32 arg2);
void fn_80127C14(s32 arg0, s32 arg1, s32 arg2);
void fn_80127AAC(s32 arg0, s32 arg1, s32 arg2);
bool ScriptGet2DArrayData(CStruct *arg0, Sc *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sub;
    V3 *v;

    sp8 = 0;
    GetChecksum_2(arg0, QB_ARRAYNAME, &sp8, 1);
    spC = 0;
    if (GetArray(arg1->unk0x18, sp8, &spC, 0) == 0) {
        spC = (s32)fn_801259C8(sp8, 1);
    }
    sp10 = 0;
    GetInteger(arg0, QB_INDEX1, &sp10, 1);
    sp14 = 0;
    GetInteger(arg0, QB_INDEX2, &sp14, 1);
    sub = fn_8012954C(spC, sp10);
    switch (((Arr *)sub)->type) {
    case 1:
        AddInteger(arg1->unk0x18, QB_VAL, fn_801293FC(sub, sp14));
        break;
    case 2: {
        s32 sc = arg1->unk0x18;
        fn_80129420(sub, sp14);
        fn_8012772C(sc, QB_VAL);
        break;
    }
    case 13:
        AddChecksum(arg1->unk0x18, QB_VAL, GetChecksum(sub, sp14));
        break;
    case 3:
        AddString(arg1->unk0x18, QB_VAL, fn_8012935C(sub, sp14));
        break;
    case 4:
        AddString(arg1->unk0x18, QB_VAL, fn_8012935C(sub, sp14));
        break;
    case 5:
        v = (V3 *)fn_80129504(sub, sp14);
        fn_80127A18(arg1->unk0x18, QB_VAL, v->a, v->b);
        break;
    case 6:
        v = (V3 *)fn_801294E0(sub, sp14);
        fn_8012788C(arg1->unk0x18, QB_VAL, v->a, v->b, v->c);
        break;
    case 10:
        fn_80127C14(arg1->unk0x18, QB_VAL, fn_80129528(sub, sp14));
        break;
    case 12:
        fn_80127AAC(arg1->unk0x18, QB_VAL, fn_8012954C(sub, sp14));
        break;
    }
    return true;
}
