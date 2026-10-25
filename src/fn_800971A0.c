// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800971A0-0x80097398 (504B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_803016A0;
extern bool lbl_803018B8;
extern bool lbl_803018BC;
s32 fn_800145AC(void);

typedef struct {
    u8 r, g, b, a;
} TrackColor;

typedef struct {
    s32 time;
    u8 r, g, b, a;
} TrackKey;

typedef struct {
    s32 count;
    s32 seed;
    TrackKey keys[1];
} TrackSet;

typedef struct {
    char pad0x0[0x1A];
    u16 count;
    char pad0x1C[0x8];
    s32 stamp;
} Track;

typedef struct {
    char pad0x0[0x8];
    Track *track;
    char pad0xC[0x8];
    u32 *colors;
    char pad0x18[0x10];
    TrackSet *sets;
} TrackOwner;

void fn_800971A0(TrackOwner *self) {
    TrackSet *set;
    TrackKey *key;
    TrackColor col;
    u32 *colors;
    s32 i;
    s32 rnd;
    s32 n;
    s32 seed;
    s32 lo;
    s32 hi;
    s32 span;
    s32 val;
    s32 j;
    s32 f;

    if (lbl_803018B8 != 0) {
        return;
    }
    if (self->track == NULL) {
        return;
    }
    if (self->track->count == 0) {
        return;
    }
    set = self->sets;
    key = set->keys;
    rnd = fn_800145AC();
    colors = self->colors;
    if (lbl_803018BC == 0 && self->track->stamp == lbl_803016A0) {
        return;
    }
    for (i = 0; i < self->track->count; i++) {
        n = set->count;
        seed = set->seed;
        lo = key[0].time;
        hi = key[n - 1].time;
        span = hi - lo;
        if (span != 0) {
            val = lo + (rnd + seed) % span;
            if (val < lo) {
                val = lo;
            }
            if (val > hi) {
                val = hi;
            }
            for (j = n - 1; j >= 0 && val < key[j].time; j--) {
            }
            f = ((val - key[j].time) * 255) / (key[j + 1].time - key[j].time);
            col.r = key[j].r + ((key[j + 1].r - key[j].r) * f >> 8);
            col.g = key[j].g + ((key[j + 1].g - key[j].g) * f >> 8);
            col.b = key[j].b + ((key[j + 1].b - key[j].b) * f >> 8);
            col.a = key[j].a + ((key[j + 1].a - key[j].a) * f >> 8);
            colors[i] = *(u32 *)&col;
        }
        set = (TrackSet *)(key + n);
        key = set->keys;
        self->track->stamp = lbl_803016A0;
    }
}
