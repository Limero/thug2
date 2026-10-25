// WIP DRAFT (non-matching) — hand-rebuilt 2026-10-06 from the
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 11.2444% -> 11.9940% `volatile` keyword(s) removed from the body
// want disassembly.  Replaces the m2c bulk-fill body (measured 7.8%).
// family=m2c range=0x80097E48-0x800988B4 size=2668B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// 2026-09-22 literal->symbol substitution: 7.6 -> 7.8 (symbol for 0x800966D8)
//
// WHAT THIS PASS FIXED (all read off the want, none of it scheduling):
//  1. FRAME. The want's frame is 0x2f98 with locals 0x20..0x2f48.  The m2c body
//     declared the 12-byte-record array as a 4-byte `s32 *sp48`, so it had no
//     array at all and therefore a completely different frame/offset set.  The
//     want's local area is exactly: out-param words @0x08..0x1c, `sp20` @0x20,
//     8-float projection @0x28 (fields read at 0x3c=+0x14 and 0x40=+0x18),
//     12-byte-record array @0x48..0x2f27 (0x2ee0 bytes = 1000 * 0xc), then the
//     six `sp2F2*`..`sp2F3C` out-params @0x2f28..0x2f47.  The array is declared
//     `Elem arr[1000]` here because the qsort width is 0xc and the region size
//     divides exactly by 12 (0x2ee0 / 12 == 1000).  Declared in ascending
//     address order, matching the measured layout in tools' fn_80085394 draft.
//  2. STACK ARGS.  The m2c body faked the outgoing parameter words with
//     file-scope `static s32 sp8/spC/sp10/sp14`/local pointer casts.  They are
//     ordinary 9th+ arguments (this compiler places them at SP+8, SP+0xc, ...),
//     so the helpers now carry real prototypes/arg counts: fn_8001E4E8 takes
//     10 args, fn_8001E3CC 12, fn_8001EA14 16 (8 int + 3 float + 5 stack) and
//     fn_80097500 13.  All the `(s32 *)1`-style casts are gone.
//  3. The projection is a struct local (`Proj_t`, the fn_80085394 convention),
//     so `sp3C`/`sp40` (which were file-scope statics — i.e. .bss accesses where
//     the want has `lfs 0x3c(r1)`/`0x40(r1)`) are now `sp28.f14`/`sp28.f18`.
//  4. GX light FIFO: want is stb 0x10 / sth 0 / sth 0x1025 / stfs through
//     `lbl_CC008000` (lis 0xCC01 + -0x8000(rX) displacement form).  The m2c body
//     wrote four *u8* stores.  Same recipe as the promoted fn_8001DC5C.
//  5. Two indirect fn-pointer casts (`((s32 (*)(...))0x8025E60C)` etc., which
//     compile to lis/addi/mtlr/blrl) are now direct `bl C_MTXLightOrtho` /
//     `bl PSMTXConcat` calls with their real symbol names.
//  6. Literal addresses 0x803016B8 / 0x80301700 / 0x8037B6A4 / 0x8037B7D8 are
//     symbol references; the `*(f32 *)(lbl_8037B7D8 + 4) > it->unk0xC` test was
//     an *integer* compare in the m2c body but is `lfs`+`fcmpu` (float) in the
//     want.
//  7. Field types: obj->unk0x5E/0x60/0x62/0x64/0x66 and item->unk0x4 are `lhz`
//     (u16) in the want, item->unk0xC is `lfs` (f32) — the shared mega-structs
//     made all of those 32-bit, which costs one wrong word each time.
//  8. The last loop's second `fn_80097500` call passed `arg0` in the item slot
//     (extra argument) instead of the list item.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* The display-list owner.  unk0x0 = display list byte count (also the second
   argument of fn_80099B10), unk0x4 = flags, unk0xC = f32 distance. */
typedef struct Sub {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    f32 unk0x10;         /* vector/position block handed to fn_80096BE8 */
    char pad0x14[0x20];
    void *unk0x34;       /* passed straight to fn_80020514 */
    s32 unk0x38;         /* 0xc-stride record index */
    char pad0x3C[4];
    char unk0x40[4];     /* GX display list (unk0x0 bytes long) */
} Sub;

typedef struct Item {
    s32 unk0x0;
    u16 unk0x4;          /* lhz 4(rX) — flags */
    u16 unk0x6;
    s32 unk0x8;
    f32 unk0xC;          /* lfs 0xc(rX) — distance */
    s32 unk0x10;
    Sub *unk0x14;
} Item;

/* qsort/callback record: 12-byte stride (fn_8026A07C width 0xc). */
typedef struct {
    void *item;
    f32 key;
    s32 pad;
} Elem;

