// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80139790-0x801399D8 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u16 a;
    u16 b;
} Elem;

typedef struct {
    u8   unk0;
    u8   unk1;
    u16  unk2;
    void *unk4;
    s32  unk8;
    s32  unkC;
    s32  unk10;
    s32  unk14;
    s32  unk18;
    s32  unk1C;
    u8   unk20;
    u8   pad21[7];
} Desc;

typedef struct Ctx {
    u8  *dest;              /* 0x000 */
    u8   code;              /* 0x004 */
    u8   pad5[3];
    s32  value;             /* 0x008 */
    void *stream;           /* 0x00c */
    void *owner;            /* 0x010 */
    s32  flags;             /* 0x014 */
    s32  unk18;             /* 0x018 */
    u16  unk1C;             /* 0x01c */
    Elem arr[31];           /* 0x01e */
    u16  pad9A;
    s32  count;             /* 0x09c */
    s32  active;            /* 0x0a0 */
    s32  unkA4;             /* 0x0a4 */
    u8   buf1[0x514];       /* 0x0a8 */
    u8   buf2[0x514];       /* 0x5bc */
    u16  unkAD8;            /* 0xad0 */
    u8   unkADA;            /* 0xad2 */
    u8   padAD3[5];
    Desc desc;              /* 0xad8 */
    u16  tmp;               /* 0xb00 */
    u8   padB02[2];
} Ctx;

typedef struct {
    char pad0[0x5C];
    u8  *pos;               /* 0x5c */
    u8  *end;               /* 0x60 */
    char pad64[0xC];
    void *stream;           /* 0x70 */
    char pad74[0x2078];
    u8   unk20EC[0x1C];
} Parser;

void fn_80138038(void *);
void *fn_8013E0F0(void *);
s8   fn_80137B30(void *, s32);
void fn_801373EC(void *, s32, s32);
s32  fn_8013F734(Parser *);
s32  fn_801399D8(s32, Ctx *);
void *fn_80137CB4(void *);
void fn_8013CC84(void *, s32, Desc *);

s32 fn_80139790(s32 arg0, Parser *arg1, s32 arg2) {
    Ctx ctx;
    u8 *p;
    s32 i;
    s32 res;
    s32 t;
    s32 y;

    fn_80138038(&ctx);
    p = arg1->pos;
    ctx.flags = arg2;
    ctx.stream = arg1->stream;
    ctx.dest = ctx.buf1;
    ctx.value = 0;
    ctx.owner = arg1;
    while (p < arg1->end) {
        u8 c;

        c = *p;
        p += 1;
        ctx.code = c;
        t = fn_80137B30(fn_8013E0F0(arg1->stream), ctx.code);
        y = ~t & 1;
        if (y) {
            u16 v;

            ctx.unkAD8 = *(u16 *)p;
            p += 2;
            ctx.value = ctx.unkAD8;
        }
        if (ctx.code == 7) {
            ctx.unkADA = p[5];
            fn_801373EC((char *)arg1 + 0x20EC, ctx.unkADA, ctx.value);
        }
        if (y) {
            if (ctx.value != 0) {
                memcpy(ctx.dest, p, ctx.value);
            }
        } else {
            memcpy(ctx.dest, p, 0x514);
        }
        if (fn_8013F734(arg1) != 0) {
            ctx.flags |= 1;
        }
        res = fn_801399D8(arg0, &ctx);
        if ((res == 0) || (res == 2)) {
            arg1->end = arg1->pos;
            return 2;
        }
        if (res == 3) {
            return 3;
        }
        if (ctx.code != 7) {
            fn_801373EC((char *)arg1 + 0x20EC, ctx.code, ctx.value);
        }
        p += ctx.value;
    }
    if (ctx.active != 0) {
        i = 0;
        while (i < ctx.count) {
            fn_80137CB4(&ctx.desc);
            ctx.tmp = ctx.arr[i].a;
            ctx.desc.unk4 = &ctx.tmp;
            ctx.desc.unk2 = 2;
            ctx.desc.unk0 = 8;
            fn_8013CC84(ctx.stream, *(s32 *)((char *)ctx.owner + 0x48), &ctx.desc);
            i += 1;
        }
    }
    arg1->end = arg1->pos;
    return 1;
}
