// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7264-0x800A72E4 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// file-local typedefs: the shared Unk_* classes are wrong for this walk
// (node+0x4 is a sentinel/payload union, obj+0x4 a re-writable cursor).
// Layout copied verbatim from the byte-proven sibling src/fn_800A71E0.c.
typedef struct N7264 { char _0[4]; union { s32 i; struct N7264 *p; } v; char _8[0x14]; s32 unk0x1C; } N7264;
typedef struct G7264 { char _0[0xC]; N7264 *unk0xC; } G7264;
typedef struct A7264 { char _0[4]; void *unk0x4; char _8[4]; s32 unk0xC; } A7264;

register s32 a0 __asm__("r10");
register s32 n11 __asm__("r11");

// fn_800A7264: pop entries off the list at arg0+0x4 until one has a +0x1C key
// equal to arg0+0xC; returns that entry, or NULL when the list runs out.
N7264 *fn_800A7264(A7264 *arg0) {
    G7264 *cont;
    N7264 *x;
    s32 key;
    a0 = (s32)arg0;
    cont = *(G7264 **)(a0 + 4);
    n11 = (s32)cont->unk0xC;
    if (((N7264 *)n11)->v.i == -1) {
        n11 = 0;
    }
    *(N7264 **)(a0 + 4) = (N7264 *)n11;
    if (n11 != 0) {
        x = ((N7264 *)n11)->v.p;
    } else {
        x = 0;
    }
    if (x != 0) {
        key = *(s32 *)(a0 + 0xC);
        while (x != 0) {
            if (x->unk0x1C == key) {
                return x;
            }
            cont = *(G7264 **)(a0 + 4);
            n11 = (s32)cont->unk0xC;
            if (((N7264 *)n11)->v.i == -1) {
                n11 = 0;
            }
            *(N7264 **)(a0 + 4) = (N7264 *)n11;
            if (n11 != 0) {
                x = ((N7264 *)n11)->v.p;
            } else {
                x = 0;
            }
        }
    }
    return x;
}
