// WIP DRAFT (non-matching) — rebuilt from disasm (heap free/coalesce)
// FLAG: -Os
// family=m2c range=0x8024EBD8-0x8024ECD0 size=248B
//
// PARKED ~15% (best of ~40 shapes; structure semantically complete).
// Blocker = doc-32 walker-role-rotation signature: retail recycles
// registers across webs in chains GCC 2.95 won't reproduce from any
// single source shape —
//   entry wants {t0:r9, hdr:r5, v:r11, prev:r6, i:r8, sz:r7, szw:r4};
//   hdr-branch wants [clrlwi v2m][add ni=r0][slwi off2=r9][add np=r8]
//   i.e. np RECYCLES i's reg while off2 recycles the guard-load's reg.
// Register pins ({r5,r6,r7,r4} + i:r8) fix the entry block byte-exactly
// but BLOCK the branch's recycling (off2/np collapse onto the pinned reg,
// extra mr); unpinned sources rotate {hdr,prev,sz} colors cyclically
// through every decl-init/statement permutation tried (24 orders).
// Memory-clobber before the loop IS required (else GCSE merges *arg0);
// beqlr-vs-bne+blr guard polarity never flipped either way.
// Retry hint: a shape that gets entry colors without pins would let the
// natural recycling resume.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

s32 fn_8024EBD8(s32 **arg0, s32 *arg1) {
    s32 *hdr = arg1 - 1;
    s32 *prev = NULL;
    s32 i = 0;
    u32 sz = ((*hdr) * 4) & QB_UNKNOWN_0x03FFFFFC;
    s32 r;
    u32 szw;

    if (**arg0 == -1) {
        return (s32)arg0;
    }
    __asm__ volatile("" ::: "memory");
    szw = sz >> 2;
    for (;;) {
        s32 *base = *arg0;
        s32 *p = base + i;
        if (p == hdr) {
            s32 v2 = base[i];
            i += v2 & 0xFFFFFF;
            {
                s32 *np = base + i;
                if (prev != NULL) {
                    s32 pv = *prev;
                    r = pv & QB_UNKNOWN_0x01000000;
                    if (r == 0) {
                        s32 nv = base[i];
                        if (nv == -1 || (nv & QB_UNKNOWN_0x01000000)) {
                            *prev = (s32)((((sz + (((u32)pv * 4) & QB_UNKNOWN_0x03FFFFFC)) >> 2) & 0xFFFFFF));
                        } else {
                            *prev = (s32)(((((sz + (((u32)pv * 4) & QB_UNKNOWN_0x03FFFFFC)) + (((u32)nv * 4) & QB_UNKNOWN_0x03FFFFFC)) >> 2) & 0xFFFFFF));
                        }
                        return r;
                    }
                } else {
                    r = (s32)arg0;
                }
                {
                    s32 nv2 = *np;
                    if (nv2 == -1) {
                        *hdr = (s32)szw;
                        return r;
                    }
                    r = nv2 & QB_UNKNOWN_0x01000000;
                    __asm__("" : "+r"(r));
                    if (r != 0) {
                        *hdr = (s32)szw;
                    } else {
                        *hdr = (s32)((((sz + (((u32)nv2 * 4) & QB_UNKNOWN_0x03FFFFFC)) >> 2) & 0xFFFFFF));
                    }
                    return r;
                }
            }
        }
        prev = p;
        i += p[0] & 0xFFFFFF;
        if (base[i] == -1) {
            break;
        }
    }
    return (s32)arg0;
}
