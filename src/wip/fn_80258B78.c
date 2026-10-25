// WIP DRAFT (non-matching) — family=m2c range=0x80258B78-0x80258EAC size=820B
// PARKED 1.1% (m2c husk — compiled body is garbage; needs full hand-rebuild
// from disasm, 820B > 600B rebuild threshold so documented only):
// Curve-table builder, void fn_80258B78(obj r3, cfg r4->r31, state r5->r29).
// Frame 0xE0; saves f21-f31 + r24-r31. Locals: cvt pair sp60/sp64 shared by
// ALL int->f64 conversions (magic = lbl_802B1BF0 = 0x4330000080000000, f30
// copy in f29 inside loop).
// Flow: idx4 = obj->0x1C<<2 (r28, copied r25); if (*(state->8 + idx4) != 0)
// skip all. root = *(obj->0x2C); n = root->0x1C[idx4]; half = n/2 signed
// (srwi+add+srawi -> r26). Float consts (.rodata2): K1=lbl_802B1BF8(0x39c1fc8f)
// K2=lbl_802B1BFC(0.25) K3=lbl_802B1C00(0x329ee9ee) C08=lbl_802B1C08(double
// 13.2) C10=lbl_802B1C10(double 2.24) K4=lbl_802B1C18 K5=lbl_802B1C1C(0.5)
// K6=lbl_802B1C20 K7=lbl_802B1C24.
// Pre-loop: A = fn_8026FF40((float)arg1->4 * K1); B = fn_8026FF40(conv14 *
// (conv14*K2) * K3) * C10; total = fmadd(A, C08, B) + conv14*K4;
// scale f24 = frsp((double)*(u32*)arg2->0? no: (double)(arg2->0)/total).
// tbl = fn_8024EAF4(HEAP, (half+1)*4); *(state->8 + idx4) = tbl.
// Loop i=0..half-1 (walker r28 += 4): t=conv14 each iteration; x =
// ((t*K5)/(float)half)*i; a = fn_8026FF40(x*K6); b = fn_8026FF40((((t*K5/
// (float)half)*i)^2)*K3)*C10; c = fmadd(a, C08copy_f25, b); d = ((((t*K5/
// (float)half)*i))*K7); v = fn_80270290((c+d)*scale); clamp v to arg2->0-1;
// arr[i] = v. Epilogue: arr[half] = -1; arg2->0xC[idx4/4]... actually stwx
// r26(half), r24(state+0xC), r25(idx4) -> state->arrC[idx] = half.
// Register recycling to watch: f25(K3 float) overwritten mid-preheader with
// C08 double copy (K3 moves to f21); f30(magic) copied f29 for loop; r7/r9/
// r10/r11 page anchors all -0x7fd5 (0x802B0000). Callees: fn_8026FF40(f32)->f32
// (called w/ single float arg), fn_80270290(f64)->f64, fn_8024EAF4(heap,n).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.4% ([2]rev->2.4%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -fno-expensive-optimizations
extern f64 lbl_802B1BF0;
extern f32 lbl_802B1BF8;
extern f32 lbl_802B1BFC;
extern f32 lbl_802B1C00;
extern f64 lbl_802B1C08;
extern f64 lbl_802B1C10;
extern f32 lbl_802B1C18;
extern f32 lbl_802B1C1C;
extern f32 lbl_802B1C20;
extern f32 lbl_802B1C24;
static s32 saved_reg_r13;

