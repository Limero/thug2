// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float
// range=0x800FFB58-0x800FFD58 size=512B
// PARKED: register-allocation coin-flips inside the hot loop (~30 residual
// word diffs at best: i/m28 callee-saved role swap r28<->r29, third vt->base
// reload into r0 vs r9, pair-load reg f12-vs-f0 choice, math fmadds schedule).
// Best score 46.9% with extra_cflags '-fno-gcse -mps-float' (-fno-gcse stops
// hoisting of call-arg addis per AGENTS recipe 69 but ICEs without -mps-float;
// plain flags hoist &buf/arg0+0xA0 into stmw'd regs -> stmw r26 vs WANT r27).
// Semantics fully decoded: init writes two Vec4s built from rodata2 floats
// lbl_8029C1C0/C4/C8 into arg0+0xA0..0xBF; then loops cnt=u16[vt+6] times
// over a stride-0xC float triple (base=vt->[0x3C] or [0x30]), scales xyz by
// pairs *(arg0+0x10)/(arg0+0x18) via ps_mul, dot-transforms by rows
// arg0+0x20/30/40(+trans 0x50..), calls bbox fn_8000728C(arg0+0xA0,&out).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 22.7% ([4]rev->19.2% [5]rev->22.7%).
#include "types.h"
#include "structs.h"
// FLAG: -mps-float -Os
extern f32 lbl_8029C1C0;
extern f32 lbl_8029C1C4;
extern f32 lbl_8029C1C8;
extern f32 lbl_8029C1CC;
void fn_8000728C(Unk_DB0E2BAB *, CStruct *);
void fn_800FFB58(Unk_9E1F72FD *arg0) {
    f32 in[4];
    f32 buf[4];
    f32 o[4];
    f32 *p;
    Unk_C7387A53 *vt;
    s32 base;
    s32 cnt;
    s32 i;
    s32 temp_r0;
    f32 dval;
    Unk_C4D756ED *m28;
    f32 a;
    f32 b;
    f32 c;
    a = lbl_8029C1C0;
    b = lbl_8029C1C4;
    buf[0] = buf[1] = buf[2] = a;
    buf[3] = b;
    arg0->unk0xA0 = ((Unk_EA529D06 *)buf)->unk0x0;
    arg0->unk0xA8 = ((Unk_EA529D06 *)buf)->unk0x8;
    buf[3] = b;
    c = lbl_8029C1C8;
    buf[0] = buf[1] = buf[2] = c;
    arg0->unk0xB8 = ((Unk_EA529D06 *)buf)->unk0x8;
    arg0->unk0xB0 = ((Unk_EA529D06 *)buf)->unk0x0;
    temp_r0 = *(u16 *)(*((s32 *)&arg0->unk0x8) + (s32)0x6);
    if (temp_r0 != 0) {
        dval = lbl_8029C1CC;
        cnt = temp_r0;
        p = in;
        m28 = (char *)arg0 + (s32)0x20;
        i = 0;
        do {
            vt = arg0->unk0x8;
            if (vt->unk0x3C != 0) {
                base = vt->unk0x3C;
                in[1] = *(f32 *)((char *)(i + vt->unk0x3C) + 4);
                in[0] = *(f32 *)((char *)(i + vt->unk0x3C));
            } else {
                base = vt->unk0x30;
                in[1] = *(f32 *)((char *)(i + vt->unk0x30) + 4);
                in[0] = *(f32 *)((char *)(i + vt->unk0x30));
            }
            p[2] = *(f32 *)((char *)base + i + 8);
            in[3] = dval;
            ((Unk_EA529D06 *)in)->unk0x0 = __builtin_ps_mul(((Unk_EA529D06 *)in)->unk0x0, arg0->unk0x10);
            ((Unk_EA529D06 *)p)->unk0x8 = __builtin_ps_mul(((Unk_EA529D06 *)p)->unk0x8, arg0->unk0x18);
            i += 0xC;
            o[0] = p[2] * m28->unk0x20 + in[0] * arg0->unk0x20 + in[1] * arg0->unk0x30 + arg0->unk0x50;
            o[1] = p[2] * ((Unk_1D62F22E_2 *)m28)->unk0x24 + in[0] * arg0->unk0x24 + in[1] * arg0->unk0x34 + arg0->unk0x54;
            o[2] = p[2] * ((Unk_1D62F22E_2 *)m28)->unk0x28 + in[0] * arg0->unk0x28 + in[1] * arg0->unk0x38 + arg0->unk0x58;
            o[3] = p[2] * ((Unk_1D62F22E_2 *)m28)->unk0x2C + in[0] * arg0->unk0x2C + in[1] * arg0->unk0x3C + arg0->unk0x5C;
            ((Unk_EA529D06 *)buf)->unk0x0 = ((Unk_EA529D06 *)o)->unk0x0;
            ((Unk_EA529D06 *)buf)->unk0x8 = ((Unk_EA529D06 *)o)->unk0x8;
            fn_8000728C((char *)arg0 + (s32)0xA0, buf);
        } while (--cnt != 0);
    }
}
