// Hand rebuild from disasm (m2c draft did not compile)
// WIP DRAFT (non-matching)
// family=m2c range=0x8020B280-0x8020C4E0 size=4704B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 35% (masked, -mps-float -fno-schedule-insns2): full hand rebuild from
// disasm; structure/size complete (34 hash cases, compare-tree switch on u32
// arg1, all call arities audited vs callee prologues). Remaining walls:
// (1) doc-15 arg-setup/store interleave coin-flips at ~20 sites (mr/lwz/stw
//     rotations inside fn_80128xxx arg setup and tail store runs);
// (2) big-function allocator-order wall (§6y class): want keeps
//     node-walk cursors in scratch r3/r9/r10/r11 (webs broken at the bl,
//     rematerializing lis r9,0xd inside loop bodies) while every C shape
//     homes them in callee-saved r26-r31; decl-order permutations, -fno-gcse,
//     pins all no-ops or regressions;
// (3) FPR naming parity in the int<->float dances (want f31/f13 roles after
//     calls vs got f12/f13 swaps, §75 asymmetric-fence territory);
// (4) EDA2772E tail: want keeps inline [li r3,0][beq][li r3,1][b] pair but
//     GCC tail-merges our return-1 into the shared block_231 pad ("+r"/
//     memory barriers all perturb more than the 2 words gained);
// (5) cvt slot at 0x40/44 + frame 0x70 REQUIRE -mps-float (16-align doubles);
//     without it everything sits 8 low.
// Verified truths this round: case value 0xCB3A8FD2 (m2c right), shared-tail
// hash 0xB394C01C, F32E8D5C else has hidden GetInteger(arg2,0x83CB0082,&sp30)
// + fn_8017EBFC/Script_GenerateCRC trick-name compare + angle-add + fn_8017F5B0
// block (m2c dropped it); its mgr read at BE54 is an uninitialized-local use
// (`mr r4,r11` before any r11 def on that path).
// FLAG: -fno-rerun-cse-after-loop
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 43.3%.
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure(void *, void *);
extern void fn_8020ABF8(Unk_90685748 * arg0);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);
extern s32 fn_80207538(void *arg0, s32 arg1);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void *fn_80127358(CStruct * arg0, Unk_C7387A53 * arg1);
extern void fn_80209334(Unk_90685748 * arg0, s32 arg1);
extern void fn_801259C8_unused(void);
extern s32 fn_801259C8(s32 arg0, s32 arg1);
extern void fn_80206E48(void *arg0);
extern void fn_80206E7C(Unk_76553646 * arg0);
extern void fn_80209268(Unk_CF8B1206 * arg0);
extern void fn_802099A0(Unk_90685748 * arg0);
extern void fn_80209A2C(Unk_605C573D * arg0, CStruct * arg1);
extern void fn_802070E8(Unk_90685748 * arg0, s32 arg1, s32 arg2);
extern void fn_8020A35C(Unk_13928190 * arg0);
extern void fn_8020A350(Unk_CF8B1206 * arg0);
extern void fn_8020A0F4(void *arg0, void *arg1, void *arg2);
extern s32 fn_800145AC(void);
extern f32 fn_8020AF18(void *arg0);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern void fn_8012772C(CStruct * arg0, s32 arg1, f32 arg2);
extern void fn_80127F20(s32 arg0, s32 arg1, f32 arg2, f32 arg3);
extern s32 CStruct_dtor(CStruct * arg0);
extern s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern void strcpy(void *arg0, void *arg1);
extern void fn_8017EF1C(Unk_950BD505 * arg0, u8 * arg1, s32 arg2, s32 arg3);
extern void fn_8017F5B0(Unk_FFAD6788 * arg0, s32 arg1);
extern void fn_8017F614(Unk_950BD505 * arg0, s32 arg1);
extern f32 fn_8014030C(s32 arg0, s32 arg1, Unk_FFAD6788 * arg2);
extern void fn_8009F054(s32 arg0, s32 arg1, s32 arg2, f32 arg3);
extern void GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 Game_GetGoalManager(void);
extern void fn_80185240(s32 arg0);
extern void CStruct_new(s32 arg0);
extern s32 CStruct_ctor(void);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern void CStruct_delete(CStruct * arg0, s32 arg1);
extern s32 fn_8017EBFC(s32 arg0);
extern s32 Script_GenerateCRC(void *arg0);
extern void fn_801C27F4(void);
extern void fn_801C27C8(void);
extern void fn_8017FC8C(Unk_F515CE8D * arg0);
extern void fn_80201F54(Unk_ABBD6FA6 * arg0);
extern void fn_80201E78(Unk_59E38960 * arg0);
extern void fn_801F0484(s32 arg0);
extern void fn_801F04CC(CScript * arg0);
extern void fn_801ED044(Unk_FF487DD2 * arg0);
extern void fn_8020C54C(Unk_BF3B6DA6 * arg0, s32 arg1);
extern void fn_8020C58C(void *arg0, s32 arg1);
extern void fn_801A9A4C(Unk_03123917 * arg0);
extern void fn_80180204(Unk_F515CE8D * arg0);
extern f32 lbl_802AF3B0;
extern f64 lbl_802AF3A8;
extern f64 lbl_802AF3B8;
extern f32 lbl_802AF3C0;
extern f32 lbl_802AF3C4;
extern f32 lbl_802AF3C8;
extern f32 lbl_802AF3CC;
s32 fn_8020B280(Unk_90685748 *arg0, u32 arg1, CStruct *arg2, CScript *arg3) {
    void *sp8;
    s32 spC;
    s32 sp10;
    void *sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    u32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    CStruct *list;
    CStruct *node;
    char *outBase;
    s32 *arrBase;
    s32 cnt;
    s32 i;
    s32 count;
    s32 mask;
    s32 maskInv;
    s32 head;
    s32 ctr;
    s32 offset;
    char *walker;
    s32 rec;
    s32 ts;
    s32 var_r3;
    s32 t85;
    s32 ret;
    s32 flags;
    s32 flag;
    Unk_7258DEBD *mgr;
    Unk_8049EAE5 *skater;
    Unk_C8FEE62D *game;
    s32 t;
    s32 zero;
    s32 one;
    f32 angle;
    f32 lim;
    switch (arg1) {
    case QB_DUMPEVENTBUFFER:
        fn_8020ABF8(arg0);
        goto block_231;
    case QB_HELD:
        sp8 = NULL;
        t85 = GetArray(arg2, QB_BUTTONS, &sp8, 0);
        if (t85 != 0) {
            list = sp8;
            i = 0;
            count = list->unk0x4;
            if (i < count) {
                do {
                    if (fn_80207538(arg0, GetChecksum(sp8, i)) != 0) {
                        goto block_231;
                    }
                    i++;
                } while (i < count);
            }
            return 0;
        } else {
            spC = t85;
            GetChecksum_2(arg2, 0, &spC, 0);
            if (spC == 0) {
                return 0;
            }
            if (fn_80207538(arg0, spC) == 0) {
                return 0;
            }
            return 1;
        }
    case QB_RELEASED:
        sp10 = 0;
        GetChecksum_2(arg2, 0, &sp10, 0);
        var_r3 = 0;
        if (sp10 != 0) {
            var_r3 = fn_80207538(arg0, sp10) == 0;
        }
        return var_r3;
    case QB_CLEARTRICKSFROM:
        node = NULL;
        while ((node = fn_80127358(arg2, node)) != NULL) {
            if ((node->unk0x4 == 0) &&
                (((*(s32 *)node) & 0x7F0000) == 0xD0000)) {
                fn_80209334(arg0, node->unk0x8);
            }
        }
        goto block_231;
    case QB_SETQUEUETRICKS:
        arg0->unk0x1248 = 0;
        node = NULL;
        outBase = (char *)arg0 + 0x1274;
        while ((node = fn_80127358(arg2, node)) != NULL) {
            if ((node->unk0x4 == 0) &&
                (((*(s32 *)node) & 0x7F0000) == 0xD0000)) {
                cnt = arg0->unk0x1248;
                arrBase = (s32 *)((char *)arg0 + 0x124C);
                *(s32 *)((char *)arrBase + (cnt << 2)) =
                    node->unk0x8;
                arg0->unk0x1248 = cnt + 1;
            }
        }
        if ((arg0->unk0x1248 == 1) &&
            (fn_801259C8(arg0->unk0x124C, 0) == 0)) {
            arg0->unk0x124C = QB_DEFAULTAIRTRICKS;
        }
        arg0->unk0x1274 = 0;
        GetChecksum_2(arg2, QB_SPECIAL, outBase, 0);
        goto block_231;
    case QB_USEGRINDEVENTS:
        arg0->unk0x1278 = 8;
        goto block_231;
    case QB_ADDTRICKSTOQUEUE:
        fn_802099A0(arg0);
        goto block_231;
    case QB_CLEARTRICKQUEUE:
        fn_80209268(arg0);
        goto block_231;
    case QB_DONEXTMANUALTRICK:
        fn_80209A2C(arg0, arg2);
        goto block_231;
    case QB_SETMANUALTRICKS:
        arg0->unk0x127C = 0;
        node = NULL;
        outBase = (char *)arg0 + 0x12A8;
        while ((node = fn_80127358(arg2, node)) != NULL) {
            if ((node->unk0x4 == 0) &&
                (((*(s32 *)node) & 0x7F0000) == 0xD0000)) {
                cnt = arg0->unk0x127C;
                arrBase = (s32 *)((char *)arg0 + 0x1280);
                *(s32 *)((char *)arrBase + (cnt << 2)) =
                    node->unk0x8;
                arg0->unk0x127C = cnt + 1;
            }
        }
        arg0->unk0x12A8 = (s32)node;
        GetChecksum_2(arg2, QB_SPECIAL, outBase, 0);
        goto block_231;
    case QB_CLEARMANUALTRICK:
        fn_80206E7C(arg0);
        goto block_231;
    case QB_SETEXTRAGRINDTRICKS:
        arg0->unk0x12C4 = 0;
        node = NULL;
        outBase = (char *)arg0 + 0x12F0;
        while ((node = fn_80127358(arg2, node)) != NULL) {
            if ((node->unk0x4 == 0) &&
                (((*(s32 *)node) & 0x7F0000) == 0xD0000)) {
                cnt = arg0->unk0x12C4;
                arrBase = (s32 *)((char *)arg0 + 0x12C8);
                *(s32 *)((char *)arrBase + (cnt << 2)) =
                    node->unk0x8;
                arg0->unk0x12C4 = cnt + 1;
            }
        }
        arg0->unk0x12F0 = (s32)node;
        GetChecksum_2(arg2, QB_SPECIAL, outBase, 0);
        goto block_231;
    case QB_CLEAREXTRAGRINDTRICK:
        fn_8020A35C(arg0);
        goto block_231;
    case QB_CLEAREVENTBUFFER:
        i = 0;
        sp14 = NULL;
        if (GetArray(arg2, QB_BUTTONS, &sp14, 0) != 0) {
            sp18 = 0;
            GetInteger(arg2, QB_OLDERTHAN, &sp18, 0);
            list = sp14;
            count = list->unk0x4;
            if (i < count) {
                do {
                    fn_802070E8(arg0, GetChecksum(sp14, i++), sp18);
                } while (i < count);
            }
            goto block_231;
        }
        fn_80206E48(arg0);
        goto block_231;
    case QB_REMOVEXEVENTS:
        ctr = 0;
        if (ctr < (s32)arg0->unk0x99C) {
            walker = (char *)arg0 + 0x50;
            do {
                if (*(s32 *)(walker - 0xC) == QB_X) {
                    *(s32 *)walker = 1;
                }
                walker += 0x18;
                ctr++;
            } while (ctr < (s32)arg0->unk0x99C);
        }
        goto block_231;
    case QB_RESTOREEVENTS:
        sp1C = 0xC8;
        mask = 0;
        GetInteger(arg2, QB_DURATION, &sp1C, 0);
        sp20 = 0;
        GetChecksum_2(arg2, QB_USEDBY, &sp20, 0);
        switch (sp20) {
        case QB_REGULAR:
            mask = 1;
            break;
        case QB_EXTRA:
            mask = 2;
            break;
        case QB_MANUAL:
            mask = 4;
            break;
        case QB_EXTRAGRIND:
            mask = 8;
            break;
        }
        head = arg0->unk0x99E;
        ctr = 0;
        maskInv = ~mask;
        offset = head * 0x18;
        walker = (char *)arg0 + offset + 0x3C;
        while (ctr < (s32)arg0->unk0x99C) {
            ts = *(s32 *)walker;
            if ((u32)(fn_800145AC() - ts) < (u32)sp1C) {
                rec = *(s32 *)((char *)arg0 + 0x50 + offset);
                if (rec & mask) {
                    *(s32 *)((char *)arg0 + 0x50 + offset) = rec & maskInv;
                }
                walker -= 0x18;
                offset -= 0x18;
                head--;
                if (head < 0) {
                    walker += 0x960;
                    offset += 0x960;
                    head += 0x64;
                }
                ctr++;
            } else {
                goto block_231;
            }
        }
        goto block_231;
    case QB_SETEXTRATRICKS:
        fn_8020A0F4(arg0, arg2, arg3);
        goto block_231;
    case QB_KILLEXTRATRICKS:
        fn_8020A350(arg0);
        goto block_231;
    case QB_SETSLOTTRICK:
        sp24 = 0;
        GetChecksum_2(arg2, QB_SLOT, &sp24, 0);
        sp28 = 0;
        GetChecksum_2(arg2, QB_TRICK, &sp28, 0);
        fn_80127F20(arg0->unk0xA6C, sp24, lbl_802AF3B0,
                    (f32)(f64)sp28);
        goto block_231;
    case QB_CHANGEPROTRICKS:
        node = NULL;
        if ((node = fn_80127358(arg2, node)) != NULL) {
            if ((node->unk0x4 == 0) &&
                (((*(s32 *)node) & 0x7F0000) == 0xD0000)) {
                t = GetStructure(node->unk0x8, 0);
                if (t != 0) {
                    CStruct_dtor(arg0->unk0xA6C);
                    fn_80126FF4(arg0->unk0xA6C, t);
                }
            }
        }
        goto block_231;
    case QB_BASHON:
        arg0->unk0x1378 = 1;
        fn_80206E48(arg0);
        goto block_231;
    case QB_BASHOFF:
        arg0->unk0x1378 = 0;
        goto block_231;
    case QB_GETSPAZZFACTOR:
        AddInteger(arg3->unk0x18, QB_SPAZZFACTOR,
                    (s32)fn_8020AF18(arg0));
        goto block_231;
    case QB_CLEARQUICKGETUP:
        arg0->unk0x1C0C = 0;
        goto block_231;
    case QB_NOQUICKGETUP:
        arg0->unk0x1C0C = 1;
        goto block_231;
    case QB_SETTRICKNAME:
        sp2C = 0;
        GetString(arg2, 0, &sp2C, 0);
        if (sp2C != 0) {
            strcpy((char *)arg0 + 0x137C, (char *)sp2C);
        } else {
            arg0->unk0x137C = (u8)sp2C;
        }
        goto block_231;
    case QB_SETTRICKSCORE:
        GetInteger(arg2, 0, (char *)arg0 + 0x13B0, 0);
        goto block_231;
    case QB_GETSPIN:
        angle = arg0->unk0x13F0;
        angle = __builtin_fabsf(angle);
        angle = angle + fn_8014030C(QB_SPIN_COUNT_SLOP, 1, arg0->unk0xC);
        fn_8012772C(arg3->unk0x18, QB_SPIN,
                    (f32)(f64)((s32)angle / 180) * lbl_802AF3C0);
        goto block_231;
    case QB_GETACTUALSPIN:
        angle = arg0->unk0x13F0;
        fn_8012772C(arg3->unk0x18, QB_SPIN,
                    (f32)(f64)(s32)__builtin_fabsf(angle));
        goto block_231;
    case QB_RESETSPIN:
        arg0->unk0x13F0 = lbl_802AF3C4;
        goto block_231;
    case QB_DISPLAY: {
        char *nameptr = (char *)arg0 + 0x137C;
        if (nameptr != NULL) {
            sp30 = 0;
            skater = arg0->unk0x20;
            if (ContainsFlag(arg2, QB_DEFERRED) != 0) {
                strcpy((char *)arg0 + 0x13B4, nameptr);
                arg0->unk0x13E8 = arg0->unk0x13B0;
                mgr = arg0->unk0x2C;
                if (((Unk_EE1FD121 *)mgr->unk0xC)->unk0x120 != 0) {
                    flag = ((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x34;
                } else {
                    flag = ((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x34 ^ 1;
                }
                if (flag != 0) {
                    arg0->unk0x13EC |= 4;
                }
            } else {
                if (GetInteger(arg2, QB_ADDSPIN, &sp30, 0) != 0) {
                    if (fn_8017EBFC(skater) == Script_GenerateCRC(nameptr)) {
                        angle = (f32)((f32)(f64)(s32)sp30 + arg0->unk0x13F0);
                        arg0->unk0x13F0 = angle;
                        if (((Unk_FFAD6788 *)arg0->unk0xC)->unk0xC8 != 0) {
                            fn_8017F5B0(skater, (s32)angle);
                        }
                    }
                }
                flags = 0;
                if (ContainsFlag(arg2, QB_BLOCKSPIN) != 0) {
                    flags = 2;
                }
                if (ContainsFlag(arg2, QB_NODEGRADE) != 0) {
                    flags |= 0x40;
                }
                mgr = arg0->unk0x2C;
                if (((Unk_EE1FD121 *)mgr->unk0xC)->unk0x120 != 0) {
                    flag = ((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x34;
                } else {
                    flag = ((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x34 ^ 1;
                }
                if (flag != 0) {
                    flags |= 4;
                }
                if (arg0->unk0xA68 != 0) {
                    if (ContainsFlag(arg2, QB_NOSPECIAL) == 0) {
                        flags |= 0x20;
                    } else {
                        arg0->unk0xA68 = 0;
                    }
                }
                if (ContainsFlag(arg2, QB_CAT) != 0) {
                    flags |= 0x80;
                }
                if (ContainsFlag(arg2, QB_NATAS) != 0) {
                    flags |= 0x100;
                }
                if (ContainsFlag(arg2, QB_NOMULT) != 0) {
                    flags |= 0x200;
                }
                if (ContainsFlag(arg2, QB_NOSWITCH) != 0) {
                    flags |= 0x400;
                }
                if (((Unk_FFAD6788 *)arg0->unk0xC)->unk0xC8 != 0) {
                    mgr = arg0->unk0x2C;
                    if (((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x1C == 4) {
                        t = arg0->unk0x13B0;
                        if (t != 0) {
                            arg0->unk0x13B0 =
                                (s32)((f32)(f64)t * skater->unk0x1558);
                        }
                    }
                    fn_8017EF1C(skater, nameptr, arg0->unk0x13B0, flags);
                    if (arg0->unk0x137C != 0) {
                        fn_8009F054(arg0->unk0xC, QB_SKATERTRICKDISPLAYED, 0,
                                    lbl_802AF3C4);
                        mgr = arg0->unk0x2C;
                        if ((((Unk_C8FEE62D *)mgr->unk0x15BC)->unk0x40 != 0) ||
                            (mgr->unk0x3E8 != 0)) {
                            angle = __builtin_fabsf(arg0->unk0x13F0);
                            lim = lbl_802AF3C8 -
                                  fn_8014030C(QB_SPIN_COUNT_SLOP, 1, arg0->unk0xC);
                            lim = lim + lbl_802AF3CC;
                            if (!(angle < lim)) {
                                fn_8017F614(skater,
                                            (s32)arg0->unk0x13F0);
                            }
                        } else {
                            fn_8017F614(skater,
                                        (s32)arg0->unk0x13F0);
                        }
                    }
                }
                if (ContainsFlag(arg2, QB_BLOCKSPIN) != 0) {
                    arg0->unk0x13F0 = lbl_802AF3C4;
                }
                arg0->unk0x13B4 = 0;
            }
        }
        if (arg0->unk0x137C != 0) {
            arg0->unk0xA68 = 0;
        }
        goto block_231;
    }
    case QB_CLEARPANEL_LANDED:
        game = arg0->unk0xC;
        skater = arg0->unk0x20;
        if (game->unk0xC8 != 0) {
            if (arg0->unk0x13B4 != 0) {
                if (((Unk_35F48240 *)arg0->unk0x2C)->unk0x3E8 != 0) {
                    angle = __builtin_fabsf(arg0->unk0x13F0);
                    lim = lbl_802AF3C8 -
                          fn_8014030C(QB_SPIN_COUNT_SLOP, 1, game);
                    lim = lim + lbl_802AF3CC;
                    if (!(angle < lim)) {
                        fn_8017EF1C(skater, (char *)arg0 + 0x13B4,
                                    arg0->unk0x13E8,
                                    arg0->unk0x13EC);
                        fn_8017F614(skater, (s32)arg0->unk0x13F0);
                    }
                } else {
                    angle = __builtin_fabsf(arg0->unk0x13F0);
                    lim = lbl_802AF3C0 -
                          fn_8014030C(QB_SPIN_COUNT_SLOP, 1, game);
                    lim = lim + lbl_802AF3CC;
                    if (!(angle < lim)) {
                        fn_8017EF1C(skater, (char *)arg0 + 0x13B4,
                                    arg0->unk0x13E8,
                                    arg0->unk0x13EC);
                        fn_8017F614(skater, (s32)arg0->unk0x13F0);
                    }
                }
                arg0->unk0x13B4 = 0;
            }
            fn_80185240(Game_GetGoalManager());
            if ((s32)((f32)(f64)skater->unk0x18 *
                      skater->unk0x6C) != 0) {
                CStruct_new(8);
                t = CStruct_ctor();
                AddChecksum(t, QB_SKATERID, game->unk0x18);
                fn_8009F054(arg0->unk0xC, QB_SKATEREXITCOMBO, t,
                            lbl_802AF3C4);
                if (t != 0) {
                    CStruct_delete(t, 3);
                }
            }
            GetChecksum_3(arg0->unk0xC, QB_SKATERGAP);
            fn_801C27F4();
            fn_8017FC8C(skater);
            arg0->unk0x13F0 = lbl_802AF3C4;
            ((Unk_C7387A53 *)arg0->unk0x34)->unk0x144 = 0;
            fn_80201F54(arg0->unk0x38);
        }
        fn_8009F054(arg0->unk0xC, QB_SKATERLANDED, 0, lbl_802AF3C4);
        if (arg0->unk0x13F4 != 0) {
            arg0->unk0x13F8 = 1;
        }
        zero = 0;
        arg0->unk0x13FC = zero;
        fn_801F0484(arg0->unk0x28);
        fn_801F04CC(arg0->unk0x28);
        ((Unk_35F48240 *)arg0->unk0x2C)->unk0x37C = zero;
        goto block_231;
    case QB_CLEARPANEL_BAILED:
        game = arg0->unk0xC;
        if (game->unk0xC8 != 0) {
            skater = arg0->unk0x20;
            if ((s32)((f32)(f64)skater->unk0x18 *
                      skater->unk0x6C) != 0) {
                CStruct_new(8);
                t = CStruct_ctor();
                AddChecksum(t, QB_SKATERID, game->unk0x18);
                fn_8009F054(arg0->unk0xC, QB_SKATEREXITCOMBO, t,
                            lbl_802AF3C4);
                if (t != 0) {
                    CStruct_delete(t, 3);
                }
            }
            fn_80180204(skater);
        }
        fn_8009F054(arg0->unk0xC, QB_SKATERBAILED, 0, lbl_802AF3C4);
        zero = 0;
        one = 1;
        arg0->unk0x13F8 = one;
        fn_8020C54C(arg0, 0);
        arg0->unk0x13F4 = one;
        arg0->unk0x13FC = zero;
        fn_801F04CC(arg0->unk0x28);
        fn_801ED044(arg0->unk0x2C);
        arg0->unk0x13F0 = lbl_802AF3C4;
        ((Unk_35F48240 *)arg0->unk0x2C)->unk0x37C = zero;
        fn_801A9A4C((char *)arg0 + 0x1404);
        GetChecksum_3(arg0->unk0xC, QB_SKATERGAP);
        fn_801C27C8();
        fn_80201E78(arg0->unk0x38);
        goto block_231;
    case QB_TRICKOFFOBJECT:
        sp34 = 0;
        GetChecksum_2(arg2, 0, &sp34, 1);
        fn_8020C58C(arg0, sp34);
        goto block_231;
    default:
        return 2;
    }
block_231:
    return 1;
}