/* GX projection matrix local: 8 floats; the light block reads +0x14/+0x18. */
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
} Proj_t;

/* The object (arg0): offsets taken from the want. */
typedef struct {
    s32 unk0x0;
    char pad0x4[8];
    u8 *unk0xC;          /* 0xc-stride record array */
    u8 *unk0x10;
    u8 *unk0x14;
    u8 *unk0x18;
    char pad0x1C[0x14];
    s32 unk0x30;
    char pad0x34[0x24];
    Item **unk0x58;      /* item list */
    char pad0x5C[2];
    u16 unk0x5E;
    u16 unk0x60;
    u16 unk0x62;
    u16 unk0x64;
    u16 unk0x66;
} Obj_t;

extern char fn_800966D8[];
extern char lbl_CC008000[];
extern bool lbl_80301898;
extern s32 lbl_80301888;
extern s32 lbl_80301894;
extern s32 lbl_8030187C;
extern s32 lbl_803016B0;
extern bool lbl_803016B4;
extern s32 lbl_803016BC;
extern s32 lbl_803016D4;
extern void *lbl_803016B8;
extern char lbl_80301700[];
extern char lbl_8037B6A4[];
extern f32 lbl_8037B7D8[];
extern f32 lbl_802974E4;
extern f32 lbl_802974E8;
extern f32 lbl_802974EC;
extern f32 lbl_802974F0;
extern f32 lbl_802974F4;

