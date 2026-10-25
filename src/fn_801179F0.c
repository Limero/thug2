// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801179F0-0x80117AC8 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x18];
    s32 unk0x18;
} Sc;

void GetString(CStruct *, s32, void *, s32);
u32 strlen(char *);
void *fn_8003E7CC(u32 size);
void *fn_80128F94(void *self);
void fn_80129068(void *self, s32 n, s32 kind);
void fn_80129218(void *self, s32 idx, s32 val);
s32 CreateString(void *);
void AddArrayPointer(s32, s32, void *);

bool ScriptStringToCharArray(CStruct *arg0, Sc *arg1) {
    char *sp8;
    union { u16 h; u32 w; } acc;
    u32 len;
    u32 i;
    void *arr;

    sp8 = 0;
    GetString(arg0, QB_STRING, &sp8, 1);
    len = strlen(sp8);
    arr = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(arr, len, 3);
    i = 0;
    acc.h &= 0xFF00;
    while (i < len) {
        acc.h = (acc.h & 0xFF) | ((u16)((u8)sp8[i]) << 8);
        fn_80129218(arr, i, CreateString(&acc.h));
        i++;
    }
    AddArrayPointer(arg1->unk0x18, QB_CHAR_ARRAY, arr);
    return true;
}
