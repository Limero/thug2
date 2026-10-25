// WIP DRAFT (non-matching) — hand-decoded structure notes below.
// family=m2c range=0x80218564-0x80218EB0 size=2380B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 3.9%: m2c statics-DCE husk (compiled ~18 insns vs want's 461).
// 2380B spawn/create function = multi-session hand-rebuild per doc §6ai-158.
// Structure decoded from want disasm:
//
// FRAME: stwu -0x10D8 (4300B!); mfcr r12; stmw r14,0x1090 (r14..r31, 18 GPRs);
//   stw r12,0x108C (CR save => doc-28 CR liveness across many bl calls);
//   big stack buffers: name buffer @r1+0x38-ish (strcpy target), search_t
//   out-params @+0x58, sp1070/sp1068 walker-state pair near top.
// PROLOGUE: r30=arg0; mgr=*(s32*)lbl_802FFE98 (lis/lwz -0x168(r9));
//   fn_8000F2F8(mgr, *(mgr+0x5F8)); obj=*(r30+0x20); r25=*(obj+0x154) head;
//   sentinel check -> var_r19; cat=*(s32*)&lbl_80305EAC; fn_80137CB4(&sp10).
// LOOP (per list entry):
// 1. r18=1 if fn_8013FB8C(*(entry+0x14))==1 || fn_80137AD4(mgr)==1.
// 2. re-lock mgr via fn_8000F2F8/F320 around fn_8021B830(obj,0,*(e+0x14),
//    *(e+0x20)) -> new object r28; strcpy(r28+0x3C, entry+1);
//    fn_80229810(r28, *(e+0x1C)); field copies +0x1E0/0x2C/0x30/0x4C;
//    zero +0x24/+0x20; fn_8021C7CC(obj,new); sp107C = fn_800145AC().
// 3. t = fn_8022986C(new); if NULL: build message block (sp50/sp51/sp38/
//    sp3C/sp54/sp44/sp4C/sp48/sp58 fields; sp40 flags from
//    *(new+0x1D8)&0x10 and fn_8022989C(new)|4) then TWO fn_8013CC84 emits
//    via *(obj+8), arg1 = fn_8022A9B8(new), stacked out-param structs.
// 4. Three sibling-walk loops over fn_8021D454/D4E8(obj,&sp1068,flag):
//    emit per matching entries; middle gated by ((flags&0x10)==0); third arm
//    handles fn_80228840 lookup + 0xB664035D hash case calling fn_80233294 /
//    fn_802332B8 / fn_801FC0E0 x2 / fn_801FA284 and fn_8013DC7C twice
//    (0x6C/0x3A98 and 0x88/0x1132, strings lbl_802AFD94/lbl_802AFDA0).
// 5. count walk of *(sp1080)->0x38 chain for fn_80173024(sp1080, *(e+0x1C),
//    fn_8013F74C(*(new+0x1C)), *(e+0x11), count) -> fn_80229644(new,t);
//    if unlinked fn_80145058(t). Per-sibling 0x25 emits + fn_80145008 +
//    fn_8022A860 updates; final self 0x25 emit + fn_8022A860(new,sp107C).
// 6. dead-looking tail guarded by if(0): fn_8022AABC(entry,3) and vcall
//    through entry->0x14 table (lha offset at +8, fn-ptr at +0xC, 3).
// EXIT: fn_8000F320(*(s32*)lbl_802FFE98); label store to walker-state slot.
// RESISTED: statics-DCE ate every stack slot; rebuild needs buffers sized
// from callee max-stores (§6v-120), doc-28 CR machinery route, exact roles
// for 18 saved GPRs.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 3.0% ([5]rev->3.0%).

#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
static s32 sp1080;
static s32 sp14;
static s32 sp44;
static s32 sp48;
static s32 sp4C;

