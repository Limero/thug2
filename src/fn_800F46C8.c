// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F46C8-0x800F47F8 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0x68];
    s16 unk0x68;
    char pad0x6A[2];
    void (*unk0x6C)(void *);
} Vt_800F46C8;

typedef struct {
    char pad0x0[0x10];
    s32 unk0x10;
    char pad0x14[0x20];
} Obj20_800F46C8;

typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x4C];
} Str_800F46C8;

typedef struct {
    char pad0x0[0x20];
    Obj20_800F46C8 *unk0x20;
    void *unk0x24;
    s32 unk0x28;
    char pad0x2C[0x24];
    Vt_800F46C8 *unk0x50;
    Str_800F46C8 *unk0x54;
} Obj_800F46C8;

extern s32 fn_800F3690(void *, void *, s32, s32, void *, s32);
extern void fn_800F49A0(void *, void *, s32);
extern char *strcpy(char *, const char *);
extern void fn_8005761C(char *, char *, s32);
extern Obj20_800F46C8 *fn_8001371C(char *, s32, s32);
extern void fn_8001075C(void *);
extern s32 fn_800132A4(void *);
extern void *Mem_Alloc_3(u32);
extern void fn_80010760(void);
extern void fn_80013294(void *, s32, void *, s32);
extern s32 fn_800132F8(void *, void *, s32, s32);
extern void fn_800F39DC(void);

s32 fn_800F46C8(Obj_800F46C8 *self, char *name, s32 flag, s32 a3, void *a4, s32 a5) {
    char buf[256];
    Obj20_800F46C8 *h;
    s32 n;
    Vt_800F46C8 *vt;
    void (*fp)(void *);

    fn_800F3690(self, name, flag, a3, a4, a5);
    fn_800F49A0(self, a4, a5);
    strcpy((char *)self->unk0x54 + 8, name);
    fn_8005761C(buf, name, self->unk0x54->unk0x4);
    h = fn_8001371C(buf, flag ^ 1, 0x64);
    self->unk0x20 = h;
    if (h == NULL) {
        return -1;
    }
    fn_8001075C(buf);
    n = fn_800132A4(self->unk0x20);
    self->unk0x24 = Mem_Alloc_3(n);
    fn_80010760();
    if (flag != 0) {
        self->unk0x20->unk0x10 = 0;
        self->unk0x20->unk0x10 |= 8;
        fn_80013294(self->unk0x20, (s32)fn_800F39DC, self, 0);
    }
    fn_800132F8(self->unk0x20, self->unk0x24, 1, n);
    if (flag == 0) {
        self->unk0x28 = n;
        vt = self->unk0x50;
        fp = vt->unk0x6C;
        fp((char *)self + vt->unk0x68);
    }
    return 0;
}