void fn_80099B10(void *, s32, s32, void *, void *);
void fn_800971A0(void *);
void fn_80097398(void);
void fn_8006EC14(void);
void fn_8006EB68(s32);
void fn_80020514(s32, void *, s32);
void fn_8001EFBC(s32, s32 *);
void fn_8001EF84(s32, s32 *);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void SetBlendMode(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E5DC(s32, s32, s32, s32, s32);
void fn_8001E66C(s32, s32 *);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001FA54(s32, s32, s32, s32, s32);
void fn_8001EA14(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32,
                 s32, s32, s32, s32, s32);
void fn_8001EDE0(s32, s32, s32, s32);
void fn_8001ECB0(void *, s32, s32, s32);
void fn_8001F91C(void *, s32, s32);
void fn_8001FEC0(s32);
s32 fn_80096BE8(void *, void *);
f32 fn_8009666C(void *);
void fn_8026A07C(void *, s32, s32, void *);
void GX_GetProjectionv(void *);
void GX_SetProjectionv(void *);
void GX_SetZMode(s32, s32, s32);
void GX_CallDisplayList(void *, s32);
void C_MTXLightOrtho(void *, f32, f32, f32, f32, f32, f32, f32, f32);
void PSMTXConcat(void *, void *, void *);
void fn_80097500(void *, Item *, u8 *, void *, void *, s32 *, s32 *, s32 *,
                 Proj_t *, s32 *, s32 *, s32 *, s32);

void fn_80097E48(Obj_t *arg0, u8 *arg1, s32 arg2, void *arg3, void *arg4) {
    s32 sp20;
    Proj_t sp28;
    Elem arr[1000];
    s32 sp2F28;
    s32 sp2F2C;
    s32 sp2F30;
    s32 sp2F34;
    s32 sp2F38;
    s32 sp2F3C;
    s32 temp;
    s32 i;
    s32 off;
    s32 keep;
    s32 n0;
    s32 n1;
    s32 n2;
    s32 n3;
    Item *it;
    Sub *sub;
    Elem *e;

    temp = arg0->unk0x0;
    if (temp == 0) {
        lbl_80301898 = 1;
        lbl_80301888 = temp;
        lbl_80301894 = temp;
        lbl_8030187C = temp;
        fn_80099B10(arg0, temp, arg2, arg3, arg4);
        fn_800971A0(arg0);
        if (arg1 != NULL) {
            fn_80020514(9, arg1, 0xC);
            fn_80020514(0xA, arg1 + 6, 0xC);
        } else {
            fn_80020514(9, arg0->unk0xC, 0xC);
            fn_80020514(0xA, arg0->unk0x10, 6);
        }
        sp2F2C = 2;
        sp2F30 = -1;
        sp2F28 = 0;
        sp2F38 = 0;
        sp2F34 = 0;
        sp2F3C = 1;
        fn_8006EC14();
        sp20 = sp2F34;
        fn_8001EFBC(4, &sp20);
        sp20 = sp2F34;
        fn_8001EFBC(5, &sp20);
        GX_GetProjectionv(&sp28);
        fn_80020514(0xB, arg0->unk0x14, 4);
        fn_80020514(0xC, arg0->unk0x14 + 2, 4);
        fn_80020514(0xD, arg0->unk0x18, 4);
        fn_80020514(0xE, arg0->unk0x18, 4);
        fn_80020514(0xF, arg0->unk0x18, 4);
        fn_80020514(0x10, arg0->unk0x18, 4);
        if (lbl_803016B0 == lbl_803016B4) {
            lbl_803016B8 = arg0;
        }
        if (arg2 & 0x10) {
            i = 0;
            off = 0;
            fn_8001E2FC(0, 0xFF, 0xFF, 4, 0xFF, 0xFF, 4);
            fn_8001E4E8(0, 0xF, 0xF, 0xF, 0xE, 0, 0, 0, 1, 0);
            fn_8001E3CC(0, 7, 7, 7, 6, 0, 0, 0, 1, 0, 0, 0);
            SetBlendMode(0, 1, 1, 0, 1, 0, 1);
            fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
            sp20 = QB_COLOR_GRAY64;
            fn_8001E66C(0, &sp20);
            fn_8001E248(2, 0, 0, 0, 0, 0, 2);
            sp20 = -1;
            fn_8001EFBC(4, &sp20);
            sp20 = -1;
            fn_8001EF84(4, &sp20);
            sp20 = -1;
            fn_8001EFBC(5, &sp20);
            sp20 = -1;
            fn_8001EF84(5, &sp20);
            sp2F34 = -1;
            fn_8001EEE0(0, 1, 1, 0, 0);
            while (i < arg0->unk0x5E) {
                it = *(Item **)((char *)arg0->unk0x58 + off);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && ((lbl_803016B0 != lbl_803016B4) ||
                    (arg0->unk0x30 + (lbl_803016BC << 5)) != sub->unk0x4)) {
                    GX_CallDisplayList(sub->unk0x40, sub->unk0x0);
                }
                i++;
                off += 4;
            }
        }
        fn_80097398();
        if (arg2 & 1) {
            i = 0;
            off = 0;
            while (i < arg0->unk0x60) {
                it = *(Item **)((char *)arg0->unk0x58 + off);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && ((lbl_803016B0 != lbl_803016B4) ||
                    (arg0->unk0x30 + (lbl_803016BC << 5)) != sub->unk0x4)) {
                    fn_80097500(arg0, it, arg1, arg3, arg4, &sp2F28, &sp2F2C,
                                &sp2F30, &sp28, &sp2F34, &sp2F38, &sp2F3C, arg2);
                }
                i++;
                off += 4;
            }
        }
        if (arg2 & 2) {
            n0 = arg0->unk0x60;
            n1 = n0 + arg0->unk0x62;
            n2 = n1 + arg0->unk0x64;
            n3 = n2 + arg0->unk0x66;
            fn_80097398();
            for (i = n0; i < n1; i++) {
                it = *(Item **)((char *)arg0->unk0x58 + i * 4);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && ((lbl_803016B0 != lbl_803016B4) ||
                    (arg0->unk0x30 + (lbl_803016BC << 5)) != sub->unk0x4)) {
                    fn_80097500(arg0, it, arg1, arg3, arg4, &sp2F28, &sp2F2C,
                                &sp2F30, &sp28, &sp2F34, &sp2F38, &sp2F3C, arg2);
                }
            }
            keep = 0;
            for (i = n1; i < n2; i++) {
                it = *(Item **)((char *)arg0->unk0x58 + i * 4);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && ((lbl_803016B0 != lbl_803016B4) ||
                    (arg0->unk0x30 + (lbl_803016BC << 5)) != sub->unk0x4)) {
                    arr[keep].item = it;
                    keep++;
                    arr[keep - 1].key = fn_8009666C(&sub->unk0x10);
                }
            }
            fn_8026A07C(arr, keep, 0xC, fn_800966D8);
            fn_80097398();
            e = arr;
            for (i = 0; i < keep; i++) {
                fn_80097500(arg0, e->item, arg1, arg3, arg4, &sp2F28, &sp2F2C,
                            &sp2F30, &sp28, &sp2F34, &sp2F38, &sp2F3C, arg2);
                e++;
            }
            fn_80097398();
            for (i = n2; i < n3; i++) {
                it = *(Item **)((char *)arg0->unk0x58 + i * 4);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && ((lbl_803016B0 != lbl_803016B4) ||
                    (arg0->unk0x30 + (lbl_803016BC << 5)) != sub->unk0x4)) {
                    fn_80097500(arg0, it, arg1, arg3, arg4, &sp2F28, &sp2F2C,
                                &sp2F30, &sp28, &sp2F34, &sp2F38, &sp2F3C, arg2);
                }
            }
        }
        if (arg2 & 0x20) {
            fn_8006EB68(0);
            C_MTXLightOrtho(arr, lbl_802974E4, lbl_802974E8, lbl_802974E4,
                            lbl_802974E8, lbl_802974EC, lbl_802974EC,
                            lbl_802974EC, lbl_802974EC);
            PSMTXConcat(arr, lbl_8037B6A4, arr);
            fn_8001F91C(arr, 0x33, 0);
            GX_SetZMode(1, 3, 0);
            fn_8001FEC0(1);
            fn_8001EA14(lbl_803016D4, 0x80, 0x80, 0, 0, 0, 0, 1, lbl_802974F0,
                        lbl_802974F0, lbl_802974F0, 1, 0, 1, 0, 0);
            fn_8001EDE0(0, 1, 0x80, 0x80);
            fn_8001ECB0(lbl_80301700, 2, 1, 0);
            fn_8001EEE0(1, 0, 1, 0, 0);
            fn_8001E6F0(0, 0, 0, 0, 0x7D);
            fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
            fn_8001FA54(7, 0, 0, 7, 0);
            SetBlendMode(1, 2, 0, 0, 1, 0, 1);
            fn_8001FAA4(0, 0x33, 0x33, 0x33, 0x33);
            fn_8001E2FC(0, 0, 0, 0xFF, 0, 0xFF, 0xFF);
            fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0);
            fn_8001E4E8(0, 0xC, 0xF, 8, 0xF, 0, 0, 0, 0, 0);
            fn_8001F2D8(arg0, arg1, 2, 9, 1, 0xD, 1);
            *(u8 *)&lbl_CC008000 = 0x10;
            *(u16 *)&lbl_CC008000 = 0;
            *(u16 *)&lbl_CC008000 = 0x1025;
            *(f32 *)&lbl_CC008000 = sp28.f14 * lbl_802974F4 + sp28.f18;
            sp2F30 = 5;
            i = 0;
            off = 0;
            while (i < arg0->unk0x5E) {
                it = *(Item **)((char *)arg0->unk0x58 + off);
                sub = it->unk0x14;
                if ((it->unk0x4 & 8) && fn_80096BE8(arr, &sub->unk0x10) &&
                    (lbl_8037B7D8[1] > it->unk0xC) && !(it->unk0x4 & 0x80)) {
                    if (sub->unk0x34 != NULL) {
                        sp2F28 = -1;
                        fn_80020514(9, sub->unk0x34, 0xC);
                    } else if (sub->unk0x38 != sp2F28) {
                        sp2F28 = sub->unk0x38;
                        fn_80020514(9, arg0->unk0xC + sub->unk0x38 * 0xC, 0xC);
                    }
                    GX_CallDisplayList(sub->unk0x40, sub->unk0x0);
                }
                i++;
                off += 4;
            }
            fn_8006EB68(1);
            sp2F3C = 1;
        }
        GX_SetProjectionv(&sp28);
        lbl_803016B0 = lbl_803016B0 + 1;
    }
}

