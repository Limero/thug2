// WIP DRAFT (non-matching) — hand-rebuilt from disasm (batch session)
// family=hand range=0x80194DD4-0x80194FAC size=472B
// FLAG: -fno-strength-reduce
// BEST: 31.5% masked with -fno-strength-reduce + 4 volatile-double dummies
// (frame 0x70 exact: stmw r21,0x34 + stfd f30/f31 @60/68; test_wip_drafts
// IGNORES FLAG lines — verify via tools/flagdiff.py or fdiff -c).
// PARKED 31.5%: control flow fully matches (chained fn_801403CC(fn_801745B4(
// lbl_80305EAC)), f32-returning fn_8012570C, 5-arg fn_8018223C/fn_80182150
// with the guard-load passing through in r4, shared crossjumped [cmpwi/ble/li]
// tail, counted latch). Remaining diffs are allocator-level: (a) GCC combines
// (arg0+OFF)+idx into a single idx+arg0 temp + displacement load where want
// recomputes addi r9,arg0,OFF + lwzx per site (-fno-strength-reduce only half-
// fixes it); (b) five-web register-home rotation arg0/t25/h/flag/idx
// (want r29/r25/r27/r26/r28 vs got r25/r27/r28/r30/r26); (c) sp8/sp18 slots —
// want sp8@8/sp18@18 with the dummy-doubles in the 1C..33 hole, ngccc's
// 8-aligned sorter puts dummies low. Resists decl order/pins/wedges/flags.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EAC;
extern s32 lbl_80300434;

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801745B4(s32);
s32 fn_801403CC(void *);
f32 fn_8012570C(s32, s32);
void GetElement_2(void *, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_8018223C(Unk_FFAD6788 *, s32, s32, s32, s32);
s32 fn_80182150(Unk_FFAD6788 *, s32, s32, s32, s32);
void CScreenElement_SetAlpha(Unk_6A70655D *, f32, s32);

void fn_80194DD4(Unk_C7387A53 *arg0) {
    volatile double _dummy;
    volatile double _dummy1;
    volatile double _d0;
    volatile double _d1;
    s32 sp18;
    s32 sp8;
    f32 temp_f30;
    f32 temp_f31;
    s32 t25;
    s32 t22;
    char *walk;
    s32 idx;
    s32 cnt;
    s32 e;
    s32 h;
    s32 r26;
    s32 v;
    s32 var_r23;

    var_r23 = 0;
    if (GetInteger(arg0->unk0x20, QB_TRICK_FLAG, &sp18, 0) != 0) {
        var_r23 = 1;
    }
    walk = (char *)arg0 + 0x84;
    idx = 0;
    cnt = 0x1E;
    t25 = fn_801403CC(fn_801745B4(lbl_80305EAC));
    t22 = lbl_80300434;
    temp_f30 = fn_8012570C(QB_GOAL_TETRIS_FADED_TRICK_ALPHA, 1);
    temp_f31 = fn_8012570C(QB_GOAL_TETRIS_UNFADED_TRICK_ALPHA, 1);
    do {
        e = *(s32 *)((char *)(idx + (s32)walk));
        if (e == 0) {
            GetElement_2(&sp8, t22, *(s32 *)((char *)arg0 + 0x80 + idx), 1);
            h = sp8;
            if (h != 0) {
                CObject_RemoveRefLink((void *)h, &sp8);
                sp8 = e;
            }
            r26 = 0;
            if ((var_r23 == 0) || (sp18 != 0)) {
                if (*(s32 *)((char *)arg0 + 0x7C + idx) != 0) {
                    v = fn_8018223C(t25,
                                    *(s32 *)((char *)arg0 + 0x7C + idx),
                                    *(s32 *)((char *)arg0 + 0x90 + idx),
                                    *(s32 *)((char *)arg0 + 0x88 + idx),
                                    *(s32 *)((char *)arg0 + 0x94 + idx));
                    if (v > 0) {
                        r26 = 1;
                    }
                } else {
                    if (*(s32 *)((char *)arg0 + 0x74 + idx) != 0) {
                        if (fn_80182150(t25,
                                        *(s32 *)((char *)arg0 + 0x74 + idx),
                                        *(s32 *)((char *)arg0 + 0x90 + idx),
                                        *(s32 *)((char *)arg0 + 0x88 + idx),
                                        1) > 0) {
                            r26 = 1;
                        } else {
                            if (*(s32 *)((char *)arg0 + 0x78 + idx) != 0) {
                                v = fn_80182150(t25,
                                                *(s32 *)((char *)arg0 + 0x78 + idx),
                                                *(s32 *)((char *)arg0 + 0x90 + idx),
                                                *(s32 *)((char *)arg0 + 0x88 + idx),
                                                1);
                                if (v > 0) {
                                    r26 = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (r26 != 0) {
                CScreenElement_SetAlpha(h, temp_f30, 1);
            } else {
                CScreenElement_SetAlpha(h, temp_f31, 1);
            }
        }
        idx += 0x24;
    } while (--cnt != 0);
}
