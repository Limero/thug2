// Auto-generated from tools/gen_dispatch_fns.py
// (table-dispatch / field-fnptr / set-dispatch / const-dispatch helpers).
#include "types.h"

void fn_8000BEB8(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_80013D44(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_80024344(void *o) { /* d base=0x24 off=0x10 */
    void **t = *(void ***)((char *)o + 0x24);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_80035A64(void *o) { /* d base=0x14 off=0x28 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_80058234(void *o) { /* d base=0x18 off=0x10 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800585B4(void *o) { /* d base=0x4 off=0x10 */
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800585E8(void *o) { /* d base=0x4 off=0x18 */
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8005861C(void *o) { /* d base=0x4 off=0x20 */
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80058650(void *o) { /* d base=0x4 off=0x28 */
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_800586CC(void *o) { /* d base=0x4 off=0x48 */
    void **t = *(void ***)((char *)o + 0x4);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}

void fn_80058B48(void *o, u32 v) { /* s store=0x40 base=0x50 off=0x18 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x40) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80058B80(void *o, u32 v) { /* s store=0x0 base=0x50 off=0x20 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x0) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80058E40(void *o, u32 v) { /* s store=0x3C base=0x50 off=0x20 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x3C) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80058E78(void *o, u32 v) { /* s store=0x48 base=0x50 off=0x30 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x48) = v;
    t = *(void ***)((char *)o + 0x50);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005B488(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8005B4BC(void *o) { /* d base=0x18 off=0x30 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005B560(void *o) { /* d base=0x18 off=0x40 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20]);
}

void fn_8005B594(void *o) { /* d base=0x18 off=0x50 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x15];
    fp((char *)o + (signed short)((s16 *)t)[0x28]);
}

void fn_8005B5C8(void *o) { /* d base=0x18 off=0x58 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x17];
    fp((char *)o + (signed short)((s16 *)t)[0x2c]);
}

void fn_8005C070(void *o) { /* d base=0x8 off=0x28 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_8005C0A4(void *o) { /* d base=0x8 off=0x30 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005C0D8(void *o) { /* d base=0x8 off=0x48 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}

void fn_8005C10C(void *o) { /* d base=0x8 off=0x50 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x15];
    fp((char *)o + (signed short)((s16 *)t)[0x28]);
}

void fn_8005C140(void *o) { /* d base=0x8 off=0x58 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x17];
    fp((char *)o + (signed short)((s16 *)t)[0x2c]);
}

void fn_8005C1B4(void *o) { /* d base=0x8 off=0x70 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x1d];
    fp((char *)o + (signed short)((s16 *)t)[0x38]);
}

void fn_8005C1E8(void *o) { /* d base=0x8 off=0x78 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x1f];
    fp((char *)o + (signed short)((s16 *)t)[0x3c]);
}

void fn_8005C21C(void *o) { /* d base=0x8 off=0x80 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x21];
    fp((char *)o + (signed short)((s16 *)t)[0x40]);
}

void fn_8005C250(void *o) { /* d base=0x8 off=0x88 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x23];
    fp((char *)o + (signed short)((s16 *)t)[0x44]);
}

void fn_8005C284(void *o) { /* d base=0x8 off=0x90 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x25];
    fp((char *)o + (signed short)((s16 *)t)[0x48]);
}

void fn_8005C36C(void *o) { /* d base=0x8 off=0xB0 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x2d];
    fp((char *)o + (signed short)((s16 *)t)[0x58]);
}

void fn_8005C3E0(void *o) { /* d base=0x8 off=0xC0 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x31];
    fp((char *)o + (signed short)((s16 *)t)[0x60]);
}

void fn_8005C414(void *o) { /* d base=0x8 off=0xC8 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x33];
    fp((char *)o + (signed short)((s16 *)t)[0x64]);
}

void fn_8005C448(void *o) { /* d base=0x8 off=0xD0 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x35];
    fp((char *)o + (signed short)((s16 *)t)[0x68]);
}

void fn_8005C47C(void *o) { /* d base=0x8 off=0xD8 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x37];
    fp((char *)o + (signed short)((s16 *)t)[0x6c]);
}

void fn_8005C4B0(void *o) { /* d base=0x8 off=0xE0 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x39];
    fp((char *)o + (signed short)((s16 *)t)[0x70]);
}

void fn_8005C4E4(void *o) { /* d base=0x8 off=0xE8 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x3b];
    fp((char *)o + (signed short)((s16 *)t)[0x74]);
}

void fn_8005C518(void *o) { /* d base=0x8 off=0xF0 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x3d];
    fp((char *)o + (signed short)((s16 *)t)[0x78]);
}

void fn_8005C54C(void *o) { /* d base=0x8 off=0xF8 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x3f];
    fp((char *)o + (signed short)((s16 *)t)[0x7c]);
}

void fn_8005C580(void *o) { /* d base=0x8 off=0x108 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x43];
    fp((char *)o + (signed short)((s16 *)t)[0x84]);
}

void fn_8005C5BC(void *o) { /* d base=0x8 off=0x110 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x45];
    fp((char *)o + (signed short)((s16 *)t)[0x88]);
}

void fn_8005C5F0(void *o) { /* d base=0x8 off=0x118 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x47];
    fp((char *)o + (signed short)((s16 *)t)[0x8c]);
}

void fn_8005C624(void *o) { /* d base=0x8 off=0x128 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4b];
    fp((char *)o + (signed short)((s16 *)t)[0x94]);
}

void fn_8005C658(void *o) { /* d base=0x8 off=0x130 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4d];
    fp((char *)o + (signed short)((s16 *)t)[0x98]);
}

void fn_8005C68C(void *o) { /* d base=0x8 off=0x138 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x4f];
    fp((char *)o + (signed short)((s16 *)t)[0x9c]);
}

void fn_8005C6E8(void *o) { /* d base=0x8 off=0x150 */
    void **t = *(void ***)((char *)o + 0x8);
    void (*fp)(void *) = (void (*)(void *))t[0x55];
    fp((char *)o + (signed short)((s16 *)t)[0xa8]);
}

void fn_8005E628(void *o, u32 v) { /* s store=0x30 base=0x4C off=0x18 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x30) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8005E6C8(void *o, u32 v) { /* s store=0x4 base=0x4C off=0x20 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x4) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_8005E9C8(void *o, u32 v) { /* s store=0x38 base=0x4C off=0x20 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x38) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_8005EA3C(void *o, u32 v) { /* s store=0x48 base=0x4C off=0x30 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x48) = v;
    t = *(void ***)((char *)o + 0x4C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005EABC(void *o, u32 v) { /* s store=0x14 base=0x1C off=0x30 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x14) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005EB6C(void *o, u32 v) { /* s store=0x8 base=0x1C off=0x28 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x8) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_8005EBE4(void *o, u32 v) { /* s store=0x4 base=0x1C off=0x30 */
    void **t;
    void (*fp)(void *);
    *(u32 *)((char *)o + 0x4) = v;
    t = *(void ***)((char *)o + 0x1C);
    fp = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_8005F098(void *o) { /* d base=0x14 off=0x28 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0xb];
    fp((char *)o + (signed short)((s16 *)t)[0x14]);
}

void fn_8005F0CC(void *o) { /* d base=0x14 off=0x48 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x13];
    fp((char *)o + (signed short)((s16 *)t)[0x24]);
}

void fn_8005F188(void *o) { /* d base=0x14 off=0x60 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x19];
    fp((char *)o + (signed short)((s16 *)t)[0x30]);
}

void fn_8005F1BC(void *o) { /* d base=0x14 off=0x68 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1b];
    fp((char *)o + (signed short)((s16 *)t)[0x34]);
}

void fn_8005F1F0(void *o) { /* d base=0x14 off=0x70 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1d];
    fp((char *)o + (signed short)((s16 *)t)[0x38]);
}

void fn_8005F224(void *o) { /* d base=0x14 off=0x78 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x1f];
    fp((char *)o + (signed short)((s16 *)t)[0x3c]);
}

void fn_8005F258(void *o) { /* d base=0x14 off=0x80 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x21];
    fp((char *)o + (signed short)((s16 *)t)[0x40]);
}

void fn_8005F2D0(void *o) { /* d base=0x14 off=0x88 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x23];
    fp((char *)o + (signed short)((s16 *)t)[0x44]);
}

void fn_8005F304(void *o) { /* d base=0x14 off=0x98 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x27];
    fp((char *)o + (signed short)((s16 *)t)[0x4c]);
}

void fn_8005F338(void *o) { /* d base=0x14 off=0xA0 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x29];
    fp((char *)o + (signed short)((s16 *)t)[0x50]);
}

void fn_8005F36C(void *o) { /* d base=0x14 off=0xA8 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x2b];
    fp((char *)o + (signed short)((s16 *)t)[0x54]);
}

void fn_8005F3A0(void *o) { /* d base=0x14 off=0xB8 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x2f];
    fp((char *)o + (signed short)((s16 *)t)[0x5c]);
}

void fn_8005F3D4(void *o) { /* d base=0x14 off=0xD0 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x35];
    fp((char *)o + (signed short)((s16 *)t)[0x68]);
}

void fn_8005F418(void *o) { /* d base=0x14 off=0xE0 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x39];
    fp((char *)o + (signed short)((s16 *)t)[0x70]);
}

void fn_8005F44C(void *o) { /* d base=0x14 off=0xE8 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x3b];
    fp((char *)o + (signed short)((s16 *)t)[0x74]);
}

void fn_8005F480(void *o) { /* d base=0x14 off=0xF0 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x3d];
    fp((char *)o + (signed short)((s16 *)t)[0x78]);
}

void fn_8005F4B4(void *o) { /* d base=0x14 off=0xF8 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x3f];
    fp((char *)o + (signed short)((s16 *)t)[0x7c]);
}

void fn_8005F4E8(void *o) { /* d base=0x14 off=0x100 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x41];
    fp((char *)o + (signed short)((s16 *)t)[0x80]);
}

void fn_8005F51C(void *o) { /* d base=0x14 off=0x108 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x43];
    fp((char *)o + (signed short)((s16 *)t)[0x84]);
}

void fn_8005F550(void *o) { /* d base=0x14 off=0x128 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x4b];
    fp((char *)o + (signed short)((s16 *)t)[0x94]);
}

void fn_8005F584(void *o) { /* d base=0x14 off=0x130 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x4d];
    fp((char *)o + (signed short)((s16 *)t)[0x98]);
}

void fn_8005F5B8(void *o) { /* d base=0x14 off=0x138 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x4f];
    fp((char *)o + (signed short)((s16 *)t)[0x9c]);
}

void fn_8005F5EC(void *o) { /* d base=0x14 off=0x110 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x45];
    fp((char *)o + (signed short)((s16 *)t)[0x88]);
}

void fn_8005F620(void *o) { /* d base=0x14 off=0x110 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x45];
    fp((char *)o + (signed short)((s16 *)t)[0x88]);
}

void fn_8005F654(void *o) { /* d base=0x14 off=0x120 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x49];
    fp((char *)o + (signed short)((s16 *)t)[0x90]);
}

void fn_8005F70C(void *o) { /* d base=0x14 off=0x140 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x51];
    fp((char *)o + (signed short)((s16 *)t)[0xa0]);
}

void fn_8005F740(void *o) { /* d base=0x14 off=0x148 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x53];
    fp((char *)o + (signed short)((s16 *)t)[0xa4]);
}

void fn_8005F774(void *o) { /* d base=0x14 off=0x150 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x55];
    fp((char *)o + (signed short)((s16 *)t)[0xa8]);
}

void fn_8005F7A8(void *o) { /* d base=0x14 off=0x158 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x57];
    fp((char *)o + (signed short)((s16 *)t)[0xac]);
}

void fn_8005F7DC(void *o) { /* d base=0x14 off=0x160 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x59];
    fp((char *)o + (signed short)((s16 *)t)[0xb0]);
}

void fn_8005F810(void *o) { /* d base=0x14 off=0x168 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x5b];
    fp((char *)o + (signed short)((s16 *)t)[0xb4]);
}

void fn_8005F844(void *o) { /* d base=0x14 off=0x170 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x5d];
    fp((char *)o + (signed short)((s16 *)t)[0xb8]);
}

void fn_8005F878(void *o) { /* d base=0x14 off=0x178 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x5f];
    fp((char *)o + (signed short)((s16 *)t)[0xbc]);
}

void fn_8005F8AC(void *o) { /* d base=0x14 off=0x180 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x61];
    fp((char *)o + (signed short)((s16 *)t)[0xc0]);
}

void fn_8005F8E8(void *o) { /* d base=0x14 off=0x188 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x63];
    fp((char *)o + (signed short)((s16 *)t)[0xc4]);
}

void fn_8005F91C(void *o) { /* d base=0x14 off=0x190 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x65];
    fp((char *)o + (signed short)((s16 *)t)[0xc8]);
}

void fn_8005F950(void *o) { /* d base=0x14 off=0x198 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x67];
    fp((char *)o + (signed short)((s16 *)t)[0xcc]);
}

void fn_8005FD34(void *o) { /* d base=0x50 off=0x18 */
    void **t = *(void ***)((char *)o + 0x50);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80070244(void *o) { /* d base=0x5C off=0x10 */
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_80070278(void *o) { /* d base=0x5C off=0x18 */
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800702AC(void *o) { /* d base=0x5C off=0x20 */
    void **t = *(void ***)((char *)o + 0x5C);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80070B40(void *o) { /* d base=0x20 off=0x10 */
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_80070B74(void *o) { /* d base=0x20 off=0x20 */
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_80070C78(void *o) { /* d base=0x20 off=0x120 */
    void **t = *(void ***)((char *)o + 0x20);
    void (*fp)(void *) = (void (*)(void *))t[0x49];
    fp((char *)o + (signed short)((s16 *)t)[0x90]);
}

void fn_8009CEF8(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8009D3A4(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8009F5CC(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800A2184(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_800A3A94(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_800A3D34(void *o) { /* d base=0x18 off=0x10 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800B6E3C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800B7354(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800B776C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800C9748(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800CB218(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800CC7D4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800CCA98(void *o) { /* d base=0x18 off=0x10 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800CD5F0(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800CD624(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800CDE98(void *o) { /* d base=0x18 off=0x10 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800DB978(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_800DBAA8(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800DCFF0(void *o) { /* d base=0x18 off=0x10 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x5];
    fp((char *)o + (signed short)((s16 *)t)[0x8]);
}

void fn_800DE000(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800DE1A4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DE1D8(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800DE354(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DE608(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DEC28(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DED50(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DF668(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800DF69C(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800E057C(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_800E0890(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800E3C08(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800E4F5C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EB604(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EB638(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800ECDFC(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EDFC0(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EEC00(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF030(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF064(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800EF21C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF250(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800EF3E4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF624(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_800EF658(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_800F3564(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_80138DF0(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8013E27C(void *o) { /* d base=0x2300 off=0x30 */
    void **t = *(void ***)((char *)o + 0x2300);
    void (*fp)(void *) = (void (*)(void *))t[0xd];
    fp((char *)o + (signed short)((s16 *)t)[0x18]);
}

void fn_801567A4(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8016D214(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_8016D248(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_80177428(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8018F4E0(void *o) { /* d base=0x14 off=0x20 */
    void **t = *(void ***)((char *)o + 0x14);
    void (*fp)(void *) = (void (*)(void *))t[0x9];
    fp((char *)o + (signed short)((s16 *)t)[0x10]);
}

void fn_8019E510(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_8019E544(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_801A0CF0(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_801A386C(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_801B1CC8(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801BBA34(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801BF520(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C0E0C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C12F4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C1BC4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C1BF8(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801C22EC(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C397C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C4F64(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C59B8(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801C65CC(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801CA870(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801CB004(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801CB784(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801CBB58(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801CBB8C(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801CD540(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EDAD4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EE8C4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EECF4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EF5FC(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EF750(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EFD58(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801EFDC8(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801F0AB8(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801F0B50(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801F1134(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801F1168(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801F54B8(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FAEA4(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FCF20(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FE59C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FEC2C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FEC60(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_801FF164(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_801FFE70(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_802010C8(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_802031E8(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8020385C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80203890(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_80203F5C(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80204378(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_802047E0(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_80205520(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8020651C(void *o) { /* l base=0x18 off=0x40 const=1 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *, int) = (void (*)(void *, int))t[0x11];
    fp((char *)o + (signed short)((s16 *)t)[0x20], 1);
}

void fn_8020CA70(void *o) { /* d base=0x18 off=0x18 */
    void **t = *(void ***)((char *)o + 0x18);
    void (*fp)(void *) = (void (*)(void *))t[0x7];
    fp((char *)o + (signed short)((s16 *)t)[0xc]);
}

void fn_8022319C(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_802231D0(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_80223204(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}

void fn_8023515C(void *o) { /* f off=0x28 */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x28);
    fp(o);
}

void fn_802351C0(void *o) { /* f off=0x1C */
    void (*fp)(void *) = *(void (**)(void *))((char *)o + 0x1C);
    fp(o);
}