// NOTE / PARKED 2026-10-06: structure+types rebuilt from the
// want; still unverified (no compiler here), so treat the score as unmeasured.
// Remaining known gaps, in the order I would attack them:
//   a. Local declaration order: this body declares the locals in ASCENDING
//      address order (sp20, sp28, arr, sp2F28..sp2F3C) because the measured
//      fn_80085394 draft reports that order reproducing its retail offsets.
//      If ngccc allocates descending instead, every offset here flips — that is
//      the single cheapest A/B to run (swap the two groups).
//   b. The outgoing-argument model (item 2 in the header) is the biggest
//      behavioural bet: it assumes this compiler puts the 9th+ argument at
//      SP+8/SP+0xc.  If the want's `stw r29,8(r1)`/`stw r31,0xc(r1)` words come
//      back missing, fall back to modelling them as the previous draft did
//      (writes to two locals at 8/0xc) — but NOT as file-scope statics.
//   c. `item` is still passed to fn_80097500 as `Item *`; the want only ever
//      forwards it, so any pointer type works — but if ngccc's allocator
//      differs, try `void *`.
//   d. fn_8001F2D8 stays UNPROTOTYPED on purpose: the want has exactly one
//      `crclr cr1eq`, before that one call (same finding as fn_80085394).
//   e. Everything about the GX/TEV helper arg counts is read off the want's
//      li/stack-store sequence; if a callee's real prototype has fewer args the
//      extra `li`s will show up as residual diff.
//   f. `lbl_802974F4` is really `float[16]` in src/r2d_80297304.c but only
//      element 0 (=750.0f) is used, so the scalar extern keeps the same codegen
//      as the other pool floats.
// This function was 7.8% as an m2c body; the frame/array recovery alone should
// move the masked score substantially, because it is what makes the prologue,
// epilogue and every stack offset line up at all.
