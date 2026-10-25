// WIP DRAFT (non-matching) — hand rebuild from disasm
// family=m2c range=0x80181014-0x801811D4 size=448B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: NEAR 92.9% (104/112 masked). Two residual scheduler clusters:
// (a) CObject_RemoveRefLink call-site arg-setup order (want addi r4-before-mr r3; got inverse);
// (b) float->int->float roundtrip dance micro-order + scratch-reg choice
//     (want lis r8/lis r11 early + lfd f13 between lwz/xoris + store pair HIGH-then-LOW;
//     got interleaves differently, uses r0/r9).
// Resisted: source reorderings, staged temps (sp8p/m64), volatile-cast store
// serialization, struct-member vs byte-offset cvt forms, 12+ flag combos
// (-fno-schedule-insns/-insns2 destroy regalloc globally: 16-18%).
// NOTABLE: want's `mr r9, r10` (dead insn reading undefined r10) is part of
// cc1's (f32)(f64)(s32)x roundtrip template (probes E/F in a private probe
// script) — reproduced here ONLY via inline asm wedge
// (`mr 9, 10`) + asm fctiwz/stfd because the natural cast form synthesizes a
// private FP pool constant into module .rodata (doc-14 promote blocker);
// manual dance referencing lbl_802A93C8 keeps .rodata empty => promotable.
// Frame-template struct pins exact layout incl. holes: {sp8, h0[12], buf[152]}
// @8..AF + pinned cvt slot @B0 via "m" operand + empty-asm pin.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80300434;
extern char lbl_802A93A8[];
extern char lbl_802A93AC[];
extern char lbl_802A93B4[];
extern char lbl_802A93C0[];
extern f32 lbl_802A93C4;
extern f64 lbl_802A93C8;
s32 fn_8017471C(void *, s32);
s32 fn_80141FA4(Unk_5FCDF30E *);
void GetElement_2(s32 *, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
char* PrintThousands(s32 arg0, char arg1);
void fn_800427AC(Unk_E80761A5 *, u8 *);
void Script_RunScript(s32, s32, s32, s32, s32);
typedef union {
    u32 w[2];
    f64 d;
} cvt_u;
void fn_80181014(Unk_667BA59C *arg0, s32 arg1, f32 farg0) {
    struct { s32 sp8; char h0[12]; char buf[152]; } L;
    cvt_u cvt;
    s32 temp_r3;
    s32 temp_r31;
    s32 var_r5;
    s32 cached;
    f32 f31v;
    f32 fv;
    s32 *sp8p;
    f64 m64;

    temp_r31 = lbl_80300434;
    temp_r3 = fn_8017471C(lbl_80305EAC, arg0->unk0xC);
    var_r5 = 0;
    if (temp_r3 != 0) {
        var_r5 = fn_80141FA4(temp_r3);
    }
    GetElement_2(&L.sp8, temp_r31, var_r5 + (s32)QB_THE_SCORE_POT_TEXT, 0);
    cached = L.sp8;
    if (cached != 0) {
        sp8p = &L.sp8;
        CObject_RemoveRefLink(cached, sp8p);
        L.sp8 = 0;
    }
    if (arg1 == 0) {
        *(u16 *)L.buf = *(u16 *)lbl_802A93A8;
    } else {
        if (farg0 != lbl_802A93C4) {
            register f32 t0 __asm__("fr0");
            f31v = farg0;
            __asm__("" : "+f"(f31v));
            __asm__ volatile("fctiwz %0, %1" : "=f"(t0) : "f"(f31v));
            __asm__ volatile("mr 9, 10" ::: "9");
            __asm__ volatile("stfd %0, %1" : : "f"(t0), "m"(cvt.d));
            __asm__("" : : "m"(cvt));
            m64 = lbl_802A93C8;
            temp_r31 = *(u32 *)((char *)L.buf + 156);
            *(volatile u32 *)((char *)L.buf + 152) = QB_INT_TO_DOUBLE_BIAS;
            *(volatile u32 *)((char *)L.buf + 156) = (u32)temp_r31 ^ 0x80000000;
            fv = (f32)(*(f64 *)((char *)L.buf + 152) - m64);
            if (fv == farg0) {
                sprintf(L.buf, (s32)lbl_802A93AC, PrintThousands(arg1, ','), temp_r31);
            } else {
                sprintf(L.buf, (s32)lbl_802A93B4, PrintThousands(arg1, ','), f31v);
            }
        } else {
            sprintf(L.buf, (s32)lbl_802A93C0, PrintThousands(arg1, ','));
        }
    }
    fn_800427AC(cached, L.buf);
    Script_RunScript(QB_UPDATESCOREPOT, 0, 0, 0, 0);
}
