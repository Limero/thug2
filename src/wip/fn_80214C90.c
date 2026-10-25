// PARKED 81.2% (-fno-schedule-insns): FPR scratch-coloring + load-order residue.
// Semantics fully correct; frame exact via 5 pinned out-slots + 6 plain-u32
// pads ("m"-pinned, volatile/array variants steal low slots); cA->fr31 pin
// fixes the {cA,sp10,sp14} recycling colors; negated-LE guard gives want's
// cror+bns. Residual 20 words: which scratch FPR (f0/f1/f11/f13) each
// subexpression lands in and [val|konst] load-order coin-flips at head +
// both return expressions. Tried: staging temps per path, swapped mult
// operand order, "+f" barriers, -fno-sched-spec/-fno-schedule-insns2
// (worse), decl-order permutations.
// FLAG: -fno-schedule-insns
// family=m2c range=0x80214C90-0x80214E24 size=404B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF6E8;
extern f32 lbl_802AF6EC;
extern f32 lbl_802AF6F0;
extern s32 GetStructure(s32 hash, s32 flag);
extern s32 GetFloat(CStruct * arg0, s32 hash, f32 * out, s32 flag);

f32 fn_80214C90(Unk_6A1874B8 *arg0) {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    register f32 var_f31 __asm__("fr31");
    f32 var_f29;
    f32 var_f30;
    f32 konst;
    f32 result;
    u32 _d0;
    u32 _d1;
    u32 _d2;
    u32 _d3;
    u32 _d4;
    u32 _d5;

    __asm__("" : : "m"(sp8), "m"(spC), "m"(sp10), "m"(sp14), "m"(sp18));
    __asm__("" : : "m"(_d0), "m"(_d1), "m"(_d2), "m"(_d3), "m"(_d4), "m"(_d5));
    var_f31 = lbl_802AF6E8;
    __asm__("" : "+f"(var_f31));
    if (arg0->unk0xA0 == var_f31) {
        return var_f31;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALK_POINT, &sp8, 1);
    var_f29 = sp8;
    if (!(arg0->unk0xA0 <= var_f29)) {
        arg0->unk0x1870 = 1;
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALK_SPEED, &sp10, 1);
        var_f30 = sp10;
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_RUN_SPEED, &sp14, 1);
        var_f31 = sp14;
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_COMBO_RUN_SPEED, &sp18, 1);
        konst = lbl_802AF6F0;
        result = ((((sp18 - var_f31) * arg0->unk0x1944) + var_f31) - var_f30) *
                 ((arg0->unk0xA0 - var_f29) / (konst - var_f29)) +
            var_f30;
        return result;
    } else {
        arg0->unk0x1870 = 0;
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALK_SPEED, &spC, 1);
        konst = lbl_802AF6EC;
        result = ((arg0->unk0xA0 - konst) / (var_f29 - konst)) *
                     (spC - var_f31) +
            var_f31;
        return result;
    }
}
