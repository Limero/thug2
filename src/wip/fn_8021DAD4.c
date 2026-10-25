// WIP DRAFT (non-matching) — hand-rebuilt from disasm (m2c draft was statics-DCE corrupted)
// family=m2c range=0x8021DAD4-0x8021E024 size=1360B
//
// PARKED at NEAR 97.6% (332/340 words), compiles clean. 2026-08-25.
// REVIEWED 2026-10-18 (random triage): single coupled mask/addr pair-swap
// stands; {iter=r23, mask=r25, &sp98=r26} jointly unreachable per the lever
// list (wedge moves iter, pins cascade, flags inert). Body untouched.
// Structure is fully decoded and semantically correct; remaining 8 words are
// ONE coupled allocator/scheduler pair-swap in the enumerator-loop preheader:
// the original computes the message address first, then derives the masked
// byte with a 24-bit clear-and-keep of one register, then takes the address
// of the sp98 slot, then loads the four small immediates (2, 0x2d, 2, 8) —
// with the mask living in r25 and the slot address in r26. The rebuild emits
// the same operations but rotates the mask derivation last and swaps the two
// homes (mask in r26, slot address in r25). The two downstream mask uses move
// with the swap: the mp34 word store at frame offset 0x114 and the OR into r0
// carrying the sp98 value at offset 0x120.
// Everything else matches byte-exact: prologue (mfcr/stmw r19/CR save),
// two-web iterator birth (addi r11 -> stores -> mr r23 home), strcpy window,
// cr3/cr4 long-range compare caching incl. GCSE preheader hoist of
// (arg2==3)/(arg2==2), the 7-way hash tree (root eq-3 via cr4 reuse;
// case 1 present as a DUPLICATE of default's body — that is what pivots
// balance_case_nodes at value 3), fn_8021FAB4 as a genuine 9-ARG call with
// the 9th arg 0x7D0 on caller stack (stw r0,8(r1)), chained/passthrough
// args at every call site, all three enumerator loops, both msg structs,
// and the epilogue label re-store.
//
// Exhausted levers for the residual pair-swap (each verified individually):
// - volatile asm wedge `__asm__ volatile("clrlwi %0,%1,0x18"...)` fixes the
//   ENTIRE preheader cluster (position+colors) BUT pushes the iterator home
//   from r23 to r22 and swaps the mw3C const to r23 (-6 net words). The three
//   constraints {iter=r23, mask=r25, &sp98=r26} are individually reachable
//   but not jointly under any shape tried.
// - non-volatile asm wedge: collapses whole allocation (14%).
// - register pin r25 on maskB: cascades every param home (+1 shift, 89%).
// - pin-a-copy itH->r23 + wedge: §73-151 frame corruption (0xe0 frame, 3.5%).
// - two-web manual split of the iterator (§6s-1): sinks the birth web.
// - u16 tmp16 named temp to force pseudo order (LHS-gimplify-first theory):
//   no effect; forward-prop still merges.
// - flags: -fno-sched-spec / -fno-sched-interblock / spec-pair (no-op here),
//   -fno-schedule-insns (frame balloons 0xe0), -fno-schedule-insns2 (fixes
//   nothing, breaks sp58 arm), -fno-rerun-cse-after-loop & -fno-gcse (frame
//   regressions). -fno-sched-spec alone = exact same 12/8 diffs.
// - mp34-before-sp98 store reorder: scrambles the store run (94.1%).
// KEY WIN worth reusing elsewhere: declaring fn_8026B2B4 as
// `s32`-returning (not void) fixed the entire prologue-window diff
// ([addi r3 hoisted above mr r27/stw]) — the live call result changes the
// ready-list fill of the first-call window. Also: hash switch needs
// `case 1:` written out with the SAME body as default (n=7 nodes) to root
// the compare tree at eq-3 like want.
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802A83F8[];
extern char lbl_802AFE24[];
extern s32 lbl_80305EC0;
extern s32 lbl_80305F1C;

