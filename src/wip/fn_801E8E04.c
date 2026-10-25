// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group-I)
// family=m2c range=0x801E8E04-0x801E97CC size=2504B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: 17.5% (compile with --extra-cflags "-mps-float") -
// allocator/scratch-role residue after a full structural rebuild.
// m2c baseline was broken (wrong frame, unprototyped callees, invented
// mid-function bls -> 12%). Hand-rebuilt body now matches want byte-for-byte
// through the list-cleanup section (first diff at +0x190). Levers that landed:
// r31 local pin models the zero->mgrList register recycling; r29 pin models
// the look web; staged tp timer pointers; old-style s32 Tmr_GetTime(); proto
// for raw-r3 passthrough; chained Mem_Free()->Tmr_GetTime() bare calls;
// EC22C out-param pair-copy semantics (&fr[0]/&fr[2] pairs, pp web kept alive
// via ((__ps_t*)pp)[k]); D+(C+(A+B)) dot-product trees per S7b-153;
// omc-before-call statement order.
// REMAINING (all inside the two matrix blocks): (a) obj web homed in recycled
// saved r31 where want keeps it in scratch r9, bm in r9 vs want r11 (b1 did
// flip to r11 once om's home changed - the two webs trade); (b) FPR colors
// shifted accordingly (f12/f13 vs want f13/f0 families); (c) pp birth order
// (got addi r30,r1,8 first vs want addi r3,r1,8 + mr r30,r3). Adding ANY
// further local hard-reg pin (r9 for om, r10 for the arg0+0x20 base) or
// named pointer local collapses allocation: stmw shrinks to r28, arg0 loses
// its r28 home, frame shifts (-0x68) -> 0.5%. Same failure signature each
// time = brittle allocator wall for this function; retry only if a new
// technique for forcing scratch-reg homes without pins appears.
// FLAG: -mps-float -Os
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 17.9%.
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303150;
extern f32 lbl_802AD888;
extern s32 lbl_80305EAC;
extern s32 lbl_80305F04;
extern char lbl_802ADA40[];
extern char lbl_802ADA34[];
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 *fn_801090B8(s32 *, s32);
s32 Tmr_GetTime();
s32 Mem_Free(void *);
void fn_800EC22C(void *, Unk_C7387A53 *);
s32 fn_801A6F44(void *, s32);
void fn_801A6F8C(void *, s32);
s32 Script_GetInteger(s32);
void fn_801A3E4C(Unk_C8FEE62D *);
void fn_801EC620(Unk_7258DEBD *);
s32 fn_801DE800(Unk_9AE08789 *);
void fn_801EC3F0(Unk_83A1E37F *, void *);
void fn_800F0F84(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8020C58C(s32, s32);
void fn_801E8E04(Unk_DBD6490B *arg0) {
    f32 fr[20];
    __ps_t *pp;
    s32 var_r11;
    s32 var_r0;
    void *listArg;
    s32 *head;
    s32 *head2;
    register s32 look __asm__("r29");
    s32 *lookp;
    Unk_4C649A8C *tp;
    register s32 var_r31 __asm__("r31");
    Unk_6A70655D *om;
    Unk_DF2324A8 *omc;
    Unk_12C58B0B *b1;
    Unk_12C58B0B *b2;
    f32 tf0;
    s32 eacp;
    var_r31 = 0;
    tp = (char *)arg0->unk0x15BC + 0xA8;
    if (tp->unk0x4 != 0) {
        tp->unk0x4 = var_r31;
        tp->unk0x8 = lbl_80303150 + Tmr_GetTime();
    }
    tp = (char *)arg0->unk0x15BC + 0xF0;
    if (tp->unk0x4 != 0) {
        tp->unk0x4 = var_r31;
        tp->unk0x8 = lbl_80303150 + Tmr_GetTime();
    }
    tp = (char *)arg0->unk0x15BC + 0xB4;
    if (tp->unk0x4 != 0) {
        tp->unk0x4 = var_r31;
        tp->unk0x8 = lbl_80303150 + Tmr_GetTime();
    }
    arg0->unk0x334 = var_r31;
    var_r31 = arg0->unk0x15C0;
    head = ((Unk_C8FEE62D *)var_r31)->unk0x1C;
    listArg = (char *)(arg0->unk0xC) + 0x58;
    if (head == NULL) {
        var_r11 = 0;
    } else {
        look = *head;
        if (look != 0) {
            var_r11 = 1;
        } else {
            ((Unk_C8FEE62D *)var_r31)->unk0x70 = look;
            if (*head != 0) {
                CObject_RemoveRefLink((void *)*head, head);
            }
            *head = look;
            Mem_Free(head);
            ((Unk_C8FEE62D *)var_r31)->unk0x1C = look;
            ((Unk_C8FEE62D *)var_r31)->unk0x74 = lbl_80303150 + Tmr_GetTime();
            var_r11 = 0;
        }
    }
    if (var_r11 != 0) {
        look = (s32)fn_801090B8(((Unk_C8FEE62D *)var_r31)->unk0x1C, (void *)listArg);
        if (look != 0) {
            var_r0 = 1;
        } else {
            head2 = ((Unk_C8FEE62D *)var_r31)->unk0x1C;
            if (head2 != NULL) {
                ((Unk_C8FEE62D *)var_r31)->unk0x70 = *head2;
                if (*head2 != 0) {
                    CObject_RemoveRefLink((void *)*head2, head2);
                }
                *head2 = look;
                Mem_Free(head2);
                ((Unk_C8FEE62D *)var_r31)->unk0x1C = look;
                ((Unk_C8FEE62D *)var_r31)->unk0x74 = lbl_80303150 + Tmr_GetTime();
            }
            var_r0 = 0;
        }
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        omc = arg0->unk0xC;
        pp = (__ps_t *)&fr[0];
        __asm__("" : "+r"(pp));
        fn_800EC22C((void *)pp, arg0->unk0x15C0);
        omc->unk0x58 = *(__ps_t *)&fr[0];
        omc->unk0x60 = ((__ps_t *)pp)[0];
        fn_800EC22C((void *)pp, arg0->unk0x15C0);
        arg0->unk0x2A0 = ((__ps_t *)pp)[1];
        arg0->unk0x298 = *(__ps_t *)&fr[0];
        b1 = ((Unk_31DE137E *)arg0->unk0x15C0)->unk0x1C;
        if (b1->unk0xB0 != 0) {
            fr[4] = *((f32 *)&om->unk0x84) * b1->unk0xA0 + (*((f32 *)&om->unk0x80) * b1->unk0x90 + (*((f32 *)&om->unk0x78) * b1->unk0x70 + *((f32 *)&om->unk0x7C) * b1->unk0x80));
            fr[5] = *((f32 *)&om->unk0x84) * b1->unk0xA4 + (*((f32 *)&om->unk0x80) * b1->unk0x94 + (*((f32 *)&om->unk0x78) * b1->unk0x74 + *((f32 *)&om->unk0x7C) * b1->unk0x84));
            fr[6] = *((f32 *)&om->unk0x84) * b1->unk0xA8 + (*((f32 *)&om->unk0x80) * b1->unk0x98 + (*((f32 *)&om->unk0x78) * b1->unk0x78 + *((f32 *)&om->unk0x7C) * b1->unk0x88));
            fr[7] = *((f32 *)&om->unk0x84) * b1->unk0xAC + (*((f32 *)&om->unk0x80) * b1->unk0x9C + (*((f32 *)&om->unk0x78) * b1->unk0x7C + *((f32 *)&om->unk0x7C) * b1->unk0x8C));
            fr[8] = *((f32 *)&om->unk0x94) * b1->unk0xA0 + (*((f32 *)&om->unk0x90) * b1->unk0x90 + (*((f32 *)&om->unk0x88) * b1->unk0x70 + *((f32 *)&om->unk0x8C) * b1->unk0x80));
            fr[9] = *((f32 *)&om->unk0x94) * b1->unk0xA4 + (*((f32 *)&om->unk0x90) * b1->unk0x94 + (*((f32 *)&om->unk0x88) * b1->unk0x74 + *((f32 *)&om->unk0x8C) * b1->unk0x84));
            fr[10] = *((f32 *)&om->unk0x94) * b1->unk0xA8 + (*((f32 *)&om->unk0x90) * b1->unk0x98 + (*((f32 *)&om->unk0x88) * b1->unk0x78 + *((f32 *)&om->unk0x8C) * b1->unk0x88));
            fr[11] = *((f32 *)&om->unk0x94) * b1->unk0xAC + (*((f32 *)&om->unk0x90) * b1->unk0x9C + (*((f32 *)&om->unk0x88) * b1->unk0x7C + *((f32 *)&om->unk0x8C) * b1->unk0x8C));
            fr[12] = *((f32 *)&om->unk0xA4) * b1->unk0xA0 + (*((f32 *)&om->unk0xA0) * b1->unk0x90 + (*((f32 *)&om->unk0x98) * b1->unk0x70 + *((f32 *)&om->unk0x9C) * b1->unk0x80));
            fr[13] = *((f32 *)&om->unk0xA4) * b1->unk0xA4 + (*((f32 *)&om->unk0xA0) * b1->unk0x94 + (*((f32 *)&om->unk0x98) * b1->unk0x74 + *((f32 *)&om->unk0x9C) * b1->unk0x84));
            fr[14] = *((f32 *)&om->unk0xA4) * b1->unk0xA8 + (*((f32 *)&om->unk0xA0) * b1->unk0x98 + (*((f32 *)&om->unk0x98) * b1->unk0x78 + *((f32 *)&om->unk0x9C) * b1->unk0x88));
            fr[15] = *((f32 *)&om->unk0xA4) * b1->unk0xAC + (*((f32 *)&om->unk0xA0) * b1->unk0x9C + (*((f32 *)&om->unk0x98) * b1->unk0x7C + *((f32 *)&om->unk0x9C) * b1->unk0x8C));
            fr[16] = *((f32 *)&om->unk0xB4) * b1->unk0xA0 + (*((f32 *)&om->unk0xB0) * b1->unk0x90 + (*((f32 *)&om->unk0xA8) * b1->unk0x70 + *((f32 *)&om->unk0xAC) * b1->unk0x80));
            fr[17] = *((f32 *)&om->unk0xB4) * b1->unk0xA4 + (*((f32 *)&om->unk0xB0) * b1->unk0x94 + (*((f32 *)&om->unk0xA8) * b1->unk0x74 + *((f32 *)&om->unk0xAC) * b1->unk0x84));
            fr[18] = *((f32 *)&om->unk0xB4) * b1->unk0xA8 + (*((f32 *)&om->unk0xB0) * b1->unk0x98 + (*((f32 *)&om->unk0xA8) * b1->unk0x78 + *((f32 *)&om->unk0xAC) * b1->unk0x88));
            fr[19] = *((f32 *)&om->unk0xB4) * b1->unk0xAC + (*((f32 *)&om->unk0xB0) * b1->unk0x9C + (*((f32 *)&om->unk0xA8) * b1->unk0x7C + *((f32 *)&om->unk0xAC) * b1->unk0x8C));
            __asm__("" : "=r"(om) : "r"(arg0->unk0xC));
            *((__ps_t *)&om->unk0x78) = *(__ps_t *)&fr[4];
            *((__ps_t *)&om->unk0x80) = *(__ps_t *)&fr[6];
            *((__ps_t *)&om->unk0x88) = *(__ps_t *)&fr[8];
            *((__ps_t *)&om->unk0x90) = *(__ps_t *)&fr[10];
            *((__ps_t *)&om->unk0x98) = *(__ps_t *)&fr[12];
            *((__ps_t *)&om->unk0xA0) = *(__ps_t *)&fr[14];
            *((__ps_t *)&om->unk0xA8) = *(__ps_t *)&fr[16];
            *((__ps_t *)&om->unk0xB0) = *(__ps_t *)&fr[18];
            b2 = ((Unk_31DE137E *)arg0->unk0x15C0)->unk0x1C;
            fr[0] = arg0->unk0x2C * b2->unk0xA0 + (((Unk_F7C2FA01 *)arg0)->unk0x28 * b2->unk0x90 + (((Unk_F7C2FA01 *)arg0)->unk0x20 * b2->unk0x70 + arg0->unk0x24 * b2->unk0x80));
            fr[1] = arg0->unk0x2C * b2->unk0xA4 + (((Unk_F7C2FA01 *)arg0)->unk0x28 * b2->unk0x94 + (((Unk_F7C2FA01 *)arg0)->unk0x20 * b2->unk0x74 + arg0->unk0x24 * b2->unk0x84));
            fr[2] = arg0->unk0x2C * b2->unk0xA8 + (((Unk_F7C2FA01 *)arg0)->unk0x28 * b2->unk0x98 + (((Unk_F7C2FA01 *)arg0)->unk0x20 * b2->unk0x78 + arg0->unk0x24 * b2->unk0x88));
            fr[3] = arg0->unk0x2C * b2->unk0xAC + (((Unk_F7C2FA01 *)arg0)->unk0x28 * b2->unk0x9C + (((Unk_F7C2FA01 *)arg0)->unk0x20 * b2->unk0x7C + arg0->unk0x24 * b2->unk0x8C));
            fr[4] = arg0->unk0x3C * b2->unk0xA0 + (((Unk_F7C2FA01 *)arg0)->unk0x38 * b2->unk0x90 + (((Unk_F7C2FA01 *)arg0)->unk0x30 * b2->unk0x70 + arg0->unk0x34 * b2->unk0x80));
            fr[5] = arg0->unk0x3C * b2->unk0xA4 + (((Unk_F7C2FA01 *)arg0)->unk0x38 * b2->unk0x94 + (((Unk_F7C2FA01 *)arg0)->unk0x30 * b2->unk0x74 + arg0->unk0x34 * b2->unk0x84));
            fr[6] = arg0->unk0x3C * b2->unk0xA8 + (((Unk_F7C2FA01 *)arg0)->unk0x38 * b2->unk0x98 + (((Unk_F7C2FA01 *)arg0)->unk0x30 * b2->unk0x78 + arg0->unk0x34 * b2->unk0x88));
            fr[7] = arg0->unk0x3C * b2->unk0xAC + (((Unk_F7C2FA01 *)arg0)->unk0x38 * b2->unk0x9C + (((Unk_F7C2FA01 *)arg0)->unk0x30 * b2->unk0x7C + arg0->unk0x34 * b2->unk0x8C));
            fr[8] = arg0->unk0x4C * b2->unk0xA0 + (((Unk_F7C2FA01 *)arg0)->unk0x48 * b2->unk0x90 + (((Unk_F7C2FA01 *)arg0)->unk0x40 * b2->unk0x70 + arg0->unk0x44 * b2->unk0x80));
            fr[9] = arg0->unk0x4C * b2->unk0xA4 + (((Unk_F7C2FA01 *)arg0)->unk0x48 * b2->unk0x94 + (((Unk_F7C2FA01 *)arg0)->unk0x40 * b2->unk0x74 + arg0->unk0x44 * b2->unk0x84));
            fr[10] = arg0->unk0x4C * b2->unk0xA8 + (((Unk_F7C2FA01 *)arg0)->unk0x48 * b2->unk0x98 + (((Unk_F7C2FA01 *)arg0)->unk0x40 * b2->unk0x78 + arg0->unk0x44 * b2->unk0x88));
            fr[11] = arg0->unk0x4C * b2->unk0xAC + (((Unk_F7C2FA01 *)arg0)->unk0x48 * b2->unk0x9C + (((Unk_F7C2FA01 *)arg0)->unk0x40 * b2->unk0x7C + arg0->unk0x44 * b2->unk0x8C));
            fr[12] = arg0->unk0x5C * b2->unk0xA0 + (((Unk_F7C2FA01 *)arg0)->unk0x58 * b2->unk0x90 + (((Unk_F7C2FA01 *)arg0)->unk0x50 * b2->unk0x70 + arg0->unk0x54 * b2->unk0x80));
            fr[13] = arg0->unk0x5C * b2->unk0xA4 + (((Unk_F7C2FA01 *)arg0)->unk0x58 * b2->unk0x94 + (((Unk_F7C2FA01 *)arg0)->unk0x50 * b2->unk0x74 + arg0->unk0x54 * b2->unk0x84));
            fr[14] = arg0->unk0x5C * b2->unk0xA8 + (((Unk_F7C2FA01 *)arg0)->unk0x58 * b2->unk0x98 + (((Unk_F7C2FA01 *)arg0)->unk0x50 * b2->unk0x78 + arg0->unk0x54 * b2->unk0x88));
            fr[15] = arg0->unk0x5C * b2->unk0xAC + (((Unk_F7C2FA01 *)arg0)->unk0x58 * b2->unk0x9C + (((Unk_F7C2FA01 *)arg0)->unk0x50 * b2->unk0x7C + arg0->unk0x54 * b2->unk0x8C));
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x20) = *(__ps_t *)&fr[0];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x28) = *(__ps_t *)&fr[2];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x30) = *(__ps_t *)&fr[4];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x38) = *(__ps_t *)&fr[6];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x40) = *(__ps_t *)&fr[8];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x48) = *(__ps_t *)&fr[10];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x50) = *(__ps_t *)&fr[12];
            *((__ps_t *)&((Unk_F7C2FA01 *)arg0)->unk0x58) = *(__ps_t *)&fr[14];
        }
    }
    if (((Unk_31DE137E *)arg0->unk0x15B8)->unk0x1C == QB_LIP) {
        if (fn_801A6F44((void *)*(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x24), QB_CHEAT_PERFECT_RAIL) != 0) {
            eacp = *(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x24);
            fn_801A6F8C((void *)eacp, Script_GetInteger(QB_CHEAT_PERFECT_RAIL));
            tf0 = lbl_802AD888;
            *(f32 *)((char *)arg0->unk0x15B8 + 0x13C) = tf0;
            *(f32 *)((char *)arg0->unk0x15B8 + 0x140) = tf0;
            lbl_80305F04 = 1;
        }
        fn_801A3E4C((void *)(arg0->unk0x15B8 + 0x108));
    }
    fn_801EC620(arg0);
    if (fn_801DE800(arg0) != 0) {
        tp = (char *)arg0->unk0x15BC + 0x138;
        if (tp->unk0x4 != 1) {
            tp->unk0x4 = 1;
            tp->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
        fn_801EC3F0(arg0, (s32)lbl_802ADA40);
        fn_801EC3F0(arg0, (s32)lbl_802ADA34);
    }
    head2 = arg0->unk0x25C;
    if ((head2 != 0) && (((Unk_C7387A53 *)arg0->unk0x260)->unk0x4C != 0)) {
        fn_800F0F84(((Unk_C7387A53 *)head2)->unk0x54, 1);
        GetChecksum_2(arg0, QB_NAME, (void *)((char *)arg0 + 0x270), 1);
        fn_8020C58C(arg0->unk0x15AC, arg0->unk0x270);
    }
    arg0->unk0x268 = lbl_80303150 + Tmr_GetTime();
}
