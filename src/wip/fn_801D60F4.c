// WIP DRAFT (non-matching) — hand-rebuilt from disasm (m2c husk had statics-DCE'd body)
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 10.9091% -> 18.8034%
//   the `lim` pin was retargeted fr31 -> fr25 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// family=m2c range=0x801D60F4-0x801D62AC size=440B
// extra_cflags: -mps-float
//
// PARKED ~19% best variant: three interacting walls (all repro'd over ~20 shapes):
//  1. PROLOGUE HOME ORDER — want [mr r30,r3][mr r31,r4] (arg0->r30 homed FIRST).
//     Plain args give arg0->r31; dual hard-reg pins (a0/r30+a1/r31) give correct
//     homes but corrupt &buf addressing (addi r29,r31,8 passed as call arg — the
//     §73-151 local-pin frame corruption); decl-init a0 doesn't flip homes;
//     single-pin a1 leaves arg1->r30. No source shape found giving want's order.
//  2. PS_MR COPY ARTIFACT — want reads the scale pair ONCE (psq_l f13,232(r1))
//     then ps_mr f0,f13 with both ps_muls0 consuming f0. ngccc either coalesces
//     (single web, no mr), routes second read through MEMORY reload
//     (psq_l f12,224(r1)), or folds the stfs/psq_l dance entirely. "+f" barriers,
//     two-read CSE, SN_PS_type union .flt.hi/.ps pun, named-copy vars all tried.
//     NOTE: *(f32*)&__ps_t punned STORE ICEs cc1 (optabs.c:4116) — must use
//     SN_PS_type union member writes.
//  3. FRAME GAP — want 0x108 with stmw r30@0xF8 (8-byte hole between locals-end
//     0xF0 and GPR saves). volatile-double dummy adds the 8 but reorders slots;
//     referenced char pads via volatile "m" pins land elsewhere (-8 shift).
// Structure (decoded from want):
//   guard: *(s32*)(*(s32*)&lbl_80305FF8 + 0x44) == 0xD443A2BC (debug-hash check,
//   m2c had it right) gates everything; then if (arg1->4 > lbl_802AD4DC):
//     t11/t12 = arg1 pair[0..7]/[8..15] * scalepair (lane0 = lbl_802AD4E0 via
//     spE8 stfs+psq_l idiom); d2@spE0/d1@spD8 dead stores KEPT; out vec =
//     (*(obj+0xC)+0x58 pair +t11, +0x60 pair +t12) stored spC8/spD0;
//     fn_80107998(&buf(sp8,42w, callee writes through +0xA8 = spB0), obj+0x58, &spC8);
//     fn_80107B20(buf,1,0)!=0 -> reset arg1 vec to (lim,lbl_E4,lbl_E4,lim);
//     if (spB0) { CObject_RemoveRefLink(spB0,&spB0); spB0=0; }
//   eq-chain (mfcr/rlwinm idiom) arg1[0,C]==arg0[70,7C] && ... -> if unequal:
//     copy pairs arg0->70<-arg1[0], 78<-arg1[8], 90<-lbl_E4, 88<-68, 80<-60,
//     obj(=arg0->C)->88 <- arg1[0] pair, ->90 <- arg1[8] pair,
//     fn_80004518(arg0->C + 0x78, 1).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

extern void *fn_80107998(Unk_C7387A53 *, void *, s32);
extern s32 fn_80107B20(Unk_E9DCA07D *, void *, void *);
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void fn_80004518(s32, s32);
extern f32 lbl_802AD4DC;
extern f32 lbl_802AD4E0;
extern f32 lbl_802AD4E4;
extern s32 lbl_80305FF8;

void fn_801D60F4(void *arg0, Unk_5EF41E38 *arg1) {
    register s32 a1 __asm__("r31");
    s32 buf[42];
    s32 spB0;
    char pad_[20];
    __ps_t spC8;
    __ps_t spD0;
    __ps_t d1;
    __ps_t d2;
    SN_PS_type e8u;
    char pad2_[8];
    register f32 lim __asm__("fr25");
    s32 var_r11;
    s32 var_r0;
    __ps_t t11;
    __ps_t t12;
    s32 a0 = (s32)arg0;
    __ps_t sc1;

    a1 = (s32)arg1;
    __asm__ __volatile__("" : : "m"(pad_[0]), "m"(pad2_[0]));

    var_r11 = 1;
    if (((Unk_C7387A53 *)lbl_80305FF8)->unk0x44 == QB_OFF) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        lim = lbl_802AD4DC;
        if (*(f32 *)((s32)arg1 + 4) > lim) {
            t11 = ((__ps_t *)((char *)arg1))[0];
            e8u.flt.hi = lbl_802AD4E0;
            t12 = ((__ps_t *)((char *)arg1))[1];
            sc1 = *(__ps_t *)&e8u;
            t12 = ps_muls0(t12, sc1);
            t11 = ps_muls0(t11, sc1);
            d2 = t12;
            d1 = t11;
            t11 = ps_add(*(__ps_t *)((char *)*(void **)((s32)arg0 + 0xC) + 88), t11);
            t12 = ps_add(*(__ps_t *)((char *)*(void **)((s32)arg0 + 0xC) + 96), t12);
            spC8 = t11;
            spD0 = t12;
            fn_80107998((void *)buf, (char *)*(void **)((s32)arg0 + 0xC) + 0x58, (s32)&spC8);
            if (fn_80107B20((void *)buf, (void *)1, (void *)0) != 0) {
                *(f32 *)((s32)arg1 + 0) = lim;
                arg1->unk0x8 = lim;
                *(f32 *)((s32)arg1 + 4) = lbl_802AD4E4;
                ((Unk_E266FB50_4 *)arg1)->unk0xC = lbl_802AD4E4;
            }
            if (spB0 != 0) {
                CObject_RemoveRefLink((void *)spB0, (void *)&spB0);
                spB0 = 0;
            }
        }
    }
    var_r0 = ((*(f32 *)((s32)arg1 + 0) == *(f32 *)((s32)arg0 + 0x70)) &&
              (*(f32 *)((s32)arg1 + 4) == *(f32 *)((s32)arg0 + 0x74)) &&
              (arg1->unk0x8 == *(f32 *)((s32)arg0 + 0x78)) &&
              (((Unk_E266FB50_4 *)arg1)->unk0xC == *(f32 *)((s32)arg0 + 0x7C)));
    if (var_r0 == 0) {
        ((__ps_t *)arg0)[14] = ((__ps_t *)((char *)arg1))[0];
        ((__ps_t *)arg0)[15] = ((__ps_t *)((char *)arg1))[1];
        *(f32 *)((s32)arg0 + 0x90) = lbl_802AD4E4;
        *(__ps_t *)((s32)arg0 + 136) = *(__ps_t *)((s32)arg0 + 104);
        *(__ps_t *)((s32)arg0 + 128) = *(__ps_t *)((s32)arg0 + 96);
        *(__ps_t *)((char *)*(void **)((s32)arg0 + 0xC) + 136) = ((__ps_t *)((char *)arg1))[0];
        *(__ps_t *)((char *)*(void **)((s32)arg0 + 0xC) + 144) = ((__ps_t *)((char *)arg1))[1];
        fn_80004518(*(s32 *)((s32)arg0 + 0xC) + 0x78, 1);
    }
}
