// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117284-0x80117334 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x18];
    s32 unk0x18;
} Sc;

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 *fn_8003E7CC(u32 size);
s32 *fn_80128F94(s32 *self);
void fn_80129068(s32 *self, s32 a, s32 b);
void fn_80129260(s32 *self, s32 idx, s32 val);
void fn_80127AAC(s32, s32, s32 *);
void fn_80126A30(s32 *);
void fn_80128FB4(s32 *, s32);

bool ScriptCreateIndexArray(CStruct *arg0, Sc *arg1) {
    s32 sp8;
    s32 i;
    s32 *arr;

    GetInteger(arg0, 0, &sp8, 1);
    i = 0;
    arr = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(arr, sp8, 1);
    while (i < sp8) {
        fn_80129260(arr, i, i);
        i++;
    }
    fn_80127AAC(arg1->unk0x18, QB_INDEX_ARRAY, arr);
    fn_80126A30(arr);
    if (arr != 0) {
        fn_80128FB4(arr, 3);
    }
    return true;
}
