// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float
// family=m2c range=0x800FD698-0x800FD81C size=388B
// PARKED: 29/96 words (30.2%). Semantics fully recovered (4x4 mat-vec,
// V=two PS pair-products; see below) and every instruction shape is
// emittable, but the game's schedule/register map resists reproduction.
//
// WANT structure (fully decoded):
//  head: obj=*(arg1+8) [r8], out=arg0 [r7], sel=*(obj+0x3c) [r10],
//        base=arg2*12 [r11]; if(sel!=0) off=sel else off=*(obj+0x30);
//        P=(vx,vy,vz) from base+off{0,4,8} -> sp18/sp1C/sp20; W=c184 -> sp24.
//        lfsx indexed first load; second reload feeds add+lfs 4(r9); third
//        reload lands in r0 (mine: r5/r0 mix).
//  PS:   cp=pair(sp20,sp24)->psq_l f12; a10=pair(arg1+0x10)->f13;
//        vp=r1+8 (addi r11,r1,8!); p18=pair(sp18,sp1C)->f0; cpS->16(r1);
//        c188->f12 late; WORD1=__builtin_ps_mul(p18,a10) [10000372];
//        a18=pair(arg1+0x18)->f11 (NOT f13: loaded while a10 still live);
//        t1S->8(r1); sp14=c188; t2=pair(sp10,sp14) via 8(r11); WORD2
//        [100002F2, c=f11]; t3S->8(r11). mr r3,r7 sits mid-section (+0x94).
//  tail: v-cached f10=spC,f5=sp8,f6=sp14 read ONCE; M-loads interleaved
//        INTO rows (not hoisted); sp10 reloaded 4x via lfs f0,8(r11);
//        row_i = V3*M3i+(V2*M2i+(V0*M0i+V1*M1i)) -> sp18/1C/20, row3 staged
//        in reg, stfs f6,0x24 AFTER psq_l f0,24(r1); pairs to (out)+0/+8.
// Tried (30+ variants, all compile_fn-masked-scored): load-order perms x6,
// fused/split muls, all-volatile vs mixed stack slots (all-volatile REQUIRED
// for frame 0x28 + spill shapes; plain slots collapse frame to 0x18),
// register pins {r7,r8,r10}+var_r11 plain/nested-pinned/unified-single-var,
// vp as separate/nested/unified var (lands r10 or perturbs FPR webs when
// pinned), volatile-typed pair accesses (fixes ORDER, flips FPR names),
// w184 named-local vs in-arm sp24 stores, post-merge store-order swap,
// flow-dependence coalescing, sel-liveness asm barrier, staged row temps,
// flags {-fno-sched-spec,-fno-sched-interblock,-fno-schedule-insns2,
// -fno-schedule-insns} (insns2/-interblock neutral-to-worse).
// Confirmed working pieces: head pins give byte-exact prologue+arms modulo
// one temp-reg choice; __builtin_ps_mul reproduces XO5=25 words exactly;
// FP-name rule observed in matched fn_800A11D8 (mul operands get f0/f13
// priority, remaining pair webs descend f12/f11) holds only when GPR
// allocation matches; single-word diffs flip whole-tail cascade.
// Sibling fn_800FD2D0 parked for the same class (docs/parkings/06).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 9.3% ([2]rev->9.3%).
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C184;
extern f32 lbl_8029C188;

void *fn_800FD698(void *arg0, Unk_BE223D5D *arg1, s32 arg2) {
    register char *out __asm__("r7");
    register char *temp_r8 __asm__("r8");
    register s32 sel __asm__("r10");
    char *var_r11;
    volatile f32 sp8;
    volatile f32 spC;
    volatile f32 sp10;
    volatile f32 sp14;
    volatile f32 sp18;
    volatile f32 sp1C;
    volatile f32 sp20;
    volatile f32 sp24;
    s32 var_r0;
    f32 w184;
    f32 v0;
    f32 v1;
    f32 v3;
    f32 r3v;
    char *vp;
    volatile f32 *v10;
    __ps_t cp;
    __ps_t a10;
    __ps_t p18;
    __ps_t t1;
    __ps_t a18;
    __ps_t olo;
    __ps_t ohi;

    temp_r8 = *((char * *)&arg1->unk0x8);
    out = arg0;
    sel = ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C;
    if (sel != 0) {
        var_r11 = (char *)(arg2 * 0xC);
        sp18 = *(f32 *)(var_r11 + sel);
        sp1C = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C + 4);
        var_r0 = ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C;
        w184 = lbl_8029C184;
    } else {
        w184 = lbl_8029C184;
        var_r0 = ((Unk_1D62F22E_2 *)temp_r8)->unk0x30;
        sp1C = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x30 + 4);
        sp18 = *(f32 *)(var_r11 + sel);
        sel = ((Unk_1D62F22E_2 *)temp_r8)->unk0x30;
        var_r11 = (char *)(arg2 * 0xC);
    }
    sp20 = *(f32 *)(var_r11 + var_r0 + 8);
    sp24 = w184;

    vp = (char *)&sp8;
    v10 = (volatile f32 *)(vp + 8);
    p18 = *(volatile __ps_t *)&sp18;
    a10 = *((volatile __ps_t *)&arg1->unk0x10);
    cp = *(volatile __ps_t *)&sp20;
    ((Unk_7AAFF886_2 *)vp)->unk0x8 = cp;
    *(volatile __ps_t *)&sp8 = __builtin_ps_mul(p18, a10);
    sp14 = lbl_8029C188;
    a18 = *((volatile __ps_t *)&arg1->unk0x18);
    ((Unk_7AAFF886_2 *)vp)->unk0x8 = __builtin_ps_mul(((Unk_7AAFF886_2 *)vp)->unk0x8, a18);

    v1 = spC;
    v0 = sp8;
    v3 = sp14;
    sp18 = v3 * arg1->unk0x50 + (*v10 * arg1->unk0x40 + (v0 * arg1->unk0x20 + v1 * arg1->unk0x30));
    sp1C = v3 * arg1->unk0x54 + (*v10 * arg1->unk0x44 + (v0 * arg1->unk0x24 + v1 * arg1->unk0x34));
    sp20 = v3 * arg1->unk0x58 + (*v10 * arg1->unk0x48 + (v0 * arg1->unk0x28 + v1 * arg1->unk0x38));
    r3v = v3 * arg1->unk0x5C + (*v10 * arg1->unk0x4C + (v0 * arg1->unk0x2C + v1 * arg1->unk0x3C));
    olo = *(__ps_t *)&sp18;
    sp24 = r3v;
    *(__ps_t *)out = olo;
    ohi = *(__ps_t *)&sp20;
    ((Unk_EA529D06 *)out)->unk0x8 = ohi;
    return out;
}
