// WIP DRAFT (non-matching) — C body reconstructed from the retail bytes.
// family=m2c range=0x8002C638-0x8002C8C8 size=656B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-05 (regalloc-shift): 52.44% masked, 78/164 words differ, size
// and frame exact (656B, stwu -0x50, stmw r29/0x44, stw r0/0x54, all locals at
// retail offsets 0x8/0x18/0x28/0x38, br_targets clean). Retail semantics fully
// recovered: node cursor *arg0, 12B header {type,kind,size} copied to the frame,
// unsigned switch on kind with case blocks laid out 1,4,2,7,3,5,6, default
// last, Mem_Alloc2's return passed as arg0 of every ctor, and the float/s32
// union pun in case 1.
// Residual: the whole body is one register group too high. Want allocates the
// three function-crossing webs arg0=r4, p(n+0xC)=r5, n=r6; ngccc gives
// arg0=r5, p=r6, n=r7 (identical instruction stream, renamed) and that shift
// cascades into cases 1/2/4/5/6/7. Two smaller residuals behind it: case 1
// emits `lfs f1,0x38(r1)` before `lwz r4,8(r1)` (want: lwz then lfs), and in
// cases 2/7 ngccc uses r1+offset for the four a-field stores where retail uses
// the r30 base for 3 of them (and orders the float stores z,w,x,y vs retail
// x,z,w,y).
// Ruled out for the group shift: payload-pointer `p` present/absent; pa/pb
// aliases before/after; a/b block- vs function-scope; `Vec4 v[2]` array form;
// struct pair form; `hd = n->h` (REQUIRED - field-by-field collapses to
// 648B) vs 3 orders of field assignment; header/case statement reorder;
// hoisted `Vec4 *r = &n->r` (hoists an extra addi into the prologue);
// hard-register pins on n/p/arg0 as pointer and as s32 alias (pins land but add
// 1-2 register-copy instructions, 660-664B); `register` on the parameter;
// -O1/-O2/-Os/-O3 (-O1 collapses to 652B, others identical).
#include "types.h"

typedef union {
    s32 i;
    f32 f;
} F32S32;

typedef struct {
    F32S32 x;
    F32S32 y;
    F32S32 z;
    F32S32 w;
} Vec4;

typedef struct {
    s32 type;
    u32 kind;
    s32 size;
} Hdr;

typedef struct {
    Hdr h;
    Vec4 q;
    Vec4 r;
} Node;

extern f32 lbl_802916E4;
extern f32 lbl_802916E8;
void *Mem_Alloc2(s32);
void *fn_8002BAC8(void *, s32, f32);
void *fn_8002BBA0(void *, s32, s32);
void *fn_8002BC78(void *, s32, Vec4 *, Vec4 *, s32);
void *fn_8002C388(void *, s32);
void *fn_8002C4C4(void *, s32, s32);
void *fn_8002C570(void *, s32, s32);

void *fn_8002C638(u8 **arg0) {
    Hdr hd;
    Vec4 a;
    Vec4 b;
    Node *n = (Node *)*arg0;
    Vec4 *p = &n->q;

    hd = n->h;
    *arg0 = (u8 *)p;

    switch (hd.kind) {
    case 1: {
        volatile F32S32 s;
        s.i = p->x.i;
        *arg0 = (u8 *)p + 4;
        return fn_8002BAC8(Mem_Alloc2(0x10), hd.type, s.f);
    }
    case 4: {
        s32 t = p->x.i;
        *arg0 = (u8 *)p + 4;
        return fn_8002BBA0(Mem_Alloc2(0x10), hd.type, t);
    }
    case 2: {
        Vec4 *pb = &b;
        Vec4 *pa = &a;
        a.x.f = lbl_802916E4;
        a.y.f = lbl_802916E4;
        a.z.f = lbl_802916E4;
        a.w.f = lbl_802916E8;
        b.x.i = p->x.i;
        b.y.i = p->y.i;
        b.z.i = p->z.i;
        b.w.i = p->w.i;
        *arg0 = (u8 *)&n->r;
        a.x.i = n->r.x.i;
        a.y.i = n->r.y.i;
        a.z.i = n->r.z.i;
        a.w.i = n->r.w.i;
        *arg0 = (u8 *)n + 0x2C;
        return fn_8002BC78(Mem_Alloc2(0x38), hd.type, pa, pb, 0);
    }
    case 7: {
        Vec4 *pb = &b;
        Vec4 *pa = &a;
        a.x.f = lbl_802916E4;
        a.y.f = lbl_802916E4;
        a.z.f = lbl_802916E4;
        a.w.f = lbl_802916E8;
        b.x.i = p->x.i;
        b.y.i = p->y.i;
        b.z.i = p->z.i;
        b.w.i = p->w.i;
        *arg0 = (u8 *)&n->r;
        a.x.i = n->r.x.i;
        a.y.i = n->r.y.i;
        a.z.i = n->r.z.i;
        a.w.i = n->r.w.i;
        *arg0 = (u8 *)n + 0x2C;
        return fn_8002BC78(Mem_Alloc2(0x38), hd.type, pa, pb, 1);
    }
    case 3:
        *arg0 = (u8 *)n + 0x2C;
        return fn_8002C388(Mem_Alloc2(0xC), hd.type);
    case 5: {
        s32 t = p->x.i;
        *arg0 = (u8 *)p + 4;
        return fn_8002C4C4(Mem_Alloc2(0x10), hd.type, t);
    }
    case 6: {
        s32 t = p->x.i;
        *arg0 = (u8 *)p + 4;
        return fn_8002C570(Mem_Alloc2(0x10), hd.type, t);
    }
    default:
        *arg0 += hd.size;
        return 0;
    }
}
