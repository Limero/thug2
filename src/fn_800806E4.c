// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800806E4-0x8008076C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct V_806E4 {
    char pad0x0[0x4];
    u16 f4;            /* +0x04, bit 0x40 gates the fast path */
    char pad0x6[0x0E];
    void *f14;         /* +0x14 */
} V_806E4;

typedef struct O_806E4 {
    char pad0x0[0x18];
    void *f18;         /* +0x18, null short-circuits to 0 */
    char pad0x1C[0x4];
    void **f20;        /* +0x20, pointer to the V */
} O_806E4;

void *fn_8007DF14(void *);
u16 fn_80080538(void *, s32 *, s32 *);
void fn_8007E89C(void);

// fn_800806E4: fast path returns a u16 out of a flag-gated view; otherwise
// runs the full fn_80080538 query (with two 0x2710-byte out buffers), then a
// 0-arg housekeeping call, and returns the query's u16 result.
u16 fn_800806E4(O_806E4 *arg0) {
    s32 sp8[0x9C4];
    s32 sp2718[0x9C4];
    void *t;
    V_806E4 *v;
    u16 r;

    t = arg0->f18;
    if (t == NULL) {
        return 0;
    }
    t = fn_8007DF14(t);
    if (*(s32 *)((char *)t + 8) != 0) {
        v = arg0->f20[0];
        if ((v->f4 & 0x40) != 0) {
            return *(u16 *)((char *)v->f14 + 0x28);
        }
    }
    r = fn_80080538(arg0, sp8, sp2718);
    fn_8007E89C();
    return r;
}
