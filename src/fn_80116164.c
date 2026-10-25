// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116164-0x80116380 (540B). Byte-identical.
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
s32 GetArray(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_801270B4(s32 arg0, s32 arg1);
void AddInteger(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80129528(s32 arg0, s32 arg1);
s32 fn_8012954C(s32 arg0, s32 arg1);
s32 fn_801293FC(s32 arg0, s32 arg1);
f32 fn_80129420(s32 arg0, s32 arg1);
void fn_8012772C(s32 arg0, s32 arg1);
s32 GetChecksum(s32 arg0, s32 arg1);
void AddChecksum(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8012935C(s32 arg0, s32 arg1);
s32 fn_801293AC(s32 arg0, s32 arg1);
void AddString(s32 arg0, s32 arg1, s32 arg2);
void fn_80127618(s32 arg0, s32 arg1, s32 arg2);
void fn_80127C14(s32 arg0, s32 arg1, s32 arg2);
void fn_80127AAC(s32 arg0, s32 arg1, s32 arg2);
bool ScriptGetNextArrayElement(CStruct *arg0, Sc *arg1) {
    Arr *sp8;
    s32 spC;
    s32 n;

    sp8 = 0;
    GetArray(arg0, 0, &sp8, 0);
    spC = -1;
    GetInteger(arg1->unk0x18, QB_INDEX, &spC, 0);
    fn_801270B4(arg1->unk0x18, QB_INDEX);
    fn_801270B4(arg1->unk0x18, QB_ELEMENT);
    if (sp8 == NULL) {
        return false;
    }
    n = sp8->count;
    if (spC < 0) {
        spC = 0;
        if (n == 0) {
            return false;
        }
    } else {
        spC = spC + 1;
        if (spC >= n) {
            return false;
        }
    }
    AddInteger(arg1->unk0x18, QB_INDEX, spC);
    switch (sp8->type) {
    case 10:
        fn_80127C14(arg1->unk0x18, QB_ELEMENT, fn_80129528((s32)sp8, spC));
        break;
    case 12:
        fn_80127AAC(arg1->unk0x18, QB_ELEMENT, fn_8012954C((s32)sp8, spC));
        break;
    case 1:
        AddInteger(arg1->unk0x18, QB_ELEMENT, fn_801293FC((s32)sp8, spC));
        break;
    case 2: {
        s32 sc = arg1->unk0x18;
        fn_80129420((s32)sp8, spC);
        fn_8012772C(sc, QB_ELEMENT);
        break;
    }
    case 13:
        AddChecksum(arg1->unk0x18, QB_ELEMENT, GetChecksum((s32)sp8, spC));
        break;
    case 3:
        AddString(arg1->unk0x18, QB_ELEMENT, fn_8012935C((s32)sp8, spC));
        break;
    case 4:
        fn_80127618(arg1->unk0x18, QB_ELEMENT, fn_801293AC((s32)sp8, spC));
        break;
    }
    return true;
}
