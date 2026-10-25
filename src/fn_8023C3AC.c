// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C3AC-0x8023C52C (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// 0x802B0E64 / 0x802B0E68 are `float lbl_802B0E64[1]`/`lbl_802B0E68[1]` in
// src/r2d_802B0E50.c (.rodata2): 0.0f and 1.0f.  The `[1]` is load-bearing, not
// cosmetic — see note 6 in the header.
extern f32 lbl_802B0E64[1];
extern f32 lbl_802B0E68[1];

void fn_80240B0C(void *, s32, s32, s32, s32, s32, s32);
void *fn_80238964(void);
void *fn_8023897C(void *, s32, s32 *);
void fn_8023EC64(void *, s32);

typedef struct { f32 x, y, z, w; } Vec;
typedef struct { s32 w; u16 h; char pad[2]; } Reg;   /* pad: sizeof must be 8 */
typedef struct { char d[6]; } Six;                    /* opaque 6-byte record */
typedef struct { s32 lo; s32 hi; } Ent;
/* fn_8023897C returns a record at world+0x10770+idx*0x154: an 8-byte-stride
   table at +8 plus a slot index at +0x14C. `ents[1]` (array, not pointer) so
   the +8 stays address arithmetic. */
typedef struct { s32 pad0; char pad4[4]; Ent ents[1]; char padC[0x13C]; s32 idx; } Rec;
typedef struct {
    void *unk0x0;        /* renderer handle: fn_80238964() */
    Reg unk0x4;          /* {w,h} viewport, cleared by fn_80240B0C */
    f32 unk0xC;          /* set to 1.0f */
    char pad0x10[0x8];
    Vec unk0x18;         /* (0,0,0,1) */
    Vec unk0x28;         /* (0,0,0,1) */
    char pad0x38[0x4];
    s32 unk0x3C;         /* flags (bit 0 read by fn_8023EC64) */
    f32 unk0x40;         /* degrees */
    f32 unk0x44;
    s32 unk0x48;         /* fn_8023EC64 result slot */
    u8 unk0x4C;
    Six unk0x4D[2];      /* two 6-byte records, +6 stride */
    char pad0x59[0x3];
    s32 unk0x5C;
    s32 unk0x60;
    s32 unk0x64;
    char pad0x68[0x4];
    s32 unk0x6C;         /* fn_8023897C slot index */
    s32 unk0x70;         /* fn_8023897C out-count */
    s32 unk0x74;
    Six unk0x78[2];      /* two more 6-byte records */
    char pad0x84[0x3C];
    s32 unk0xC0;         /* 0/1 flag, also read by fn_8023CE8C/fn_8023D184 */
    char pad0xC4[0x4];
    s32 unk0xC8;
    s32 unk0xCC;
} Obj;

void *fn_8023C3AC(Obj *arg0) {
    Vec *v0;
    Vec *v1;
    Six *p;
    u32 i;               /* u32, not s32 — see note 1 above */
    f32 one;             /* 1.0f, read once — see note 6 */
    f32 zero;            /* 0.0f, read once — see note 6 */
    Rec *rec;
    void *mgr;

    fn_80240B0C(&arg0->unk0x4, 0, 0, 0, 0, 0, 0);
    p = &arg0->unk0x4D[0];
    v0 = &arg0->unk0x18;
    v1 = &arg0->unk0x28;
    zero = lbl_802B0E64[0];
    arg0->unk0x18.x = zero;
    v0->y = zero;
    v0->z = zero;
    one = lbl_802B0E68[0];
    v0->w = one;
    arg0->unk0x28.x = zero;
    v1->w = one;
    v1->z = zero;
    v1->y = zero;
    arg0->unk0x3C = 0;
    arg0->unk0x40 = zero;
    arg0->unk0x44 = zero;
    arg0->unk0x48 = 0;
    i = 1;
    do {
        Six *q = p;
        p++;
        fn_80240B0C(q, 0, 0, 0, 0, 0, 0);
    } while (i-- != 0);
    p = &arg0->unk0x78[0];
    i = 1;
    do {
        Six *q = p;
        p++;
        fn_80240B0C(q, 0, 0, 0, 0, 0, 0);
    } while (i-- != 0);
    arg0->unk0xC = lbl_802B0E68[0];
    arg0->unk0x4C = 0;
    arg0->unk0x5C = 0;
    arg0->unk0x60 = 0;
    arg0->unk0x64 = 0;
    arg0->unk0x6C = 0;
    arg0->unk0x70 = 0;
    arg0->unk0xC0 = 0;
    arg0->unk0xC8 = 0;
    arg0->unk0x74 = 0;
    mgr = fn_80238964();
    arg0->unk0x0 = mgr;
    rec = fn_8023897C(mgr, arg0->unk0x6C, &arg0->unk0x70);
    fn_8023EC64(arg0, rec->ents[rec->idx].lo);
    arg0->unk0xCC = 1;
    return arg0;
}
