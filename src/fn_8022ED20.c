// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022ED20-0x8022EDDC (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_802B0610;
extern __ps_t lbl_802B04F8[];

typedef struct {
    __ps_t xy;
    __ps_t zw;
} Pair16;

typedef struct INode {
    char pad0x00[0x10];
    __ps_t xy;
    __ps_t zw;
    char pad0x20[0x14];
    struct INode *next;
} INode;

typedef struct Outer {
    char pad0x00[0x10];
    INode *head;
    char pad0x14[0x8];
    struct Outer *next;
} Outer;

typedef struct {
    char pad0x00[0x60];
    Outer *head;
} Arg0;

s32 fn_8022ED20(Arg0 *arg0, Pair16 *arg1, Pair16 *out, f32 *best) {
    __ps_t blk[3];
    Outer *o;
    INode *n;
    __ps_t *p;
    register __ps_t d0 __asm__("fr13");
    __ps_t d1;
    __ps_t t;
    __ps_t acc;
    __ps_t s;
    f32 min;
    s32 ret;

    o = arg0->head;
    min = lbl_802B0610;
    ret = 0;
    if (o == NULL) {
        return ret;
    }
    do {
        n = o->head;
        if (n != NULL) {
            p = blk;
            do {
                register __ps_t kb __asm__("fr10");
                {
                    __ps_t ln = n->xy;
                    register __ps_t lb __asm__("fr12") = n->zw;
                    register __ps_t la __asm__("fr11") = arg1->zw;
                    register __ps_t la2 __asm__("fr0") = arg1->xy;
                    kb = lbl_802B04F8[0];
                    d1 = lb - la;
                    d0 = ln - la2;
                }
                blk[1] = d1;
                blk[0] = d0;
                t = p[1];
                t = __builtin_ps_mul(t, t);
                t = __builtin_ps_merge00(t, kb);
                acc = __builtin_ps_madd(d0, d0, t);
                s = __builtin_ps_sum0(acc, acc, acc);
                blk[2] = s;
                {
                    register f32 vv __asm__("fr13");
                    register f32 cc __asm__("fr0");
                    vv = ((f32 *)&blk[2])[0];
                    cc = vv;
                    __asm__ __volatile__("" : "+f"(vv));
                    if (cc < min) {
                        min = cc;
                    ret = 1;
                    out->xy = n->xy;
                    out->zw = n->zw;
                    *best = min;
                    }
                }
                n = n->next;
            } while (n != NULL);
        }
        o = o->next;
    } while (o != NULL);
    return ret;
}