void fn_80218564(Unk_C7387A53 *arg0) {
    s32 sp108C;
    s32 sp1084;
    Unk_C7387A53 *sp1080;
    s32 sp107C;
    s32 sp1078;
    s32 sp1070;
    Unk_59AB5482 sp1068;
    s32 sp68;
    s32 sp58;
    s32 sp54;
    u8 sp51;
    u8 sp50;
    s32 *sp4C;
    s32 *sp48;
    s32 *sp44;
    s32 sp40;                                       
    s32 sp3C;
    s32 sp38;
    s8 sp30;
    s8 sp20;
    s32 sp1C;
    s32 sp18;
    s32 *sp14;
    s16 sp12;
    s8 sp10;
    s32 sp8;
    s32 var_r18;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s32 *temp_r3_3;
    s32 *temp_r3_4;
    s32 *temp_r3_7;
    s32 temp_cr0_eq;
    s32 temp_r29_2;
    s32 temp_r30_6;
    s32 temp_r30_7;
    s32 temp_r3_8;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 var_r30;
    s32 var_r7;
    s32 var_r9;
    s32 var_r9_2;
    void *temp_r25;
    Unk_A7137CF0 *temp_r27;
    void *temp_r28;
    void *temp_r29;
    void *temp_r30;
    void *temp_r30_10;
    void *temp_r30_2;
    void *temp_r30_3;
    void *temp_r30_4;
    void *temp_r30_5;
    void *temp_r30_8;
    void *temp_r30_9;
    Unk_B0F19D72 *temp_r3;
    Unk_B0F19D72 *temp_r3_2;
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    CStruct *temp_r9_3;
    void *var_r17;
    void *var_r19;
    void *var_r31;
    void *var_r31_2;
    void *var_r31_3;
    CScript *var_r31_4;
    CStruct *var_r9_3;

    sp108C = 0;
    temp_r3 = *(void **)0x802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x5F8);
    temp_r27 = arg0->unk0x20;
    sp1080 = *(void **)0x80305EAC;
    fn_80137CB4(&sp10);
    sp1C = 2;
    sp20 = 8;
    sp1084 = *(s32 *)0x80303448;
    temp_r9 = temp_r27->unk0x154;
    var_r19 = temp_r9;
    temp_cr0_eq = (s32) temp_r9->unk0x4 == -1;
    if (temp_cr0_eq != 0) {
        var_r19 = NULL;
    }
    0;
    if (temp_cr0_eq == 0) {
loop_4:
        sp1070 = (s32)lbl_802A83F8;
        sp1068.unk0x4 = 0;
        temp_r9_2 = ((Unk_C8FEE62D *)var_r19)->unk0xC;
        var_r17 = temp_r9_2;
        if ((s32) temp_r9_2->unk0x4 == -1) {
            var_r17 = NULL;
        }
        temp_r25 = ((Unk_C8FEE62D *)var_r19)->unk0x4;
        if ((u32) *((u32 *)&((Unk_78674569 *)temp_r25)->unk0x18) > (u32) *(s32 *)(*(s32 *)((char *)((char *)temp_r27) + 0x8) + 0x1804)) {
            sp1070 = (s32)lbl_802A83F8;
        } else {
            var_r18 = 0;
            if ((fn_8013FB8C(((Unk_78674569 *)temp_r25)->unk0x14) == 1) || (fn_80137AD4(sp1084) == 1)) {
                var_r18 = 1;
            }
            temp_r29 = temp_r25 + 1;
            temp_r3_2 = *(s32 *)0x802FFE98;
            fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x5F8);
            temp_r28 = fn_8021B830(temp_r27, 0, ((Unk_78674569 *)temp_r25)->unk0x14, ((Unk_78674569 *)temp_r25)->unk0x20);
            fn_8000F320(*(s32 *)0x802FFE98);
            strcpy(temp_r28 + 0x3C, temp_r29);
            fn_80229810(temp_r28, ((Unk_78674569 *)temp_r25)->unk0x1C);
            ((Unk_77666767 *)temp_r28)->unk0x1E0 = (s32) ((Unk_78674569 *)temp_r25)->unk0x24;
            ((Unk_77666767 *)temp_r28)->unk0x2C = (s32) ((Unk_78674569 *)temp_r25)->unk0x2C;
            ((Unk_77666767 *)temp_r28)->unk0x30 = (s32) ((Unk_78674569 *)temp_r25)->unk0x30;
            ((Unk_77666767 *)temp_r28)->unk0x24 = 0;
            ((Unk_77666767 *)temp_r28)->unk0x20 = 0;
            ((Unk_77666767 *)temp_r28)->unk0x4C = (s32) ((Unk_78674569 *)temp_r25)->unk0x40;
            fn_8021C7CC(temp_r27, temp_r28);
            temp_r3_3 = fn_8022986C(temp_r28);
            sp107C = fn_800145AC();
            if (temp_r3_3 == NULL) {
                sp50 = *(s32 *)((char *)temp_r25 + (s32)0x11);
                sp51 = *(s32 *)((char *)temp_r28 + (s32)0x37);
                sp38 = ((Unk_77666767 *)temp_r28)->unk0x2C;
                sp3C = ((Unk_77666767 *)temp_r28)->unk0x30;
                sp44 = temp_r3_3;
                sp54 = ((Unk_77666767 *)temp_r28)->unk0x4C;
                sp4C = temp_r3_3;
                sp48 = temp_r3_3;
                strcpy(&sp58, temp_r29);
                var_r9 = 1;
                sp40 = 1;
                if (!(((Unk_77666767 *)temp_r28)->unk0x1D8 & 0x10)) {
                    var_r9 = 0;
                }
                if (var_r9 != 0) {
                    sp40 = 1 | 0x10;
                }
                if (fn_8022989C(temp_r28) != 0) {
                    sp40 |= 4;
                }
                sp10 = 0x79;
                sp18 = 0xFF;
                sp12 = (s16) temp_r3_3;
                sp14 = temp_r3_3;
                temp_r30 = temp_r27->unk0x8;
                fn_8013CC84(temp_r30, fn_8022A9B8(temp_r28), &sp10);
                sp14 = &sp38;
                sp12 = 0x30;
                sp10 = 0x22;
                sp30 = 2;
                temp_r30_2 = temp_r27->unk0x8;
                fn_8013CC84(temp_r30_2, fn_8022A9B8(temp_r28), &sp10);
                sp30 = 0;
            }
            0;
            0;
            if (fn_8022989C(temp_r28) == 0) {
                var_r31 = fn_8021D454(temp_r27, &sp1068, 1);
                if (var_r31 != NULL) {
                    do {
                        if (temp_r28 != var_r31) {
                            temp_r3_4 = fn_8022986C(var_r31);
                            if (temp_r3_4 == NULL) {
                                sp40 = temp_r3_4;
                                sp50 = *(s32 *)((char *)temp_r25 + (s32)0x11);
                                sp51 = *(s32 *)((char *)temp_r28 + (s32)0x37);
                                sp38 = ((Unk_77666767 *)temp_r28)->unk0x2C;
                                sp3C = ((Unk_77666767 *)temp_r28)->unk0x30;
                                sp44 = temp_r3_4;
                                sp54 = ((Unk_77666767 *)temp_r28)->unk0x4C;
                                sp4C = temp_r3_4;
                                sp48 = temp_r3_4;
                                strcpy(&sp58, temp_r28 + 0x3C);
                                temp_r3_5 = fn_801A4B88(((Unk_77666767 *)temp_r28)->unk0x50, &sp68, 0x1000, 0) + 0x30;
                                sp14 = &sp38;
                                sp12 = temp_r3_5;
                                sp10 = 0x22;
                                sp18 = 0x80;
                                sp1C = 2;
                                sp20 = 8;
                                sp30 = 2;
                                temp_r30_3 = temp_r27->unk0x8;
                                fn_8013CC84(temp_r30_3, fn_8022A9B8(var_r31), &sp10);
                                sp30 = (s8) temp_r3_4;
                            }
                        }
                        var_r31 = fn_8021D4E8(temp_r27, &sp1068, 1);
                    } while (var_r31 != NULL);
                }
            }
            
            if (((!(((Unk_77666767 *)temp_r28)->unk0x1D8 & 0x10)) == 0 ? 0 : 1) != 0) {
                var_r31_2 = fn_8021D454(temp_r27, &sp1068, 0);
                if (var_r31_2 != NULL) {
                    do {
                        if ((temp_r28 != var_r31_2) && ((s32) ((Unk_77666767 *)var_r31_2)->unk0x1E0 == (s32) ((Unk_77666767 *)temp_r28)->unk0x1E0)) {
                            sp50 = (u8) *(s32 *)(*(s32 *)((char *)((char *)var_r31_2) + 0x18) + 0x18);
                            sp40 = ((Unk_77666767 *)var_r31_2)->unk0x1D8 & 0x27880;
                            sp51 = *(s32 *)((char *)var_r31_2 + (s32)0x37);
                            sp38 = ((Unk_77666767 *)var_r31_2)->unk0x2C;
                            sp3C = ((Unk_77666767 *)var_r31_2)->unk0x30;
                            sp44 = NULL;
                            sp54 = ((Unk_77666767 *)var_r31_2)->unk0x4C;
                            sp4C = NULL;
                            sp48 = NULL;
                            strcpy(&sp58, var_r31_2 + 0x3C);
                            temp_r3_6 = fn_801A4B88(((Unk_77666767 *)var_r31_2)->unk0x50, &sp68, 0x1000, var_r18) + 0x30;
                            sp14 = &sp38;
                            sp12 = temp_r3_6;
                            sp10 = 0x22;
                            sp18 = 0x80;
                            sp1C = 2;
                            sp20 = 8;
                            sp30 = 2;
                            temp_r30_4 = temp_r27->unk0x8;
                            fn_8013CC84(temp_r30_4, fn_8022A9B8(temp_r28), &sp10);
                            sp30 = 0;
                        }
                        var_r31_2 = fn_8021D4E8(temp_r27, &sp1068, 0);
                    } while (var_r31_2 != NULL);
                }
            } else {
                var_r31_3 = fn_8021D454(temp_r27, &sp1068, 0);
                if (var_r31_3 != NULL) {
                    do {
                        if (temp_r28 != var_r31_3) {
                            temp_r3_7 = fn_8022986C(temp_r28);
                            if (temp_r3_7 == NULL) {
                                sp50 = (u8) *(s32 *)(*(s32 *)((char *)((char *)var_r31_3) + 0x18) + 0x18);
                                sp40 = ((Unk_77666767 *)var_r31_3)->unk0x1D8 & 0x27880;
                                sp51 = *(s32 *)((char *)var_r31_3 + (s32)0x37);
                                sp38 = ((Unk_77666767 *)var_r31_3)->unk0x2C;
                                sp3C = ((Unk_77666767 *)var_r31_3)->unk0x30;
                                sp54 = ((Unk_77666767 *)var_r31_3)->unk0x4C;
                                sp44 = fn_80228840(temp_r27, *(s32 *)(*(s32 *)((char *)((char *)var_r31_3) + 0x18) + 0x18));
                                sp4C = ((Unk_77666767 *)var_r31_3)->unk0x24;
                                sp48 = ((Unk_77666767 *)var_r31_3)->unk0x20;
                                strcpy(&sp58, var_r31_3 + 0x3C);
                                sp12 = fn_801A4B88(((Unk_77666767 *)var_r31_3)->unk0x50, &sp68, 0x1000, var_r18) + 0x30;
                                sp10 = 0x22;
                                sp14 = &sp38;
                                sp18 = 0x80;
                                sp1C = 2;
                                sp20 = 8;
                                sp30 = 2;
                                temp_r30_5 = temp_r27->unk0x8;
                                fn_8013CC84(temp_r30_5, fn_8022A9B8(temp_r28), &sp10);
                                sp30 = (s8) temp_r3_7;
                            }
                        }
                        var_r31_3 = fn_8021D4E8(temp_r27, &sp1068, 0);
                    } while (var_r31_3 != NULL);
                }
                temp_r29_2 = fn_8021D920(temp_r27);
                if ((fn_8022986C(temp_r28) == NULL) && (temp_r29_2 == QB_LOAD_SK5ED_GAMEPLAY)) {
                    fn_80233294(*(s32 *)0x80305FF8);
                    temp_r30_6 = fn_8022A9B8(temp_r28);
                    temp_r7 = fn_802332B8(*(s32 *)0x80305FF8, 0);
                    sp8 = 1;
                    fn_8013DC7C(temp_r27->unk0x8, temp_r30_6, 0x6C, 0x3A98, temp_r7, 0x802AFD94, 8, 0);
                    temp_r30_7 = fn_8022A9B8(temp_r28);
                    fn_801FC0E0();
                    fn_801FC0E0();
                    temp_r7_2 = fn_801FA284();
                    sp8 = 1;
                    fn_8013DC7C(temp_r27->unk0x8, temp_r30_7, 0x88, 0x1132, temp_r7_2, 0x802AFDA0, 8, 0);
                }
                sp1078 = temp_r29_2;
                sp14 = &sp1078;
                sp12 = 4;
                sp10 = 0x53;
                sp1C = 2;
                sp18 = 0x80;
                sp20 = 8;
                temp_r30_8 = temp_r27->unk0x8;
                fn_8013CC84(temp_r30_8, fn_8022A9B8(temp_r28), &sp10);
            }
            if (fn_8022989C(temp_r28) == 0) {
                if ((fn_8022986C(temp_r28) != NULL) && (fn_8009CF2C(temp_r27) != 0)) {
                    var_r30 = 0;
                } else {
                    var_r7 = 0;
                    var_r9_3 = sp1080->unk0x38;
                    if ((s32) var_r9_3->unk0x4 == -1) {
                        var_r9_3 = NULL;
                    }
                    if (var_r9_3 != NULL) {
                        do {
                            var_r9_3 = var_r9_3->unk0xC;
                            var_r7 += 1;
                            if ((s32) var_r9_3->unk0x4 == -1) {
                                var_r9_3 = NULL;
                            }
                        } while (var_r9_3 != NULL);
                    }
                    var_r30 = var_r7;
                }
                temp_r3_8 = fn_80173024(sp1080, ((Unk_78674569 *)temp_r25)->unk0x1C, fn_8013F74C(((Unk_77666767 *)temp_r28)->unk0x1C), (s8) *(s32 *)((char *)temp_r25 + (s32)0x11), var_r30);
                fn_80229644(temp_r28, temp_r3_8);
                if (fn_8022986C(temp_r28) == NULL) {
                    fn_80145058(temp_r3_8);
                }
                var_r31_4 = fn_8021D454(temp_r27, &sp1068, 1);
                if (var_r31_4 != NULL) {
                    do {
                        if (temp_r28 != var_r31_4) {
                            sp14 = &sp107C;
                            sp12 = 4;
                            sp10 = 0x25;
                            sp18 = 0x80;
                            sp1C = 2;
                            sp20 = 8;
                            temp_r30_9 = temp_r27->unk0x8;
                            fn_8013CC84(temp_r30_9, fn_8022A9B8(var_r31_4), &sp10);
                            if ((fn_8022986C(var_r31_4) == NULL) && (fn_8022989C(var_r31_4) == 0)) {
                                fn_80145008(var_r31_4->unk0x18);
                                fn_8022A860(var_r31_4, sp107C);
                            }
                        }
                        var_r31_4 = fn_8021D4E8(temp_r27, &sp1068, 1);
                    } while (var_r31_4 != NULL);
                }
            }
            sp14 = &sp107C;
            sp12 = 4;
            sp10 = 0x25;
            sp1C = 2;
            sp18 = 0x80;
            sp20 = 8;
            temp_r30_10 = temp_r27->unk0x8;
            fn_8013CC84(temp_r30_10, fn_8022A9B8(temp_r28), &sp10);
            fn_8022A860(temp_r28, sp107C);
            if (0) {
                fn_8022AABC(temp_r25, 3);
            }
            if (0) {
                temp_r9_3 = ((Unk_C8FEE62D *)var_r19)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r19 + temp_r9_3->unk0x8, 3);
            }
            var_r19 = var_r17;
            sp1070 = (s32)lbl_802A83F8;
            if (var_r19 != NULL) {
                goto loop_4;
            }
        }
    }
    fn_8000F320(*(s32 *)0x802FFE98);
    0;
}
