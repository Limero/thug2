// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A71E0-0x800A7264 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// file-local typedefs: the shared Unk_* classes are wrong for this walk
// (node+0x4 is a union, arg0+0x4 a re-writable cursor) -- see AGENTS.md 6bb-286.
typedef struct G71E0 { char _0[0xC]; struct N71E0 *unk0xC; } G71E0;
typedef struct N71E0 { char _0[4]; union { s32 i; struct N71E0 *p; } v; char _8[0x14]; s32 unk0x1C; } N71E0;
typedef struct A71E0 { char _0[4]; void *unk0x4; char _8[4]; s32 unk0xC; } A71E0;

register s32 a0 __asm__("r10");
register s32 n11 __asm__("r11");

N71E0 *fn_800A71E0(A71E0 *arg0, G71E0 *arg1, s32 arg2) {
    G71E0 *cont;
    N71E0 *node;
    N71E0 *x;
    a0 = (s32)arg0;
    *(G71E0 **)(a0 + 4) = arg1;
    node = arg1->unk0xC;
    if (node->v.i == -1) {
        node = 0;
    }
    *(N71E0 **)(a0 + 4) = node;
    if (node == 0) {
        __asm__("" : "+r"(node));
        node = 0;
    } else {
        node = node->v.p;
    }
    x = node;
    *(s32 *)(a0 + 0xC) = arg2;
    while (x != 0) {
        if (x->unk0x1C == arg2) {
            return x;
        }
        cont = *(G71E0 **)(a0 + 4);
        n11 = (s32)cont->unk0xC;
        if (((N71E0 *)n11)->v.i == -1) {
            n11 = 0;
        }
        *(N71E0 **)(a0 + 4) = (N71E0 *)n11;
        if (n11 != 0) {
            x = ((N71E0 *)n11)->v.p;
        } else {
            x = 0;
        }
    }
    return x;
}
