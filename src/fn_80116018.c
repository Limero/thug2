// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116018-0x80116164 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct CStruct CStruct;

typedef struct {
    char pad0x00[0x18];
    s32 unk0x18;
} Sc;

typedef struct {
    char pad0x00[2];
    u8 type;
    char pad0x03;
    s32 count;
} Arr;

extern char lbl_8029D1E0[];

s32 GetArray(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 fn_80128294(CStruct *arg0, void *arg1, void *arg2, s32 arg3);
void fn_801270B4(s32 arg0, s32 arg1);
CStruct *CStruct_new(s32 arg0);
CStruct *CStruct_ctor(CStruct *arg0);
s32 fn_80129528(CStruct *arg0, s32 arg1);
void fn_80126FF4(CStruct *arg0, s32 arg1);
void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_8012954C(s32 arg0, s32 arg1);
void fn_80127F40(s32 arg0, s32 arg1, s32 arg2);
s32 fn_801293FC(s32 arg0, s32 arg1);

bool ScriptGetElement(CStruct *arg0, Sc *arg1) {
    Arr *sp8;
    s32 spC;
    CStruct *t;

    sp8 = 0;
    GetArray(arg0, 0, &sp8, 0);
    spC = 0;
    fn_80128294(arg0, lbl_8029D1E0, &spC, 0);
    fn_801270B4(arg1->unk0x18, QB_ELEMENT);
    if (sp8 != NULL) {
        if (spC < 0 || spC >= sp8->count) {
            return false;
        }
        switch (sp8->type) {
        case 10:
            t = CStruct_ctor(CStruct_new(8));
            fn_80126FF4(t, fn_80129528((CStruct *)sp8, spC));
            fn_80127E70(arg1->unk0x18, QB_ELEMENT, 0xB, (s32)t);
            break;
        case 12:
            fn_80127F40(arg1->unk0x18, QB_ELEMENT, fn_8012954C((s32)sp8, spC));
            break;
        case 1:
            fn_80127E70(arg1->unk0x18, QB_ELEMENT, 1, fn_801293FC((s32)sp8, spC));
            break;
        }
    }
    return true;
}