void fn_80258B78(CScript *arg0, CStruct *arg1, CStruct *arg2) {
    s32 sp64;
    s32 sp60;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f13;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f27;
    f32 temp_f28_2;
    f32 temp_f31_2;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f26;
    f64 temp_f28;
    f64 temp_f30;
    f64 temp_f30_2;
    f64 temp_f31;
    s32 temp_r11;
    s32 temp_r26;
    s32 temp_r28;
    s32 temp_r9_2;
    s32 var_r0;
    s32 var_r27;
    s32 var_r28;
    u32 temp_r9;
    Unk_31DE137E *temp_r8;

    temp_r28 = arg0->unk0x1C * 4;
    if ((s32) *((s32 *)temp_r28 + arg2->unk0x8) == 0) {
        temp_r8 = **((s32 * *)&arg0->unk0x2C);
        var_r27 = 0;
        temp_f30 = lbl_802B1BF0;
        temp_r9 = *((s32 *)temp_r8->unk0x1C + temp_r28);
        temp_f13 = lbl_802B1BF8;
        temp_r9_2 = temp_r9 + (temp_r9 >> 0x1FU);
        temp_r26 = temp_r9_2 >> 1;
        temp_f31 = fn_8026FF40(-3.948926e-39f, temp_r8, temp_r9_2, (f32) (f64) *((f32 *)&arg1->unk0x4) * temp_f13, temp_f13);
        temp_f25 = lbl_802B1C00;
        temp_f0 = (f32) (f64) *((f32 *)&arg1->unk0x4);
        temp_f26 = lbl_802B1C10;
        temp_f1 = fn_8026FF40(temp_f0 * (temp_f0 * lbl_802B1BFC) * temp_f25) * temp_f26;
        temp_f28 = lbl_802B1C08;
        temp_f24 = (f32) ((f64) *((f32 *)&arg2->unk0x0) / ((temp_f31 * temp_f28) + temp_f1 + (f64) ((f32) (f64) *((f32 *)&arg1->unk0x4) * lbl_802B1C18)));
        *((s32 *)temp_r28 + arg2->unk0x8) = fn_8024EAF4(*(s32 *)((char *)saved_reg_r13 - 0x7F40), (temp_r26 + 1) * 4, temp_f1);
        if (temp_r26 > 0) {
            sp64 = temp_r26 ^ 0x80000000;
            sp60 = QB_INT_TO_DOUBLE_BIAS;
            temp_f27 = lbl_802B1C1C;
            temp_f22 = lbl_802B1C20;
            var_r28 = 0;
            temp_f23 = lbl_802B1C24;
            temp_f28_2 = (f32) ((f64) sp60 - temp_f30);
            do {
                var_r0 = (s32) fn_80270290(((temp_f30_2 * temp_f28) + temp_f1_2 + (f64) ((((f32) ((f64) sp60 - temp_f30) * temp_f27) / temp_f28_2) * temp_f31_2 * temp_f23)) * (f64) temp_f24);
                temp_r11 = *((f32 *)&arg2->unk0x0);
                sp60 = QB_INT_TO_DOUBLE_BIAS;
                sp64 = (s32)arg1->unk0x4 ^ 0x80000000;
                temp_f1_2 = fn_8026FF40(temp_f0_3 * temp_f0_3 * temp_f25) * temp_f26;
                temp_f0_3 = (((f32) ((f64) sp60 - temp_f30) * temp_f27) / temp_f28_2) * temp_f31_2;
                sp60 = QB_INT_TO_DOUBLE_BIAS;
                sp64 = (s32)arg1->unk0x4 ^ 0x80000000;
                temp_f30_2 = fn_8026FF40(((temp_f0_2 * temp_f27) / temp_f28_2) * temp_f31_2 * temp_f22);
                temp_f31_2 = (f32) ((f64) sp60 - temp_f30);
                sp60 = QB_INT_TO_DOUBLE_BIAS;
                temp_f0_2 = (f32) ((f64) sp60 - temp_f30);
                sp64 = var_r27 ^ 0x80000000;
                sp60 = QB_INT_TO_DOUBLE_BIAS;
                sp64 = (s32)arg1->unk0x4 ^ 0x80000000;
                if (var_r0 >= temp_r11) {
                    var_r0 = temp_r11 - 1;
                }
                var_r27 += 1;
                *((s32 *)var_r28 + ((s32)temp_r28 + arg2->unk0x8)) = var_r0;
                var_r28 += 4;
            } while (var_r27 < temp_r26);
        }
        *((s32 *)((char *)*((s32 *)temp_r28 + arg2->unk0x8) + (var_r27 * 4))) = -1;
        *((s32 *)arg2 + 0xC + temp_r28) = temp_r26;
    }
}
