// WIP DRAFT (non-matching) — hand rewrite
// family=m2c range=0x801A8E5C-0x801A91D8 size=892B
// PARKED: 37.7% size-exact. Remaining diffs are doc-15-class allocator/scheduler
// artifacts: (1) prologue register homes shifted (arg1->r18 vs want r20,
// arg3->r21 vs r23; &cmd home r14 emitted as fresh addi per site); (2) count
// web split (mr r29,r5 + mr r26,r29) - ngccc fails to coalesce the arg2 entry
// copy with the fn_801A8A6C redefinition, stealing a saved reg and cascading;
// (3) scheduler interleave of the f10/f11/f14/f1C store cluster + c_off/c_type/
// c_argC/c_flag stores around both memcpys. Tried: statement-order permutations
// (invariant), address-staging locals (pCmd/pState/pBufA/pF10/pBufB/pF820/
// pTrio), volatile f1C/f828 readback (fixed size), comma-chained A9B8(D358),
// file-scope register pins (break call-save semantics), full 9-arg fn_8013DC7C
// proto (crclr layout right, regalloc worse), flags -fno-schedule-insns/
// insns2/sched-spec/sched-interblock/gcse/strength-reduce/branch-count-reg.
// Volatile readback idiom (n1 = *(volatile u32*)&fr.f1C) is REQUIRED for the
// lwz+slwi reload pair want shows after fn_8021F6CC.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 42.2% ([9]rev->40.8% [7]rev->41.7% [0]rev->42.2%).
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305F1C[];
extern char lbl_80305F9C[];
extern char lbl_802A83F8[];
extern char lbl_802AB964[];

typedef struct {
    /* r1+0x10 */ u8 f10;
    u8 f11;
    char pad02[2];
    s32 f14;
    s32 f18;
    s32 f1C;
    /* r1+0x20 */ char bufA[0x800];
    /* r1+0x820 */ u8 f820;
    char pad811[3];
    s32 f824;
    s32 f828;
    /* r1+0x82C */ char bufB[0x804];
    /* r1+0x1030 */ u8 c_type;
    char padC1;
    u16 c_off;
    s32 c_ptr;
    char padC2[4];
    s32 c_argC;
    u8 c_flag;
    char pad1031[0x17];
    /* r1+0x1058 */ s32 d454a;
    s32 d454b;
    /* r1+0x1060 */ s32 gslot;
    char pad1064[4];
    /* r1+0x1068 */ u8 t_val;
    char padT[3];
    s32 t_arg0;
    s32 t_idx;
    char pad1074[4];
    /* r1+0x1078 */ u8 r_tag;
    char padR1;
    u16 r_len;
    s32 *r_ptr;
    char padR2[0x20];
    /* r1+0x10A0 */ u8 flags[8];
    /* r1+0x10A8 */ s32 gslotsaved;
    /* r1+0x10AC */ s32 df8;
} frame_t;

void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021B554(Unk_9994C3F5 *);
s32 fn_801A8DF8(s32);
s32 fn_801A8A6C(s32, s32, s32 *, u8 *, s32, s32);
u8 fn_8021F6CC(Unk_2EC243AC *);
void *fn_8021D358(void *, s32);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void *fn_8021D454(void *, CStruct *, s32);
void *fn_8021D4E8(void *, CStruct *, s32);
s32 fn_8022989C(CScript *);
void fn_80177F38(Unk_C7387A53 *, s32);
s32 fn_8013F74C(s32);
void fn_801A9270(s32, s32, s32);
void fn_8013DC7C();

