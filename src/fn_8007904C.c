// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007904C-0x800791A4 (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern char lbl_802FFE98[];

/* Real arities, audited against each callee's first instructions:
 *   Mem_Alloc/Mem_Free2  read r3 only (mr r4,r3)
 *   fn_8000F2F8/fn_8000F320  read r3 (lwz 0x110(r3))
 *   fn_80078C5C  7 args: the call site sets r3(r3, the vcall return), r4, r5,
 *   r6, r7 and f1/f2, so it is (base,w,h,dst,0x20,f32,f32). Its own WIP
 *   draft's 6-arg reconstruction is missing the 0x20.
 *   memcpy is deliberately LEFT IMPLICIT — want keeps `crclr cr1eq` before
 *   that one bl and has none before any other call here. */
void *Mem_Alloc(s32);
void Mem_Free2(void *);
void *memset(void *, int, unsigned int);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
s32 fn_8000F320(Unk_9994C3F5 *);
void fn_80078C5C(s32 *, s32, s32, void *, s32, f32, f32);

typedef struct { char _00[0x6]; u8 log2w; u8 log2h; } DIM;
typedef struct { char _00[0x158]; s16 off; char _15A[2];
                 void *(*getbase)(void *); } MGR;
typedef struct { char _00[0x8]; MGR *mgr; DIM *dim; } COMP;

bool fn_8007904C(COMP *arg0, f32 farg0, f32 farg1) {
    Unk_9994C3F5 *hm;
    void *buf, *base, *dst;
    MGR *m;
    DIM *d;

    hm = *(Unk_9994C3F5 **)lbl_802FFE98;
    fn_8000F2F8(hm, hm->unk0x118);
    buf = Mem_Alloc((u16) (1 << arg0->dim->log2w) *
                    (u16) (1 << arg0->dim->log2h) * 4);
    memset(buf, 0, (u16) (1 << arg0->dim->log2w) *
                     (u16) (1 << arg0->dim->log2h) * 4);
    fn_8000F320(*(Unk_9994C3F5 **)lbl_802FFE98);

    m = arg0->mgr;
    base = m->getbase((char *)arg0 + m->off);
    d = arg0->dim;
    fn_80078C5C(base, (u16) (1 << d->log2w), (u16) (1 << d->log2h), buf,
                0x20, farg0, farg1);
    m = arg0->mgr;
    dst = m->getbase((char *)arg0 + m->off);
    memcpy(dst, buf, (u16) (1 << arg0->dim->log2w) *
                       (u16) (1 << arg0->dim->log2h) * 4);
    if (buf != 0) {
        Mem_Free2(buf);
    }
    return true;
}
