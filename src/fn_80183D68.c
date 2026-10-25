// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80183D68-0x80183F08 (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

// Per-call-site signatures, taken from the promoted callees in src/ and from the
// register setup at each `bl` here:
//   ContainsFlag really is (CStruct*, s32) and is called with the hash in r4 -
//   its arg0 is the previous call's return, i.e. it is CHAINED, not 1-arg.
//   fn_8018E1E8 is void in src/ but its r3 is consumed here, so s32 at this site.
extern s32 lbl_80305F9C;
s32 GoalManager_GetGoal(void *, s32, s32);
s32 fn_8009CF2C(void *);
s32 ContainsFlag(void *, s32);
void *fn_80137CB4(void *);
void fn_8013DE78(void *, void *);
s32 fn_8018BFAC(void *);
s32 fn_8018E1E8(void *);
u8 fn_8021F6CC(void *);
s32 fn_8021B55C(void *, s32);

// vtable reached through mgr+0x14: s16 method offset + fn ptr at +4.
// Layout copied from the byte-proven promoted sibling src/fn_80183F08.c.
typedef struct {
    char _00[0x80];
    s16 unk80;
    char _82[2];
    s32 unk84;
    char _88[0x20];
    s16 unkA8;
    char _AA[2];
    s32 unkAC;
} GoalVT;

typedef struct {
    char _00[0x14];
    GoalVT *vt;
    char _18[0x14];
    s32 *unk2C;
    void *unk30;
} Mgr;

typedef struct {
    char _00[0x38];
    s32 unk38;
    char _3C[0x10];
    s32 unk4C;
} Obj;

// One stack object (0x30 bytes) shared by fn_80137CB4 / fn_8013DE78; unk04 is a
// self-pointer to unk28 (want: addi r0,r1,0x30 ; stw r0,0xc(r1)).
typedef struct {
    u8 unk00;
    char _01[1];
    u16 unk02;
    char *unk04;
    char _08[4];
    s32 unk0C;
    u8 unk10;
    char _11[0x17];
    u8 unk28;
    char _29[3];
    s32 unk2C;
} Search;

s32 fn_80183D68(Obj *arg0, s32 arg1) {
    Search fr;
    Mgr *mgr;
    GoalVT *vt;
    GoalVT *vt2;
    s32 (*fp)(void *);
    s32 g;
    s32 cur;
    s32 node;
    s32 t;
    s32 chk;
    s32 chk2;
    s32 chk3;

    g = lbl_80305F9C;
    mgr = (Mgr *)GoalManager_GetGoal(arg0, arg1, 1);
    if (mgr != NULL) {
        cur = arg1;
        /* load the POINTER only: want's pre-loop block is one `lwz 0x30(r31)`,
           and the dereference happens in the loop-test block. */
        node = (s32)mgr->unk30;
        goto ltest;
    lbody:
        cur = node;
        node = *(s32 *)((char *)GoalManager_GetGoal(arg0, cur, 1) + 0x30);
    ltest:
        if (node != 0) {
            t = *(s32 *)node;
            node = t;
            /* keep want's `mr r9,r0`: the zero-code barrier blocks cc1's
               coalesce of `node` with `t`, which would delete the copy. */
            __asm__("" : "+r"(node));
            if (t != 0) {
                goto lbody;
            }
        }
        if (cur == arg0->unk38) {
            chk = *(s32 *)mgr->unk2C;
            if (chk == 0) {
                arg0->unk38 = chk;
            }
        }
        vt = mgr->vt;
        fp = (s32 (*)(void *))vt->unkAC;
        if (fp((char *)mgr + vt->unkA8) != 0) {
            goto tail;
        }
        chk2 = *(s32 *)mgr->unk2C;
        /* want keeps the pointer in r9 and the loaded word in r0 at the two
           compare-only sites; the address must stay live past the load, which
           cc1's coalesce otherwise removes. */
        __asm__("" : : "r"(mgr->unk2C));
        __asm__("" : "+r"(chk2));
        if (chk2 != 0) {
            goto tail;
        }
        if (fn_8009CF2C(g) != 0) {
            fn_80137CB4(&fr);
            cur = fn_8021B55C(g, 0);
            fr.unk28 = fn_8021F6CC(g);
            fr.unk2C = fn_8018E1E8(mgr);
            fr.unk04 = (char *)&fr.unk28;
            fr.unk00 = 0x6E;
            fr.unk0C = 2;
            fr.unk02 = (u16)8;
            fr.unk10 = (u8)8;
            fn_8013DE78(cur, &fr);
        } else {
            chk3 = *(s32 *)mgr->unk2C;
            __asm__("" : : "r"(mgr->unk2C));
            __asm__("" : "+r"(chk3));
            if (chk3 == 0) {
                if (ContainsFlag(fn_8018BFAC(mgr), QB_EDITED_GOAL) == 0) {
                    arg0->unk4C = arg0->unk4C + 1;
                }
            }
        }
tail:
        vt2 = mgr->vt;
        fp = (s32 (*)(void *))vt2->unk84;
        fp((char *)mgr + vt2->unk80);
    }
    return mgr != 0;
}
