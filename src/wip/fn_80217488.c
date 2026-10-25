// PARKED 2.6%: m2c statics-DCE husk (compiled body ~7 insns vs want's 272).
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 0.7440% -> 1.1905% per-object flags: -Os -> -fno-schedule-insns2
// 2688B FPR-heavy function = multi-session hand-rebuild per doc §6ai-158
// (same class as D3D18/D5058/D59F8). Structure decoded from want disasm:
//
// FRAME: stwu -0xF0; stfd f31,0xE8 (FPR +8 quirk, recipe 63); stmw r19,0xB4
//   (saves r19..r31, 13 GPRs); locals: search_t @r1+8 (walker state),
//   sp18..sp98 region holds two 4x4 float matrices.
// PROLOGUE WEBS: r31=lbl_802A83F8 addr (@ha/@l); r11=&search_t; r19=&search_t
//   home copy; r20=*(s32*)&lbl_80305F9C; f31 = *(f32*)&lbl_802AFD5C loaded
//   before first call.
// BODY:
// 1. if (fn_80198F7C(*(s32*)&lbl_80305EC0) != 0x6C5FF266) { search.f8=label;
//    return; }   [hash check]
// 2. var_r26 = fn_8021D454(r20, &search, 0); loop while != NULL:
//    a. if (fn_80229B94(var)==0) goto next;
//    b. switch (fn_80229BAC(var)): case0->hash 0x36EA35EB, case1->0x06270B12,
//       case2->0x3DB516B0, case3->0x85E38F38, default->0
//    c. temp_r31(=obj+0x78 later) : r29 = fn_8009F498(hash); if NULL next;
//    d. GetChecksum_3(*(r26+0x18), 0x222756D5);
//       fn_800C9780(); fn_80038C04(0xDDEBD751?, r5=obj+0x78);
//    e. DOC-30 SPIN WINDOW: r0 is loaded with 4 and moved to the count
//       register; four stack addresses are set up (r25=sp+0x20,
//       r27=sp+0x28, r24=sp+0xA0, r22=sp+0x64); the window then spins
//       on a self-targeting decrement-and-branch.
//    f. sp98 = fn_80003E0C(&sp18, *(f32*)&lbl_802AFD58);
//    g. BLOCK M1 (16x): result[i][j] = sum_k M1[i][k]*M2[k][j], each element =
//       fmuls + 3x fmadds chain over *(sp98)[0..0xC] x obj[0x10/0x14/0x18/0x1C
//       +k*4] x obj2[0x78/...] etc; stores to sp58..sp94. Scratch FPR rotation
//       f9-f13 (lfs/fmuls/fmadds interleaved, see want 0x802175FC-0x80217894).
//    h. BLOCK M2: same shape second multiply storing to obj+0x30.. (temp_r11)
//       using sp18/sp1C/sp20/sp24 columns; then reload walker->0x18 into
//       temp_r9 and repeat into sp28.. via r30=&spA0 web.
//    i. tail stores sp38..sp44 (second matrix rows), then next-walker
//       var_r26 = fn_8021D4E8(r20, &search, 0).
// 3. search.f8 = lbl_802A8030-class label store at exit (stw r31,8(r19)).
// RESISTED: m2c statics-DCE ate all matrix locals (file-scope statics in the
// old draft). Rebuild needs real local arrays/structs for both matrices plus
// exact scratch-FPR scheduling of ~200 lfs/fmul/fmadds insns.
// family=m2c range=0x80217488-0x80217F08 size=2688B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
extern f32 lbl_802AFD58;
extern f32 lbl_802AFD5C;
extern f32 lbl_802AFD60;
extern f32 lbl_802AFD64;
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_80229B94(void *);
s32 fn_80038C04(s32, s32);
// FLAG: -fno-schedule-insns2
s32 GetChecksum_3(Unk_6A70655D *, void *);
extern char lbl_802A83F8[];
static s32 sp1C;
static s32 sp24;
static s32 sp98;
static s32 spA0;

