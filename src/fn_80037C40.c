// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80037C40-0x80037CF4 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

/* 1.0f pool entry at .rodata2:0x80291EF0 (lbl_80291EE8..F0C is the 1.0f/0.0f
 * block the callers broadcast into their 16-byte scratch). */
extern f32 lbl_80291EF0;

/* 0x20-byte lookup entry: +0x08 is the packed state word, +0x10/+0x18 the two
 * PS slots the caller's 16-byte vector is copied into. */
typedef struct {
    char pad0x00[8];
    u32 state;
    u32 pad0x0C;
    __ps_t v[2];
} Entry;

/* the caller's 16-byte scratch: read as 3 floats for the guard tests and as
 * two PS slots for the copy (fn_800379CC fills i[0..3] with the 1.0f word). */
typedef union {
    struct {
        f32 f[4];
        s32 i[4];
    } s;
    __ps_t ps[2];
} XVec4;

extern void *fn_80036328(void *arg0, s32 arg1);

s32 fn_80037C40(void *arg0, s32 arg1, XVec4 *arg2, s32 arg3) {
    Entry *p = (Entry *)fn_80036328(arg0, arg1);

    if (p != NULL) {
        f32 one = lbl_80291EF0;
        s32 all = 0;

        p->v[0] = arg2->ps[0];
        p->v[1] = arg2->ps[1];
        if (arg2->s.f[0] == one && arg2->s.f[1] == one) {
            all = (arg2->s.f[2] == one);
        }
        p->state &= 0xCFFFFFFF;
        if (all == 0) {
            u32 n = p->state | 0x10000000;
            if (arg3) {
                n = p->state | 0x20000000;
            }
            p->state = n;
        }
    }
    return p != NULL;
}
