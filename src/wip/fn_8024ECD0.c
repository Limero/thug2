// WIP DRAFT (non-matching) — rebuilt from disasm (heap realloc)
// family=m2c range=0x8024ECD0-0x8024EE00 size=304B
//
// PARKED ~52% (best of ~20 shapes; semantics complete).
// Recovered structure: realloc(heap, ptr, size) — lock guard; *--p header;
// aligned/limit chain (size->r4 recycled); oldsz>=limit fast return;
// chk = next-free-and-big-enough via subfc/adde carry bool; pathA
// alloc(heap,limit)+memcpy(0x8026AE28)+EBD8 free; pathB split-in-place
// (small: total|0x01000000, big: limit-header + stwx at p+aligned).
// Remaining residue (all doc-15/scheduling class):
//  - want fuses [bl EAF4][or. r31,r3,r3][beq exit]; got sinks the test
//    past the memcpy block (assignment-in-condition, "+r"/rebirth
//    barriers, shared-ret-var restructures all tried).
//  - memcpy arg-move order want [r4][r5][r3] vs got [r5][r4][r3].
//  - chk second-branch beq-calc vs bne-zero polarity flips with every
//    arm permutation (nested-else / compute-first / goto forms).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *fn_8024EAF4(s32 **heap, s32 size);
s32 fn_8024EBD8(s32 **heap, s32 *ptr);
void memcpy(void *dst, const void *src, u32 n);

void *fn_8024ECD0(CStruct *heap, void *ptr, s32 size) {
    s32 *p;
    s32 v;
    u32 t;
    u32 aligned;
    u32 oldsz;
    s32 chk;
    u32 off;
    s32 nv;
    s32 *np;
    void *newblk;

    t = size;
    if (heap->unk0x4 != 0) {
        return NULL;
    }
    p = (s32 *)ptr;
    v = *--p;
    aligned = (t + 3) & QB_UNKNOWN_0xFFFFFFFC;
    t = aligned + 4;
    oldsz = (v * 4) & QB_UNKNOWN_0x03FFFFFC;
    if (oldsz >= t) {
        return ptr;
    }
    {
        off = oldsz;
        __asm__("" : "=r"(off) : "0"(off));
        np = (s32 *)((char *)p + off);
        nv = *(s32 *)((char *)p + off);
        if (nv == -1) {
            chk = 0;
        } else if (!(nv & QB_UNKNOWN_0x01000000)) {
            chk = (((nv * 4) & QB_UNKNOWN_0x03FFFFFC) >= t - oldsz);
        } else {
            chk = 0;
        }
        if (chk == 0) {
            newblk = fn_8024EAF4(heap, t);
        } else {
            s32 nv2 = *np;
            u32 total = oldsz + ((nv2 * 4) & QB_UNKNOWN_0x03FFFFFC);
            if (total < t + 8) {
                *p = (s32)(((total >> 2) & 0xFFFFFF) | QB_UNKNOWN_0x01000000);
            } else {
                *p = (s32)(((((t + 3) >> 2) & 0xFFFFFF) | QB_UNKNOWN_0x01000000));
                *(s32 *)((char *)p + (t & QB_UNKNOWN_0xFFFFFFFC)) = (s32)(((u32)(total - t + 3) >> 2) & 0xFFFFFF);
            }
            return ptr;
        }
        if (newblk != NULL) {
            memcpy(newblk, ptr, oldsz);
            fn_8024EBD8(heap, ptr);
        }
        return newblk;
    }
}
