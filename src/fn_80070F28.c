// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070F28-0x8007111C (500B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801293FC(CStruct *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
typedef struct SkaterVT {
    char pad0x00[0x18];
    s16 off0x18;
    char pad0x1A[0x2];
    s32 fn0x1C;
    s16 off0x20;
    char pad0x22[0x2];
    s32 fn0x24;
    s16 off0x28;
    char pad0x2A[0x2];
    s32 fn0x2C;
    s16 off0x30;
    char pad0x32[0x2];
    s32 fn0x34;
} SkaterVT;
bool fn_80070F28(CStruct *arg0, CStruct *arg1) {
    volatile s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    u8 buf1[4];
    s32 sp20;
    u8 buf2[4];
    SkaterVT *vtA;
    SkaterVT *vtB;

    spC = -1;
    sp10 = -1;
    sp14 = -1;
    if (GetInteger(arg1, QB_ON, &spC, 0) != 0) {
        vtA = (SkaterVT *)arg0->unk0x4;
        ((s32 (*)(void *, void *))vtA->fn0x1C)((char *)arg0 + vtA->off0x18, spC);
    }
    GetInteger(arg1, QB_BLOOM1, &sp10, 0);
    GetInteger(arg1, QB_BLOOM2, &sp14, 0);
    if ((sp10 != -1) || (sp14 != -1)) {
        vtA = (SkaterVT *)arg0->unk0x4;
        ((s32 (*)(void *, void *, void *))vtA->fn0x2C)((char *)arg0 + vtA->off0x28, sp10, sp14);
    }
    sp18 = 0;
    if (GetArray(arg1, QB_STRENGTH, &sp18, 0) != 0) {
        s32 a = fn_801293FC(sp18, 0);
        s32 b = fn_801293FC(sp18, 1);
        s32 c = fn_801293FC(sp18, 2);
        buf1[0] = (u8)a;
        buf1[1] = (u8)b;
        buf1[2] = (u8)c;
        buf1[3] = 0;
        *(s32 *)(void *)&sp8 = *(s32 *)buf1;
        vtB = (SkaterVT *)arg0->unk0x4;
        ((s32 (*)(void *, void *))vtB->fn0x34)((char *)arg0 + vtB->off0x30, &sp8);
    }
    sp20 = 0;
    if (GetArray(arg1, QB_COLOR, &sp20, 0) != 0) {
        s32 a = fn_801293FC(sp20, 0);
        s32 b = fn_801293FC(sp20, 1);
        s32 c = fn_801293FC(sp20, 2);
        buf2[0] = (u8)a;
        buf2[1] = (u8)b;
        buf2[2] = (u8)c;
        buf2[3] = 0;
        *(s32 *)(void *)&sp8 = *(s32 *)buf2;
        vtB = (SkaterVT *)arg0->unk0x4;
        ((s32 (*)(void *, void *))vtB->fn0x24)((char *)arg0 + vtB->off0x20, &sp8);
    }
    return true;
}
