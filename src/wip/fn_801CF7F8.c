// WIP DRAFT (non-matching) — hand-rebuilt from disasm.
// RE-TRIAGED 2026-10-19: sweep still DIFF — doc-06 paired-single wall; wall stands. Parked as-is.
// family=m2c range=0x801CF7F8-0x801CF9B0 size=440B
// FLAG: -mps-float
// PARKED: doc06 paired-single wall (see docs/parkings/06-paired-single-ops.md).
// Structure fully mapped: GetFloat(arg1,0,&fr+0xD0,0) wrapper; fn_801079C(&sp8);
// PS pair staging o->0x58/0x60 pairs + lbl_802AD278 pair into sp8 buf (capstone prints
// psq displacements DECIMAL: 200(r1)=0xC8, 224(r1)=0xE0); then an inline PS vector-math
// chain of opcode-4 words — ps_mr XO10=72 pair moves (0x11400090 class, emittable as
// __ps_t copies), ps_mul/madd A-form (0x100B02F2/0x100A02BA), ps_sum0/ps_sum1 X-form
// (0x10000014/0x100A0018), muls0-class 0x11AB0332 — feeding fabs+fcmpu ble guard
// (plain ble, no NaN dance: negated-compare form needed, §6r-95). Then fn_80107B20
// (&sp8,1,0), r30 triple-recycle arg0->ret->andi-bit, three CObject_RemoveRefLink cleanup sites
// storing {0, bitv, ret}. The ps_sum/mul contraction tree has no C expression that
// schedules identically (same wall class as fn_801CE098 / fn_80155FF8);
// needs per-op __builtin_ps_sum0/_mul emission-order control. Twin: fn_801CF9B0.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AD358;
extern f32 lbl_802AD35C;
extern f32 lbl_802AD364;
extern char lbl_802AD278[];
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_801079C(void *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);

void fn_801CF7F8(Unk_C7387A53 *arg0, CStruct *arg1) {
    struct fr_t {
        char pad0[0xA8];
        s32 spB0;
        char pad1[0x24];
        s32 spD8;
        char pad2[8];
    } fr;
    char *sp8p = (char *)&fr;
    s32 t;

    GetFloat(arg1, 0, (char *)&fr + (s32)0xD0, 0);
    fn_801079C(sp8p);
    {
        s32 o = arg0->unk0xC;
        volatile __ps_t *q = (volatile __ps_t *)sp8p;
        q[0] = ((Unk_0B6E8BDA *)o)->unk0x58;
        q[1] = ((Unk_0B6E8BDA *)o)->unk0x60;
        q[2] = *(__ps_t *)&lbl_802AD278;
        q[0] = q[0];
        q[1] = q[1];
        q[24] = ((Unk_0B6E8BDA *)o)->unk0x98;
        q[25] = ((Unk_0B6E8BDA *)o)->unk0xA0;
        ((Unk_B806C637 *)&fr)->unk0xDC = lbl_802AD35C;
        ((Unk_B806C637 *)&fr)->unk0xE4 = ((Unk_B806C637 *)&fr)->unk0x28;
    }
    {
        f32 d8v = *(f32 *)((char *)&fr + (s32)0xD0 + 8);
        f32 a = ((Unk_73ADC38A *)sp8p)->unk0x18;
        f32 b = ((Unk_73ADC38A *)sp8p)->unk0x1C;
        f32 c = ((Unk_73ADC38A *)sp8p)->unk0x20;
        f32 k = ((Unk_B806C637 *)&fr)->unk0xC0;
        f32 m = ((Unk_B806C637 *)&fr)->unk0xC4;
        f32 n = ((Unk_B806C637 *)&fr)->unk0xC8;
        ((Unk_73ADC38A *)sp8p)->unk0x18 = d8v * k + a;
        ((Unk_73ADC38A *)sp8p)->unk0x1C = d8v * m + b;
        ((Unk_73ADC38A *)sp8p)->unk0x20 = d8v * n + c;
    }
    t = fn_80107B20(sp8p, 1, 0);
    if (t != 0) {
        s32 hw = ((Unk_73ADC38A *)sp8p)->unk0x58;
        s32 bitv = hw & 8;
        if (bitv != 0) {
            goto store_zero;
        }
        {
            f32 fv = ((Unk_73ADC38A *)sp8p)->unk0xA4;
            if (!(__builtin_fabsf(fv) > lbl_802AD364)) {
                s32 v = ((Unk_B806C637 *)&fr)->unk0xA8;
                if (v != 0) {
                    CObject_RemoveRefLink(v, (char *)&fr + (s32)0xA8);
                    ((Unk_B806C637 *)&fr)->unk0xA8 = bitv;
                }
                return 1;
            }
        }
store_zero:
        {
            s32 v = ((Unk_B806C637 *)&fr)->unk0xA8;
            if (v != 0) {
                CObject_RemoveRefLink(v, (char *)&fr + (s32)0xA8);
                ((Unk_B806C637 *)&fr)->unk0xA8 = 0;
            }
        }
        t = 0;
    } else {
        s32 v = ((Unk_B806C637 *)&fr)->unk0xA8;
        if (v != 0) {
            CObject_RemoveRefLink(v, (char *)&fr + (s32)0xA8);
            ((Unk_B806C637 *)&fr)->unk0xA8 = t;
        }
        t = 0;
    }
}
