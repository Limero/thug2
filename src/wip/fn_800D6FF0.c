// PARKED 2026-10-10: 15.22% -> 65.52% (size-exact 232B).
//   Three separate bugs, all mechanical:
//   1. the 48 missing bytes were a 64-byte `__ps_t` block copy of the 3rd parameter
//      into a local buffer (16 psq_l/psq_st at 8-byte stride), so arg2 is `__ps_t *`
//      and the frame is 0x58 (stmw r28,0x48) not 0x30; -mps-float is required and the
//      `-fno-expensive-optimizations` scaffolding line was dropped (measured: it
//      changes nothing, so the flagless/`-mps-float`-only spelling is kept).
//   2. `s32`-typed float fields at 0x1DC/0x1E0 -> `*((f32 *)&...)` (fn_800DB9D4 class).
//   3. the allocation chain is `arg0->unk0x1E4 = fn_80007B94(fn_80009A44(0x98));` with
//      both declared s32, plus prototypes for fn_80007BFC/GetFloat — the three
//      spurious `crclr cr1eq` in the old object.
//   RESIDUAL (20 words): only the emission order of the 8 PS pair copies (want copies
//   slot 56 first, then 0,8,...,48) and the hoisting of `addi r9,r1,8`/`addi r29,r30,0x1dc`.
//   v3 (this body) is the best of three measured spellings; alternatives tried were
//   ascending copy order and the -fno-expensive-optimizations flag (both worse).
// family=m2c range=0x800D6FF0-0x800D70D8 size=232B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float
extern f32 lbl_80299BC0;

s32 fn_80009A44(s32);
s32 fn_80007B94(s32);
void fn_80007BFC(s32, void *, void *);
s32 GetFloat(CStruct *, s32, f32 *, s32);

void fn_800D6FF0(Unk_1536F9AE *arg0, CStruct *arg1, __ps_t *arg2) {
    __ps_t sp8[8];
    __ps_t *dst;
    f32 *pdst;
    f32 temp_f0;
    s32 var_ctr;

    if ((s32) arg0->unk0x1E4 == 0) {
        arg0->unk0x1E4 = fn_80007B94(fn_80009A44(0x98));
    }
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    dst = sp8;
    dst[7] = arg2[7];
    dst[6] = arg2[6];
    dst[5] = arg2[5];
    dst[4] = arg2[4];
    dst[3] = arg2[3];
    dst[2] = arg2[2];
    dst[1] = arg2[1];
    dst[0] = arg2[0];
    fn_80007BFC(arg0->unk0x1E4, arg0->unk0xC + 0x78, sp8);
    temp_f0 = lbl_80299BC0;
    pdst = (f32 *)((char *)arg0 + 0x1DC);
    *((f32 *)&arg0->unk0x1DC) = temp_f0;
    *((f32 *)&arg0->unk0x1E0) = temp_f0;
    GetFloat(arg1, QB_TIME, pdst, 0);
    arg0->unk0x1C = (s32) (arg0->unk0x1C | 0x20);
}
