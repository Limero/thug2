// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80087010-0x80087240 (560B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern float lbl_802965D8[];
extern float lbl_80366DC8[];

void fn_80099B2C(s32, s32, s32);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
s32 fn_8001EFBC(s32, s32 *);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F4(void);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F250(s32, s32);
void fn_8001F2D8(s32, ...);
int rand(void);

typedef struct {
    char pad0x00[0x20];
    u16 unk20;
    u16 unk22;
    char pad0x24[0x8];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} prm_t;

typedef struct {
    f32 f0, f4, f8;
    s32 padC;
    s32 idx10;
    s16 v14, v16;
    f32 f18, f1C, f20;
    s32 pad24;
    s32 idx28;
    s16 v2C, v2E;
    f32 f30, f34, f38;
    s32 pad3C;
    s32 idx40;
    s16 v44, v46;
} vtx_t;

void fn_80087010(prm_t *arg0) {
    struct { volatile s32 w; } sp8;
    struct { s8 r, g, b; u8 a; } col;
    s32 sp10;
    s32 i;
    vtx_t *p;
    u8 v;

    i = 0;
    fn_80099B2C(arg0->unk2C, arg0->unk30, arg0->unk38);
    fn_8001E248(0, 1, 1, 0, 0, 0, 2);
    fn_8001E248(2, 0, 1, 1, 0, 0, 2);
    col.r = (s8)(lbl_80366DC8[0] * lbl_802965D8[0]);
    col.a = 0xFF;
    col.g = (s8)(lbl_80366DC8[1] * lbl_802965D8[0]);
    col.b = (s8)(lbl_80366DC8[2] * lbl_802965D8[0]);
    sp8.w = *(s32 *) &col;
    fn_8001EFBC(4, &sp8.w);
    fn_8001F2D8(3, 9, 1, 0xB, 1, 0xD, 1);
    fn_8001F0A0(0x90, arg0->unk3C, (u16)(arg0->unk20 * 3));
    p = (vtx_t *)arg0->unk34;
    while (i < (s32)arg0->unk20) {
        v = 0;
        if (arg0->unk22 != 0) {
            v = (u8)(rand() % (0x100 - arg0->unk22));
            if (v != 0) {
                v = 0;
            } else {
                v = 0x32;
            }
        }
        *(s8 *) &sp10 = v;
        i++;
        *(s8 *) ((char *) &sp10 + 1) = v;
        *(s8 *) ((char *) &sp10 + 2) = v;
        fn_8001F0F8(p->f0, p->f4, p->f8);
        fn_8001F1D4(p->idx10 + sp10);
        fn_8001F250(p->v14, p->v16);
        fn_8001F0F8(p->f18, p->f1C, p->f20);
        fn_8001F1D4(p->idx28 + sp10);
        fn_8001F250(p->v2C, p->v2E);
        fn_8001F0F8(p->f30, p->f34, p->f38);
        fn_8001F1D4(p->idx40 + sp10);
        fn_8001F250(p->v44, p->v46);
        p++;
    }
    fn_8001F0F4();
}
