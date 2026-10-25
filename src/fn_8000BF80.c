// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000BF80-0x8000C394 (1044B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* lbl_80312434 is a 4-entry table of 12-byte entries (stride 0xC); the sibling
 * byte-identical fn_8000C410 indexes it exactly this way.  Entry layout read
 * straight off the DOL:  +0x0 u16 flags word, +0x2/+0x3/+0x4/+0x5 s8 (the four
 * that go through the (f32)(f64) int->float path), +0x6/+0x7 u8 (compared
 * UNSIGNED against 0x80 -> cmplwi/ble), +0x8/+0x9 u8 (copied verbatim into the
 * object), +0xA s8 (== -1 selects the disabled path). */
typedef struct BF80Entry {
    u16 flags;
    s8 a2;
    s8 a3;
    s8 a4;
    s8 a5;
    u8 b6;
    u8 b7;
    u8 b8;
    u8 b9;
    s8 bA;
    char pad0xB[1];
} BF80Entry;

/* The receiver: +0x10 is the table index, +0x18 and +0xE8 are word flags, and
 * +0x20..+0x34 is a dense 21-byte control-point block written entirely with
 * stb (so every field there is a byte, not a word). */
typedef struct BF80Obj {
    char pad0x0[0x10];
    s32 idx;
    char pad0x14[0x4];
    s32 f18;
    char pad0x1C[0x4];
    u8 c20;
    u8 c21;
    u8 c22;
    u8 c23;
    s8 c24;
    s8 c25;
    s8 c26;
    s8 c27;
    u8 c28;
    u8 c29;
    u8 c2A;
    u8 c2B;
    u8 c2C;
    u8 c2D;
    u8 c2E;
    u8 c2F;
    u8 c30;
    u8 c31;
    u8 c32;
    u8 c33;
    u8 c34;
    char pad0x35[0xB3];
    s32 fE8;
} BF80Obj;

extern char lbl_80312434[];
void fn_8000C5A4(BF80Obj *);
void fn_8000C5CC(void);
void fn_8000BF80(BF80Obj *arg0) {
    s32 entry_off;
    s32 cv5;
    s32 cv4;
    s32 cv2;
    s32 cv3;
    u8 t22;
    u8 t23;
    u8 t800;
    u8 t400;
    u8 t7;
    register u8 base22 __asm__("r9"); /* 2026-10-08: doc-75 pin */
    register s32 acc2pin __asm__("r9");
    u8 acc3;
    u8 acc4;
    u8 t1;
    u8 t6;
    u8 t8;
    u8 t2;
    u8 t4;
    BF80Entry *ent;
    u16 *tab;

    entry_off = arg0->idx * 0xC;
    tab = (u16 *)(entry_off + (s32)lbl_80312434);
    ent = (BF80Entry *)tab;
    if (ent->bA == -1) {
        arg0->fE8 = 0;
        arg0->f18 = 0;
        fn_8000C5CC();
        fn_8000C5A4(arg0);
        return;
    }

    arg0->f18 = 1;
    arg0->fE8 = 1;
    arg0->c20 = 0;
    arg0->c21 = 0x70;
    arg0->c22 = 0xFF;
    arg0->c23 = 0xFF;

    t22 = 0xFF;
    if ((tab[0] & 0x1010) == 0x1000) {
        t22 = 0xF7;
    }
    arg0->c22 = t22;
    if (tab[0] & 0x10) {
        arg0->c22 = t22 ^ 1;
    }

    t23 = arg0->c23;
    if (tab[0] & 0x800) {
        t23 ^= 0x10;
    }
    arg0->c23 = t23;
    if (tab[0] & 0x400) {
        t23 ^= 0x20;
    }
    arg0->c23 = t23;
    if (tab[0] & 0x100) {
        t23 ^= 0x40;
    }
    arg0->c23 = t23;
    if (tab[0] & 0x200) {
        t23 ^= 0x80;
    }
    arg0->c23 = t23;
    if (ent->b6 > 0x80U) {
        t23 ^= 4;
    }
    arg0->c23 = t23;
    if (ent->b7 > 0x80U) {
        t23 ^= 8;
    }
    arg0->c23 = t23;

    arg0->c34 = 0;
    if (tab[0] & 0x10) {
        arg0->c34 = 4;
    }

    t800 = 0;
    if (tab[0] & 0x800) {
        t800 = 0xFF;
    }
    arg0->c2C = t800;
    t400 = 0;
    if (tab[0] & 0x400) {
        t400 = 0xFF;
    }
    arg0->c2D = t400;
    t6 = 0;
    arg0->c2E = ent->b8;
    arg0->c2F = ent->b9;
    if (ent->b6 > 0x80U) {
        t6 = 0xFF;
    }
    arg0->c30 = t6;
    t7 = 0;
    if (ent->b7 > 0x80U) {
        t7 = 0xFF;
    }
    arg0->c31 = t7;

    arg0->c32 = 0;
    arg0->c33 = 0;
    arg0->c28 = 0;
    arg0->c29 = 0;
    arg0->c2A = 0;
    arg0->c2B = 0;

    base22 = arg0->c22;
    if (tab[0] & 8) {
        base22 ^= 0x10;
    }
    arg0->c22 = base22;
    t8 = 0;
    if (tab[0] & 8) {
        t8 = 0xFF;
    }
    arg0->c2A = t8;
    acc2pin = base22;
    if (tab[0] & 2) {
        acc2pin ^= 0x20;
    }
    arg0->c22 = acc2pin;
    t2 = 0;
    if (tab[0] & 2) {
        t2 = 0xFF;
    }
    arg0->c28 = t2;
    acc3 = acc2pin & 0xff;
    if (tab[0] & 4) {
        acc3 ^= 0x40;
    }
    arg0->c22 = acc3;
    t4 = 0;
    if (tab[0] & 4) {
        t4 = 0xFF;
    }
    arg0->c2B = t4;
    acc4 = (u8)(s8) acc3;
    if (tab[0] & 1) {
        acc4 ^= 0x80;
    }
    arg0->c22 = acc4;
    t1 = 0;
    if (tab[0] & 1) {
        t1 = 0xFF;
    }
    arg0->c29 = t1;

    cv2 = (s32) (2.0f * (f32) (f64) ent->a2);
    cv3 = (s32) (2.0f * (f32) (f64) ent->a3);
    if (cv2 < -0x80) {
        cv2 = -0x80;
    }
    if (cv2 > 0x7F) {
        cv2 = 0x7F;
    }
    if (cv3 < -0x80) {
        cv3 = -0x80;
    }
    if (cv3 > 0x7F) {
        cv3 = 0x7F;
    }
    cv4 = (s32) (2.0f * (f32) (f64) ent->a4);
    cv5 = (s32) (2.0f * (f32) (f64) ent->a5);
    if (cv4 < -0x80) {
        cv4 = -0x80;
    }
    if (cv4 > 0x7F) {
        cv4 = 0x7F;
    }
    if (cv5 < -0x80) {
        cv5 = -0x80;
    }
    if (cv5 > 0x7F) {
        cv5 = 0x7F;
    }
    arg0->c24 = (s8) (cv4 - 0x80);
    arg0->c25 = (s8) (0x7F - cv5);
    arg0->c26 = (s8) (cv2 - 0x80);
    arg0->c27 = (s8) (0x7F - cv3);
}