s32 strcpy(char *, char *);
s32 fn_8022989C(CScript *);
s32 IsTrue(s32, void *);
void fn_801A8998(Unk_C7387A53 *, s32);
s32 fn_80219698(CStruct *);
void *fn_8021D454(void *, CStruct *, s32);
void *fn_8021D4E8(void *, CStruct *, s32);
s32 fn_8022986C(CScript *);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8013DEE0(Unk_440CB216 *, s32, s32, void *, s32, s32, s32);
void fn_8013E2EC(s32, Unk_C7387A53 *);
void fn_8013F6E4(Unk_FFAD6788 *);
void fn_8013ED00(Unk_C7387A53 *);
s32 fn_80229884(CScript *);
void fn_8021C7EC(Unk_031F7D04 *, Unk_C8FEE62D *);
void fn_8021CDA0(Unk_9994C3F5 *);
s32 fn_8021D7F0(void *);
s32 fn_80198F7C(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8021FAB4(Unk_9994C3F5 *, s32, s32, char *, char *, s32, s32, s32, s32);
s32 fn_8022A848(CScript *);
void fn_801AAC90(Unk_EE1FD121 *);
void fn_8022A510(void *, s32);
s32 fn_80229B94(CScript *);
s32 fn_80229BAC(CScript *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_801258E8(void *, s32);
void AddComponent(CStruct *, s32, s32, void *);
void CStruct_delete(CStruct *, s32);
void *NextItem(void *);
void fn_80229C38(CScript *);

struct fr_s {
    char strbuf[0x10];   /* frame 0x10 */
    s32 iter[3];         /* frame 0x20 (iterator state) */
    char p2C[4];         /* frame 0x2C */
    u8 mb30;             /* frame 0x30 (msg struct) */
    u16 mh32;            /* frame 0x32 */
    void *mp34;          /* frame 0x34 */
    char p38[4];         /* frame 0x38 */
    u32 mw3C;            /* frame 0x3C */
    u8 mb40;             /* frame 0x40 */
    char p41[0x17];      /* frame 0x41..0x57 */
    char sp58[0x40];     /* frame 0x58 (out-param buffer) */
    u16 sp98;            /* frame 0x98 */
};

void fn_8021DAD4(Unk_9994C3F5 *arg0, CScript *arg1, s32 arg2) {
    struct fr_s fr;
    CScript *walker;
    Unk_C7387A53 *entry;
    s32 mgr;
    s32 hash;
    s32 idx;
    s32 obj;
    s32 allFlag;
    s32 f;
    s32 flag200;
    s32 maskB;
    u16 tmp16;
    char *strSrc;
    s32 *it;

    it = fr.iter;
    fr.iter[2] = (s32)lbl_802A83F8;
    it[1] = 0;
    strcpy(fr.strbuf, (char *)arg1 + 0x3C);
    if (fn_8022989C(arg1) == 0 && IsTrue(lbl_80305EC0, QB_SHOULD_MODULATE_COLOR) != 0) {
        fn_801A8998(lbl_80305F1C, *(s32 *)(arg1->unk0x18 + 0x18));
    }
    if (fn_80219698(arg0) != 0) {
        if (fn_8022989C(arg1) == 0) {
            walker = fn_8021D454(arg0, fr.iter, 1);
            if (walker != NULL) {
                do {
                    if (fn_8022986C(walker) == 0) {
                        fn_80137CB4(&fr.mb30);
                        mgr = arg0->unk0x8;
                        maskB = arg2 & 0xFF;
                        tmp16 = (*(u8 *)(arg1->unk0x18 + 0x1B) << 8) | maskB;
                        fr.sp98 = tmp16;
                        fr.mp34 = &fr.sp98;
                        fr.mh32 = 2;
                        fr.mb30 = 0x2D;
                        fr.mw3C = 2;
                        fr.mb40 = 8;
                        fn_8013CC84(mgr, fn_8022A9B8(walker), &fr.mb30);
                    }
                    walker = fn_8021D4E8(arg0, fr.iter, 1);
                } while (walker != NULL);
            }
        }
        if ((u32)(arg2 - 3) <= 1U) {
            void *t9 = *((void * *)&arg1->unk0x1C);
            fn_8013DEE0(arg0->unk0x8, 0x51, 0, 0,
                        ((Unk_89391A04 *)t9)->unk0x4C, *((u16 *)&((Unk_89391A04 *)t9)->unk0x50), 0);
            if (arg2 == 3) {
                fn_8013E2EC(arg0->unk0x8, arg1->unk0x1C);
            }
        } else if (arg2 == 6) {
            void *t9 = *((void * *)&arg1->unk0x1C);
            fn_8013DEE0(arg0->unk0x8, 0x56, 0, 0,
                        ((Unk_89391A04 *)t9)->unk0x4C, *((u16 *)&((Unk_89391A04 *)t9)->unk0x50), 0);
        }
        if (arg2 != 2 && arg1->unk0x1C != NULL) {
            fn_8013F6E4(arg1->unk0x1C);
            fn_8013ED00(arg1->unk0x1C);
        }
        switch (arg2) {
        case 0:
            hash = QB_NET_MESSAGE_PLAYER_QUIT;
            break;
        case 2:
            hash = QB_NET_MESSAGE_PLAYER_NOW_OBSERVING;
            break;
        case 3:
            hash = QB_NET_MESSAGE_PLAYER_BANNED;
            break;
        case 4:
            hash = QB_NET_MESSAGE_PLAYER_KICKED;
            break;
        case 6:
            hash = QB_NET_MESSAGE_PLAYER_LEFT_OUT;
            break;
        case 5:
            hash = QB_NET_MESSAGE_PLAYER_DROPPED;
            break;
        case 1:
            hash = QB_NET_MESSAGE_PLAYER_TIMED_OUT;
            break;
        default:
            hash = QB_NET_MESSAGE_PLAYER_TIMED_OUT;
            break;
        }
        if (fn_8022986C(arg1) == 0) {
            fn_8021FAB4(arg0, 1, hash, fr.strbuf, 0, 0, 0, 0, 0x7D0);
        }
        if (arg2 == 2) {
            if (fn_8022A848(arg1) != 0) {
                if (arg0->unk0x78 != 0) {
                    fn_801AAC90(arg0->unk0x78);
                }
                fn_8022A510(arg1, 0);
            }
            if (fn_80229B94(arg1) != 0) {
                idx = fn_80229BAC(arg1);
                sprintf(&fr.sp58, lbl_802AFE24, idx + 1);
                obj = CStruct_ctor(CStruct_new(8));
                AddInteger(obj, QB_TEAM, idx);
                AddComponent(obj, QB_STRING0, 3, fn_801258E8(&fr.sp58, 0));
                Script_RunScript(QB_FLAG_RETURNED, obj, 0, 0, 0);
                if (obj != 0) {
                    CStruct_delete(obj, 3);
                }
                entry = NextItem(arg0);
                if (entry != NULL && fn_8022989C(entry) == 0 &&
                    entry->unk0x34 == idx) {
                    Script_RunScript(QB_HIDE_CTF_ARROW, 0, 0, 0, 0);
                }
                fn_80229C38(arg1);
            }
        } else {
            flag200 = fn_80229884(arg1);
            fn_8021C7EC(arg0, arg1);
            if (flag200 != 0) {
                fn_8021CDA0(arg0);
                if (fn_8021D7F0(arg0) == 0 && fn_80198F7C(lbl_80305EC0) != QB_NETLOBBY) {
                    Script_RunScript(QB_NETWORK_END_GAME_SELECTED, 0, 0, 0, 0);
                }
            }
        }
        allFlag = 1;
        walker = fn_8021D454(arg0, fr.iter, 0);
        while (walker != NULL) {
            f = 1;
            if (!(walker->unk0x1D8 & 0x100)) {
                f = 0;
            }
            if (f == 0) {
                allFlag = 0;
                break;
            }
            walker = fn_8021D4E8(arg0, fr.iter, 0);
        }
        if (allFlag != 0) {
            fn_80137CB4(&fr.mb30);
            fr.mb30 = 0x5A;
            fr.mw3C = 2;
            fr.mb40 = 8;
            walker = fn_8021D454(arg0, fr.iter, 1);
            if (walker != NULL) {
                do {
                    mgr = arg0->unk0x8;
                    fn_8013CC84(mgr, fn_8022A9B8(walker), &fr.mb30);
                    walker = fn_8021D4E8(arg0, fr.iter, 1);
                } while (walker != NULL);
            }
        }
    } else {
        fn_8021C7EC(arg0, arg1);
    }
    fr.iter[2] = (s32)lbl_802A83F8;
}