void fn_801A8E5C(s32 arg0, s32 arg1, u32 arg2, s32 *arg3, s32 arg4) {
    frame_t fr;
    void *mgr;
    s32 t27;
    u32 count;
    u32 ctr;
    s8 *zp;
    s32 zero9;
    void *it;
    s32 i;
    u32 j;
    s32 v;
    u32 n1;
    u32 n2;
    void *pCmd;
    void *pState;
    char *pBufA;
    void *pF10;
    char *pBufB;
    void *pF820;
    void *pTrio;

    pCmd = &fr.c_type;
    mgr = *(void **)&lbl_80305F9C;
    fr.gslotsaved = *(s32 *)&lbl_80305EAC;
    count = arg2;
    fn_80137CB4(pCmd);
    fr.gslot = (s32)lbl_802A83F8;
    pState = &fr.d454a;
    fr.d454b = 0;
    if (arg4 != 0) {
        t27 = fn_8021B554(mgr);
        fr.df8 = fn_801A8DF8(arg0);
        zp = (s8 *)&fr.flags[7];
        for (ctr = 8U; ctr != 0U; ctr--) {
            *zp = 0;
            zp -= 1;
        }
        count = fn_801A8A6C(*(s32 *)&lbl_80305F1C, arg2, arg3, &fr.flags[0],
                            arg0, arg1);
        if (count != 0) {
            pBufA = &fr.bufA[0];
            pF10 = &fr.f10;
            pBufB = &fr.bufB[0];
            pF820 = &fr.f820;
            pTrio = &fr.t_val;
            for (i = 0; i <= 7; i++) {
                if (fr.flags[i] == 0) {
                    continue;
                }
                fn_80137CB4(pCmd);
                fr.t_arg0 = arg0;
                fr.t_idx = i;
                fr.t_val = fn_8021F6CC(mgr);
                fn_8013CC84(t27,
                            fn_8022A9B8((v = fn_8021D358(mgr, (u16)arg0),
                                         fr.r_ptr = &fr.t_val,
                                         fr.r_len = 0xC,
                                         fr.r_tag = 0x4B, v)),
                            pCmd);
                fr.t_arg0 = arg0;
                fr.t_idx = i;
                fr.t_val = fn_8021F6CC(mgr);
                v = fn_8021D358(mgr, (u16)i);
                if (v != 0) {
                    fn_8013CC84(t27, fn_8022A9B8(v), pCmd);
                }
            }
            fr.f18 = arg1;
            fr.f10 = 1;
            fr.f14 = arg0;
            *(volatile u32 *)&fr.f1C = count;
            fr.f11 = fn_8021F6CC(mgr);
            n1 = *(volatile u32 *)&fr.f1C;
            memcpy(&fr.bufA[0], arg3, n1 * 4);
            fr.c_off = (u16)(n1 * 4 + 0x10);
            fr.c_flag = 8;
            fr.c_type = 0x3B;
            fr.c_argC = 2;
            fr.c_ptr = (s32)&fr.f10;
            zero9 = 0;
            it = fn_8021D454(mgr, pState, 0);
            while ((s32)it != 0) {
                fn_8013DC7C(t27, fn_8022A9B8(it), fr.c_type, fr.c_off,
                            fr.c_ptr, (s32)lbl_802AB964, 8, 1, zero9);
                it = fn_8021D4E8(mgr, pState, 0);
            }
            fr.f824 = arg0;
            *(volatile u32 *)&fr.f828 = count;
            fr.f820 = fn_8021F6CC(mgr);
            n2 = *(volatile u32 *)&fr.f828;
            memcpy(&fr.bufB[0], arg3, n2 * 4);
            fr.c_ptr = (s32)&fr.f820;
            fr.c_off = (u16)(n2 * 4 + 0xC);
            fr.c_type = 0x5B;
            it = fn_8021D454(mgr, pState, 1);
            while ((s32)it != 0) {
                if (fn_8022989C(it) != 0) {
                    fn_8013DC7C(t27, fn_8022A9B8(it), fr.c_type, fr.c_off,
                                fr.c_ptr, (s32)lbl_802AB964, 8, 1, zero9);
                }
                it = fn_8021D4E8(mgr, pState, 1);
            }
            fn_80177F38(fr.gslotsaved, 0);
            if (fn_8013F74C(fr.df8) == 0) {
                goto tail;
            }
            goto endstore;
        }
        goto endstore;
    }
tail:
    for (j = 0U; j < count; j++) {
        fn_801A9270(*(s32 *)&lbl_80305F1C, arg3[j], arg0);
    }
endstore:
    fr.gslot = (s32)lbl_802A83F8;
}