void fn_80217488(void) {
    void *spA0;
    void *sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    Unk_59AB5482 sp28;
    f32 sp20;
    Unk_59AB5482 sp18;
    Unk_59AB5482 sp8;
    s32 var_r3;
    f32 temp_f31;
    s32 temp_r20;
    s32 temp_r3;
    s32 var_ctr;
    Unk_C7387A53 *temp_r10;
    CStruct *temp_r11;
    void *temp_r11_2;
    void *temp_r31;
    void *temp_r3_2;
    Unk_6A70655D *temp_r9;
    CScript *var_r26;

    temp_r20 = *(s32 *)&lbl_80305F9C;
    sp8.unk0x4 = 0;
    sp8.unk0x8 = (s32)lbl_802A83F8;
    if (fn_80198F7C(*(s32 *)&lbl_80305EC0, 0x80300000, 0x80300000) != QB_NETCTF) {
        sp8.unk0x8 = (s32)lbl_802A83F8;
        return;
    }
    var_r26 = fn_8021D454(temp_r20, &sp8, 0);
    if (var_r26 != NULL) {
        temp_f31 = lbl_802AFD5C;
loop_4:
        if (fn_80229B94(var_r26) != 0) {
            temp_r3 = fn_80229BAC(var_r26);
            switch (temp_r3) {                      
            case 0:
                var_r3 = QB_TRG_CTF_RED;
                break;
            case 1:
                var_r3 = QB_TRG_CTF_BLUE;
                break;
            case 2:
                var_r3 = QB_TRG_CTF_GREEN;
                break;
            case 3:
                var_r3 = QB_TRG_CTF_YELLOW;
                break;
            default:
                var_r3 = 0;
                break;
            }
            temp_r3_2 = fn_8009F498(var_r3);
            if (temp_r3_2 != NULL) {
                temp_r31 = temp_r3_2 + 0x78;
                GetChecksum_3(var_r26->unk0x18, QB_SKELETON);
                fn_800C9780();
                fn_80038C04(QB_BONE_HEAD, temp_r31);
                var_ctr = 4;
                do {
                    var_ctr -= 1;
                } while (var_ctr != 0);
                sp98 = fn_80003E0C(&sp18, lbl_802AFD58);
                temp_r11 = temp_r31 + 0x30;
                ((Unk_59AB5482 *)&sp98)->unk0x4 = temp_r31;
                sp58 = (((Unk_DB0E2BAB *)sp98)->unk0xC * ((Unk_DB0E2BAB *)temp_r31)->unk0x30) + ((((Unk_DB0E2BAB *)sp98)->unk0x8 * ((Unk_DB0E2BAB *)temp_r31)->unk0x20) + ((((Unk_DB0E2BAB *)sp98)->unk0x0 * ((Unk_C7387A53 *)temp_r3_2)->unk0x78) + (((Unk_DB0E2BAB *)sp98)->unk0x4 * ((Unk_DB0E2BAB *)temp_r31)->unk0x10)));
                sp5C = (((Unk_DB0E2BAB *)sp98)->unk0xC * ((Unk_DB0E2BAB *)temp_r31)->unk0x34) + ((((Unk_DB0E2BAB *)sp98)->unk0x8 * ((Unk_DB0E2BAB *)temp_r31)->unk0x24) + ((((Unk_DB0E2BAB *)sp98)->unk0x0 * ((Unk_DB0E2BAB *)temp_r31)->unk0x4) + (((Unk_DB0E2BAB *)sp98)->unk0x4 * ((Unk_DB0E2BAB *)temp_r31)->unk0x14)));
                sp60 = (((Unk_DB0E2BAB *)sp98)->unk0xC * ((Unk_DB0E2BAB *)temp_r31)->unk0x38) + ((((Unk_DB0E2BAB *)sp98)->unk0x8 * ((Unk_DB0E2BAB *)temp_r31)->unk0x28) + ((((Unk_DB0E2BAB *)sp98)->unk0x0 * ((Unk_DB0E2BAB *)temp_r31)->unk0x8) + (((Unk_DB0E2BAB *)sp98)->unk0x4 * ((Unk_DB0E2BAB *)temp_r31)->unk0x18)));
                sp64 = (((Unk_DB0E2BAB *)sp98)->unk0xC * ((Unk_DB0E2BAB *)temp_r31)->unk0x3C) + ((((Unk_DB0E2BAB *)sp98)->unk0x8 * ((Unk_DB0E2BAB *)temp_r31)->unk0x2C) + ((((Unk_DB0E2BAB *)sp98)->unk0x0 * ((Unk_DB0E2BAB *)temp_r31)->unk0xC) + (((Unk_DB0E2BAB *)sp98)->unk0x4 * ((Unk_DB0E2BAB *)temp_r31)->unk0x1C)));
                sp68 = (((Unk_DB0E2BAB *)sp98)->unk0x1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x30) + ((((Unk_DB0E2BAB *)sp98)->unk0x18 * ((Unk_DB0E2BAB *)temp_r31)->unk0x20) + ((((Unk_DB0E2BAB *)sp98)->unk0x10 * ((Unk_C7387A53 *)temp_r3_2)->unk0x78) + (((Unk_DB0E2BAB *)sp98)->unk0x14 * ((Unk_DB0E2BAB *)temp_r31)->unk0x10)));
                sp6C = (((Unk_DB0E2BAB *)sp98)->unk0x1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x34) + ((((Unk_DB0E2BAB *)sp98)->unk0x18 * ((Unk_DB0E2BAB *)temp_r31)->unk0x24) + ((((Unk_DB0E2BAB *)sp98)->unk0x10 * ((Unk_DB0E2BAB *)temp_r31)->unk0x4) + (((Unk_DB0E2BAB *)sp98)->unk0x14 * ((Unk_DB0E2BAB *)temp_r31)->unk0x14)));
                sp70 = (((Unk_DB0E2BAB *)sp98)->unk0x1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x38) + ((((Unk_DB0E2BAB *)sp98)->unk0x18 * ((Unk_DB0E2BAB *)temp_r31)->unk0x28) + ((((Unk_DB0E2BAB *)sp98)->unk0x10 * ((Unk_DB0E2BAB *)temp_r31)->unk0x8) + (((Unk_DB0E2BAB *)sp98)->unk0x14 * ((Unk_DB0E2BAB *)temp_r31)->unk0x18)));
                sp74 = (((Unk_DB0E2BAB *)sp98)->unk0x1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x3C) + ((((Unk_DB0E2BAB *)sp98)->unk0x18 * ((Unk_DB0E2BAB *)temp_r31)->unk0x2C) + ((((Unk_DB0E2BAB *)sp98)->unk0x10 * ((Unk_DB0E2BAB *)temp_r31)->unk0xC) + (((Unk_DB0E2BAB *)sp98)->unk0x14 * ((Unk_DB0E2BAB *)temp_r31)->unk0x1C)));
                sp78 = (((Unk_DB0E2BAB *)sp98)->unk0x2C * ((Unk_DB0E2BAB *)temp_r31)->unk0x30) + ((((Unk_DB0E2BAB *)sp98)->unk0x28 * ((Unk_DB0E2BAB *)temp_r31)->unk0x20) + ((((Unk_DB0E2BAB *)sp98)->unk0x20 * ((Unk_C7387A53 *)temp_r3_2)->unk0x78) + (((Unk_DB0E2BAB *)sp98)->unk0x24 * ((Unk_DB0E2BAB *)temp_r31)->unk0x10)));
                sp7C = (((Unk_DB0E2BAB *)sp98)->unk0x2C * ((Unk_DB0E2BAB *)temp_r31)->unk0x34) + ((((Unk_DB0E2BAB *)sp98)->unk0x28 * ((Unk_DB0E2BAB *)temp_r31)->unk0x24) + ((((Unk_DB0E2BAB *)sp98)->unk0x20 * ((Unk_DB0E2BAB *)temp_r31)->unk0x4) + (((Unk_DB0E2BAB *)sp98)->unk0x24 * ((Unk_DB0E2BAB *)temp_r31)->unk0x14)));
                sp80 = (((Unk_DB0E2BAB *)sp98)->unk0x2C * ((Unk_DB0E2BAB *)temp_r31)->unk0x38) + ((((Unk_DB0E2BAB *)sp98)->unk0x28 * ((Unk_DB0E2BAB *)temp_r31)->unk0x28) + ((((Unk_DB0E2BAB *)sp98)->unk0x20 * ((Unk_DB0E2BAB *)temp_r31)->unk0x8) + (((Unk_DB0E2BAB *)sp98)->unk0x24 * ((Unk_DB0E2BAB *)temp_r31)->unk0x18)));
                sp84 = (((Unk_DB0E2BAB *)sp98)->unk0x2C * ((Unk_DB0E2BAB *)temp_r31)->unk0x3C) + ((((Unk_DB0E2BAB *)sp98)->unk0x28 * ((Unk_DB0E2BAB *)temp_r31)->unk0x2C) + ((((Unk_DB0E2BAB *)sp98)->unk0x20 * ((Unk_DB0E2BAB *)temp_r31)->unk0xC) + (((Unk_DB0E2BAB *)sp98)->unk0x24 * ((Unk_DB0E2BAB *)temp_r31)->unk0x1C)));
                sp88 = (((Unk_DB0E2BAB *)sp98)->unk0x3C * ((Unk_DB0E2BAB *)temp_r31)->unk0x30) + ((((Unk_DB0E2BAB *)sp98)->unk0x38 * ((Unk_DB0E2BAB *)temp_r31)->unk0x20) + ((((Unk_DB0E2BAB *)sp98)->unk0x30 * ((Unk_C7387A53 *)temp_r3_2)->unk0x78) + (((Unk_DB0E2BAB *)sp98)->unk0x34 * ((Unk_DB0E2BAB *)temp_r31)->unk0x10)));
                sp8C = (((Unk_DB0E2BAB *)sp98)->unk0x3C * ((Unk_DB0E2BAB *)temp_r31)->unk0x34) + ((((Unk_DB0E2BAB *)sp98)->unk0x38 * ((Unk_DB0E2BAB *)temp_r31)->unk0x24) + ((((Unk_DB0E2BAB *)sp98)->unk0x30 * ((Unk_DB0E2BAB *)temp_r31)->unk0x4) + (((Unk_DB0E2BAB *)sp98)->unk0x34 * ((Unk_DB0E2BAB *)temp_r31)->unk0x14)));
                sp90 = (((Unk_DB0E2BAB *)sp98)->unk0x3C * ((Unk_DB0E2BAB *)temp_r31)->unk0x38) + ((((Unk_DB0E2BAB *)sp98)->unk0x38 * ((Unk_DB0E2BAB *)temp_r31)->unk0x28) + ((((Unk_DB0E2BAB *)sp98)->unk0x30 * ((Unk_DB0E2BAB *)temp_r31)->unk0x8) + (((Unk_DB0E2BAB *)sp98)->unk0x34 * ((Unk_DB0E2BAB *)temp_r31)->unk0x18)));
                sp94 = (((Unk_DB0E2BAB *)sp98)->unk0x3C * ((Unk_DB0E2BAB *)temp_r31)->unk0x3C) + ((((Unk_DB0E2BAB *)sp98)->unk0x38 * ((Unk_DB0E2BAB *)temp_r31)->unk0x2C) + ((((Unk_DB0E2BAB *)sp98)->unk0x30 * ((Unk_DB0E2BAB *)temp_r31)->unk0xC) + (((Unk_DB0E2BAB *)sp98)->unk0x34 * ((Unk_DB0E2BAB *)temp_r31)->unk0x1C)));
                0;
                0;
                0;
                0;
                0;
                0;
                *((f32 *)&sp18) = temp_f31;
                ((Unk_560A7BB5 *)&sp18)->unk0x4 = lbl_802AFD60;
                sp18.unk0xC = temp_f31;
                sp18.unk0x8 = temp_f31;
                ((Unk_DB0E2BAB *)temp_r31)->unk0x30 = (f32) (((Unk_DB0E2BAB *)temp_r31)->unk0x30 + ((sp20 * ((Unk_DB0E2BAB *)temp_r31)->unk0x20) + ((*((f32 *)&sp18) * ((Unk_C7387A53 *)temp_r3_2)->unk0x78) + (sp1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x10))));
                *((f32 *)&temp_r11->unk0x4) = (f32) (*((f32 *)&temp_r11->unk0x4) + ((sp20 * ((Unk_DB0E2BAB *)temp_r31)->unk0x24) + ((*((f32 *)&sp18) * ((Unk_DB0E2BAB *)temp_r31)->unk0x4) + (sp1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x14))));
                *((f32 *)&temp_r11->unk0x8) = (f32) (*((f32 *)&temp_r11->unk0x8) + ((sp20 * ((Unk_DB0E2BAB *)temp_r31)->unk0x28) + ((*((f32 *)&sp18) * ((Unk_DB0E2BAB *)temp_r31)->unk0x8) + (sp1C * ((Unk_DB0E2BAB *)temp_r31)->unk0x18))));
                0;
                *((f32 *)&sp28) = temp_f31;
                ((Unk_E266FB50 *)&sp28)->unk0xC = lbl_802AFD64;
                sp28.unk0x4 = temp_f31;
                sp28.unk0x8 = temp_f31;
                0;
                0;
                temp_r11_2 = var_r26->unk0x18;
                spA0 = temp_r31;
                temp_r10 = temp_r11_2 + 0x78;
                ((Unk_59AB5482 *)&spA0)->unk0x4 = temp_r10;
                *((f32 *)&sp28) = (((Unk_DB0E2BAB *)spA0)->unk0xC * ((Unk_6A70655D *)temp_r11_2)->unk0xA8) + ((((Unk_DB0E2BAB *)spA0)->unk0x8 * ((Unk_6A70655D *)temp_r11_2)->unk0x98) + ((((Unk_DB0E2BAB *)spA0)->unk0x0 * ((Unk_6A70655D *)temp_r11_2)->unk0x78) + (((Unk_DB0E2BAB *)spA0)->unk0x4 * ((Unk_6A70655D *)temp_r11_2)->unk0x88)));
                sp2C = (((Unk_DB0E2BAB *)spA0)->unk0xC * ((Unk_6A70655D *)temp_r11_2)->unk0xAC) + ((((Unk_DB0E2BAB *)spA0)->unk0x8 * ((Unk_6A70655D *)temp_r11_2)->unk0x9C) + ((((Unk_DB0E2BAB *)spA0)->unk0x0 * ((Unk_6A70655D *)temp_r11_2)->unk0x7C) + (((Unk_DB0E2BAB *)spA0)->unk0x4 * ((Unk_6A70655D *)temp_r11_2)->unk0x8C)));
                sp30 = (((Unk_DB0E2BAB *)spA0)->unk0xC * ((Unk_6A70655D *)temp_r11_2)->unk0xB0) + ((((Unk_DB0E2BAB *)spA0)->unk0x8 * ((Unk_6A70655D *)temp_r11_2)->unk0xA0) + ((((Unk_DB0E2BAB *)spA0)->unk0x0 * ((Unk_6A70655D *)temp_r11_2)->unk0x80) + (((Unk_DB0E2BAB *)spA0)->unk0x4 * ((Unk_6A70655D *)temp_r11_2)->unk0x90)));
                sp34 = (((Unk_DB0E2BAB *)spA0)->unk0xC * ((Unk_6A70655D *)temp_r11_2)->unk0xB4) + ((((Unk_DB0E2BAB *)spA0)->unk0x8 * ((Unk_6A70655D *)temp_r11_2)->unk0xA4) + ((((Unk_DB0E2BAB *)spA0)->unk0x0 * ((Unk_6A70655D *)temp_r11_2)->unk0x84) + (((Unk_DB0E2BAB *)spA0)->unk0x4 * ((Unk_6A70655D *)temp_r11_2)->unk0x94)));
                sp38 = (((Unk_DB0E2BAB *)spA0)->unk0x1C * ((Unk_6A70655D *)temp_r11_2)->unk0xA8) + ((((Unk_DB0E2BAB *)spA0)->unk0x18 * ((Unk_6A70655D *)temp_r11_2)->unk0x98) + ((((Unk_DB0E2BAB *)spA0)->unk0x10 * ((Unk_6A70655D *)temp_r11_2)->unk0x78) + (((Unk_DB0E2BAB *)spA0)->unk0x14 * ((Unk_6A70655D *)temp_r11_2)->unk0x88)));
                sp3C = (((Unk_DB0E2BAB *)spA0)->unk0x1C * ((Unk_6A70655D *)temp_r11_2)->unk0xAC) + ((((Unk_DB0E2BAB *)spA0)->unk0x18 * ((Unk_6A70655D *)temp_r11_2)->unk0x9C) + ((((Unk_DB0E2BAB *)spA0)->unk0x10 * ((Unk_6A70655D *)temp_r11_2)->unk0x7C) + (((Unk_DB0E2BAB *)spA0)->unk0x14 * ((Unk_6A70655D *)temp_r11_2)->unk0x8C)));
                sp40 = (((Unk_DB0E2BAB *)spA0)->unk0x1C * ((Unk_6A70655D *)temp_r11_2)->unk0xB0) + ((((Unk_DB0E2BAB *)spA0)->unk0x18 * ((Unk_6A70655D *)temp_r11_2)->unk0xA0) + ((((Unk_DB0E2BAB *)spA0)->unk0x10 * ((Unk_6A70655D *)temp_r11_2)->unk0x80) + (((Unk_DB0E2BAB *)spA0)->unk0x14 * ((Unk_6A70655D *)temp_r11_2)->unk0x90)));
                sp44 = (((Unk_DB0E2BAB *)spA0)->unk0x1C * ((Unk_6A70655D *)temp_r11_2)->unk0xB4) + ((((Unk_DB0E2BAB *)spA0)->unk0x18 * ((Unk_6A70655D *)temp_r11_2)->unk0xA4) + ((((Unk_DB0E2BAB *)spA0)->unk0x10 * ((Unk_6A70655D *)temp_r11_2)->unk0x84) + (((Unk_DB0E2BAB *)spA0)->unk0x14 * ((Unk_6A70655D *)temp_r11_2)->unk0x94)));
                sp48 = (((Unk_DB0E2BAB *)spA0)->unk0x2C * ((Unk_6A70655D *)temp_r11_2)->unk0xA8) + ((((Unk_DB0E2BAB *)spA0)->unk0x28 * ((Unk_6A70655D *)temp_r11_2)->unk0x98) + ((((Unk_DB0E2BAB *)spA0)->unk0x20 * ((Unk_6A70655D *)temp_r11_2)->unk0x78) + (((Unk_DB0E2BAB *)spA0)->unk0x24 * ((Unk_6A70655D *)temp_r11_2)->unk0x88)));
                sp4C = (((Unk_DB0E2BAB *)spA0)->unk0x2C * ((Unk_6A70655D *)temp_r11_2)->unk0xAC) + ((((Unk_DB0E2BAB *)spA0)->unk0x28 * ((Unk_6A70655D *)temp_r11_2)->unk0x9C) + ((((Unk_DB0E2BAB *)spA0)->unk0x20 * ((Unk_6A70655D *)temp_r11_2)->unk0x7C) + (((Unk_DB0E2BAB *)spA0)->unk0x24 * ((Unk_6A70655D *)temp_r11_2)->unk0x8C)));
                sp50 = (((Unk_DB0E2BAB *)spA0)->unk0x2C * ((Unk_6A70655D *)temp_r11_2)->unk0xB0) + ((((Unk_DB0E2BAB *)spA0)->unk0x28 * ((Unk_6A70655D *)temp_r11_2)->unk0xA0) + ((((Unk_DB0E2BAB *)spA0)->unk0x20 * ((Unk_6A70655D *)temp_r11_2)->unk0x80) + (((Unk_DB0E2BAB *)spA0)->unk0x24 * ((Unk_6A70655D *)temp_r11_2)->unk0x90)));
                sp54 = (((Unk_DB0E2BAB *)spA0)->unk0x2C * ((Unk_6A70655D *)temp_r11_2)->unk0xB4) + ((((Unk_DB0E2BAB *)spA0)->unk0x28 * ((Unk_6A70655D *)temp_r11_2)->unk0xA4) + ((((Unk_DB0E2BAB *)spA0)->unk0x20 * ((Unk_6A70655D *)temp_r11_2)->unk0x84) + (((Unk_DB0E2BAB *)spA0)->unk0x24 * ((Unk_6A70655D *)temp_r11_2)->unk0x94)));
                sp58 = (((Unk_DB0E2BAB *)spA0)->unk0x3C * ((Unk_6A70655D *)temp_r11_2)->unk0xA8) + ((((Unk_DB0E2BAB *)spA0)->unk0x38 * ((Unk_6A70655D *)temp_r11_2)->unk0x98) + ((((Unk_DB0E2BAB *)spA0)->unk0x30 * ((Unk_6A70655D *)temp_r11_2)->unk0x78) + (((Unk_DB0E2BAB *)spA0)->unk0x34 * ((Unk_6A70655D *)temp_r11_2)->unk0x88)));
                sp5C = (((Unk_DB0E2BAB *)spA0)->unk0x3C * ((Unk_6A70655D *)temp_r11_2)->unk0xAC) + ((((Unk_DB0E2BAB *)spA0)->unk0x38 * ((Unk_6A70655D *)temp_r11_2)->unk0x9C) + ((((Unk_DB0E2BAB *)spA0)->unk0x30 * ((Unk_6A70655D *)temp_r11_2)->unk0x7C) + (((Unk_DB0E2BAB *)spA0)->unk0x34 * ((Unk_6A70655D *)temp_r11_2)->unk0x8C)));
                sp60 = (((Unk_DB0E2BAB *)spA0)->unk0x3C * ((Unk_6A70655D *)temp_r11_2)->unk0xB0) + ((((Unk_DB0E2BAB *)spA0)->unk0x38 * ((Unk_6A70655D *)temp_r11_2)->unk0xA0) + ((((Unk_DB0E2BAB *)spA0)->unk0x30 * ((Unk_6A70655D *)temp_r11_2)->unk0x80) + (((Unk_DB0E2BAB *)spA0)->unk0x34 * ((Unk_6A70655D *)temp_r11_2)->unk0x90)));
                sp64 = (((Unk_DB0E2BAB *)spA0)->unk0x3C * temp_r10->unk0x3C) + ((((Unk_DB0E2BAB *)spA0)->unk0x38 * ((Unk_6A70655D *)temp_r11_2)->unk0xA4) + ((((Unk_DB0E2BAB *)spA0)->unk0x30 * ((Unk_6A70655D *)temp_r11_2)->unk0x84) + (((Unk_DB0E2BAB *)spA0)->unk0x34 * ((Unk_6A70655D *)temp_r11_2)->unk0x94)));
                0;
                0;
                0;
                0;
                0;
                0;
                temp_r9 = var_r26->unk0x18;
                sp38 = (sp24 * temp_r9->unk0xA8) + ((sp20 * temp_r9->unk0x98) + ((*((f32 *)&sp18) * temp_r9->unk0x78) + (sp1C * temp_r9->unk0x88)));
                sp3C = (sp24 * temp_r9->unk0xAC) + ((sp20 * temp_r9->unk0x9C) + ((*((f32 *)&sp18) * temp_r9->unk0x7C) + (sp1C * temp_r9->unk0x8C)));
                sp40 = (sp24 * temp_r9->unk0xB0) + ((sp20 * temp_r9->unk0xA0) + ((*((f32 *)&sp18) * temp_r9->unk0x80) + (sp1C * temp_r9->unk0x90)));
                sp44 = (sp24 * temp_r9->unk0xB4) + ((sp20 * temp_r9->unk0xA4) + ((*((f32 *)&sp18) * temp_r9->unk0x84) + (sp1C * temp_r9->unk0x94)));
                0;
                0;
                0;
                0;
                0;
                goto block_21;
            }
        } else {
block_21:
            var_r26 = fn_8021D4E8(temp_r20, &sp8, 0);
            if (var_r26 != NULL) {
                goto loop_4;
            }
        }
    }
    sp8.unk0x8 = (s32)lbl_802A83F8;
}
