// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161AC0-0x80161CAC (492B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern f32 lbl_802A82F4;
extern f32 lbl_802A82F8;
extern __ps_t lbl_802A8048;
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void *fn_801746A4(Unk_C7387A53 *, s32);
void *fn_8021D358(s32, s32);
s32 fn_80229B94(CScript *);
void AddInteger(CStruct *, s32, s32);

typedef union { __ps_t p; f32 w[2]; } S;

typedef struct {
    s32 team;
    f32 rad2;
    S d10;
} FR;

bool ScriptGetCollidingPlayerAndTeam(CStruct *arg0, Unk_EFC8CFAD *arg1) {
    FR fr;
    s32 var_r23;
    s32 var_r26;
    u32 var_r29;
    s32 cnt;
    s32 lst;
    Unk_C7387A53 *gv;
    CStruct *head;
    Unk_E892005F *node;
    Unk_C7387A53 *ent;
    CStruct *walk;
    s32 nxt;
    f32 best;
    f32 dist;
    f32 radv;
    __ps_t n12;
    __ps_t o13;
    __ps_t p0;
    __ps_t q10;
    __ps_t k11;
    __ps_t dxy;
    __ps_t sq;
    __ps_t dzp;
    __ps_t mg;
    __ps_t acc;
    __ps_t tot;
    Unk_DF2324A8 *mgr28;
    s32 ctx25;

    ctx25 = arg1->unk0x18;
    mgr28 = arg1->unk0xBC;
    best = lbl_802A82F4;
    GetInteger(arg0, QB_EXCLUDE_TEAM, &fr.team, 1);
    var_r23 = -1;
    var_r26 = -1;
    GetFloat(arg0, QB_RADIUS, &fr.rad2, 1);
    var_r29 = 0U;
    fr.rad2 = fr.rad2 * lbl_802A82F8;
    fr.rad2 = fr.rad2 * fr.rad2;
    for (;;) {
        cnt = 0U;
        gv = *(s32 *)&lbl_80305EAC;
        __asm__("" : "+r"(gv));
        head = (void *)gv->unk0x38;
        nxt = head->unk0x4;
        __asm__ volatile("" : "+r"(head));
        walk = head;
        goto check;
        while (walk != NULL) {
            walk = (void *)walk->unk0xC;
            cnt += 1;
            nxt = walk->unk0x4;
        check:
            if (nxt == -1) {
                walk = NULL;
            }
        }
        if (var_r29 >= (u32)cnt) {
            break;
        }
        node = fn_801746A4(lbl_80305EAC, var_r29);
        if (node != NULL) {
            ent = fn_8021D358(lbl_80305F9C, (u16)((Unk_7F52D842 *)node)->unk0x1A);
            if (ent != NULL) {
                if (ent->unk0x34 != fr.team) {
                    goto else_arm;
                }
                if (fn_80229B94(ent) == 0) {
                    goto next_iter;
                }
                __asm__ volatile("" ::: "memory");
                if (ent->unk0x34 == fr.team) {
                    goto have_target;
                }
            else_arm:
                if (fn_80229B94(ent) != 0) {
                    goto next_iter;
                }
            have_target:
                    n12 = node->unk0x58;
                    o13 = mgr28->unk0x58;
                    p0 = mgr28->unk0x60;
                    q10 = node->unk0x60;
                    k11 = lbl_802A8048;
                    dxy = __builtin_ps_sub(o13, n12);
                    sq = __builtin_ps_mul(dxy, dxy);
                    dzp = __builtin_ps_sub(p0, q10);
                    mg = __builtin_ps_merge00(dzp, k11);
                    acc = __builtin_ps_madds0(mg, mg, sq);
                    radv = fr.rad2;
                    tot = __builtin_ps_sum0(acc, acc, acc);
                    fr.d10.p = tot;
                    {
                        __ps_t tot2 = tot;
                        f32 lr = fr.d10.w[0];
                        __asm__("" : "+f"(tot2));
                        __asm__ __volatile__("fmr %0, %1" : "=f"(dist) : "f"(lr));
                    }
                    if ((dist < radv) && (dist < best)) {
                        var_r26 = node->unk0x18;
                        best = dist;
                    }
            }
        }
    next_iter:
        var_r29 += 1U;
    }
    if (var_r26 > -1) {
        var_r23 = *(s32 *)((s32)(fn_8021D358(lbl_80305F9C, (u16)var_r26)) + 0x34);
    }
    AddInteger(ctx25, QB_TEAM, var_r23);
    AddInteger(ctx25, QB_PLAYER, var_r26);
    return true;
}
