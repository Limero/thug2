// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081264-0x8008144C (488B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern const f32 lbl_80296294;

typedef struct Unk_80081264Tab Unk_80081264Tab;

typedef struct Unk_80081264Dst {
    char pad0x0[0x4];
    u16 unk0x4;
    char pad0x6[0x11];
    u8 unk0x17;
    s16 unk0x18;
    s16 unk0x1A;
    s16 unk0x1C;
    s16 unk0x1E;
} Unk_80081264Dst;

typedef struct {
    char pad0x0[0x4];
    s32 ent;       /* 0x4: pointer to the entry */
    char pad0x8[0x4];
    u16 baseIdx;   /* 0xC */
    char pad0xE[0x2];
    u8 unk0x10;
    u8 unk0x11;
    char pad0x12[0x6];
    s32 key;       /* 0x18 */
} Unk_80081264Entry;

typedef struct {
    char pad0x0[0x14];
    s32 mid;                /* 0x14: pointer to a holder */
} Unk_80081264Rec;

typedef struct {
    char pad0x0[0x4];
    Unk_80081264Entry *ent;  /* 0x4 */
} Unk_80081264Holder;

typedef struct Unk_80081264Mid Unk_80081264Mid;

struct Unk_80081264Mid {
    char pad0x0[0x54];
    struct Unk_80081264Tab *tab; /* 0x54 */
};

struct Unk_80081264Tab {
    char pad0x0[0x38];
    Unk_80081264Dst *dsts;  /* 0x38, 32-byte stride */
    char pad0x3C[0x1C];
    Unk_80081264Rec **arr;  /* 0x58, array of record pointers */
    char pad0x5C[0x2];
    u16 count;             /* 0x5E */
};

typedef struct {
    char pad0x0[0x30];
    Unk_80081264Mid *m;     /* 0x30 */
} Unk_80081264Root;

typedef struct {
    f32 f0;
    f32 f4;
    char pad0x8[0x28];
    f32 f30;
    f32 f34;
} Unk_80081264Arg3;

bool fn_80081264(Unk_80081264Root *arg0, s32 arg1, s32 arg2, Unk_80081264Arg3 *arg3) {
    s32 i;
    f32 scale;
    Unk_80081264Entry *e;
    s32 slot;
    s32 found;

    if (arg0->m == NULL) {
        return true;
    }
    if (arg0->m->tab == NULL) {
        return true;
    }
    for (i = 0; i < arg0->m->tab->count; i++) {
        scale = lbl_80296294;
        e = ((Unk_80081264Holder *)arg0->m->tab->arr[i]->mid)->ent;
        if (e == NULL) {
            continue;
        }
        found = 0;
        slot = arg2;
        if (e->key == arg1) {
            found = 1;
        } else if ((u32) e->key > (u32) arg1) {
            u32 d = e->key - arg1;
            if (d <= 0x7FU) {
                u32 byte = d >> 3U;
                u32 bit = d & 7;
                if (bit != 0) {
                    if (bit == (u32) arg2 + 1) {
                        found = 1;
                        slot = 0;
                    }
                } else if ((byte != 0) && (byte & (1U << arg2))) {
                    s32 j;
                    found = 1;
                    j = 0;
                    if (j < slot) {
                        do {
                            if (!(byte & (1U << j))) {
                                slot -= 1;
                            }
                            j += 1;
                        } while (j < arg2);
                    }
                }
            }
        }
        if ((found != 0) && (slot < (s32) *(u8 *)((char *)e + 0x4))) {
            Unk_80081264Dst *dst;
            dst = arg0->m->tab->dsts + (e->baseIdx + slot);
            dst->unk0x17 = 1;
            dst->unk0x4 = (u16) (dst->unk0x4 | 4);
            *(u8 *)((char *)e + 0x6) = (u8) (*(u8 *)((char *)e + 0x6) | 0x10);
            dst->unk0x18 = (s16) (arg3->f0 * scale);
            dst->unk0x1A = (s16) (arg3->f4 * scale);
            dst->unk0x1C = (s16) (arg3->f30 * scale);
            dst->unk0x1E = (s16) (arg3->f34 * scale);
        }
    }
    return true;
}
