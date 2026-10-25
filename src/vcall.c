#include "types.h"
void fn_80058CC8(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0xC) = a0;
    *(float *)((char *)o + 0x10) = a1;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_80058D04(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x1C) = a0;
    *(float *)((char *)o + 0x20) = a1;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_8005DB64(void *o, s32 a0, s32 a1) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x0) = a0;
    *(s32 *)((char *)o + 0x4) = a1;
    t = *(void ***)((char *)o + 0x14);
    fp = (void (*)(void *))t[0x14 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x10 / 2]);
}

void fn_8005DBA0(void *o, s32 a0, s32 a1) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x8) = a0;
    *(s32 *)((char *)o + 0xC) = a1;
    t = *(void ***)((char *)o + 0x14);
    fp = (void (*)(void *))t[0x14 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x10 / 2]);
}

void fn_8005E700(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x8) = a0;
    *(float *)((char *)o + 0xC) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_8005E73C(void *o, s16 a0, s16 a1) {
    void **t;
    void (*fp)(void *);
    *(s16 *)((char *)o + 0x2C) = a0;
    *(s16 *)((char *)o + 0x2E) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_8005E898(void *o, s32 a0, s32 a1) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x3C) = a0;
    *(s32 *)((char *)o + 0x40) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_8005E8D4(void *o, float a0, float a1) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x18) = a0;
    *(float *)((char *)o + 0x1C) = a1;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_8005E910(void *o, float a0) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x20) = a0;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x24 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x20 / 2]);
}

void fn_80069D68(void *o, float a0) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x40) = a0;
    t = *(void ***)((char *)o + 0x1B8);
    fp = (void (*)(void *))t[0x3C / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x38 / 2]);
}

void fn_80069F1C(void *o, float a0) {
    void **t;
    void (*fp)(void *);
    *(float *)((char *)o + 0x138) = a0;
    t = *(void ***)((char *)o + 0x1B8);
    fp = (void (*)(void *))t[0x3C / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x38 / 2]);
}

void fn_8009C7F4(void *o, s32 a0, s32 a1, s32 a2, s32 a3) {
    void **t;
    void (*fp)(void *);
    *(s32 *)((char *)o + 0x28) = a0;
    *(s32 *)((char *)o + 0x30) = a1;
    *(s32 *)((char *)o + 0x34) = a2;
    *(s32 *)((char *)o + 0x2C) = a3;
    t = *(void ***)((char *)o + 0x20);
    fp = (void (*)(void *))t[0x34 / 4];
    fp((char *)o + (signed short)((s16 *)t)[0x30 / 2]);
}
