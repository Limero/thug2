// WIP DRAFT — hand-rebuilt from disasm (groupB PS zone, 2026-08-25)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 35.6164% -> 45.8904% `volatile` keyword(s) removed from the body
// PARKED 37-39% (-mps-float): PS allocator/scheduler residue after full
// structural rebuild. ALL instruction idioms now decode+emit correctly:
// unlink-blocks A/B byte-match except GPR homes; ps_add pair updates,
// dot rows (fmuls+2*fmadds left-assoc), spill pairs, merge00->madd->
// sum0 len2 idiom (lbl_802AF450 const pair), ps_mr copy, fcmpu/ble
// negated-compare, rsqrte, muls0 normalize, dead sp2C store all EMIT.
// Remaining diff clusters (all documented wall classes):
// (a) arg0 home r29 vs got r28 (+obj r28 vs r29) - pure pair swap;
//     pin-a-copy cascades (mr r27,r3; mr r29,r27), pointer pins dropped,
//     -fno-sched-spec/-fno-schedule-insns no-op or destroy layout (doc-15/32).
// (b) frame slots: want dots fr[] at r1+0x18..0x24 w/ spill pairs sp8/C,
//     sp10/14 + inv@0x28 + const2@0x2C; got puts fr[] at 0x10 or 0x20
//     depending on __ps_t local count (GCC 8-aligned sort order fights
//     declaration order; tried named-spill vars, volatile arrays, plain).
// (c) FPR colors shift by cascade from (a)/(b): x54 f9-vs-f8 etc.
// (d) want loads chk(0x54) BEFORE spill stores; got sinks it - minor.
// Callee facts verified: Tmr_GetTime = 0-arg s32 old-style (r3 overwritten
// in its prologue); CObject_RemoveRefLink(void*,void*) 2-arg; Mem_Free(node);
// fn_801090B8(r28->0x1c, arg0+0x28) result or.-tested, chained into block B
// stores (stw r30 = NULL result).
// family=hand range=0x8020F938-0x8020FB80 size=584B
// INERT: not registered in splits.txt/configure.py - never compiled.
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

extern s32 Tmr_GetTime();
extern void CObject_RemoveRefLink(CStruct *, CStruct *);
extern void Mem_Free(void *);
extern void *fn_801090B8(void *, void *);
extern s32 lbl_80303150;
extern f32 lbl_802AF584;
extern f32 lbl_802AF588;
extern char lbl_802AF450[];

typedef union { __ps_t ps; f32 f[2]; } PSU;

void fn_8020F938(Unk_830733AE *arg0) {
    
    
    char *pos;
    Unk_A54BEA09 *node;
    s32 *walker;
    void *res;
    s32 flag;
    s32 ok;
    f32 sp2C;
    __ps_t keep01;
    __ps_t keep23;
    f32 fr[4];
    f32 K;
    __ps_t d12;
    __ps_t d34;
    __ps_t sq;
    __ps_t cur;
    __ps_t inv;

    Unk_C8FEE62D *obj;
    obj = arg0->unk0x1850;
    obj = arg0->unk0x1850;
    pos = (char *)arg0 + 0x28;
    node = *((s32 * *)&obj->unk0x1C);
    if (node == NULL) {
        flag = 0;
    } else {
        res = *(void **)node;
        if (res != NULL) {
            flag = 1;
        } else {
            obj->unk0x70 = res;
            if (*(s32 *)node != 0) {
                CObject_RemoveRefLink(*(void **)node, node);
                *(s32 *)node = res;
            }
            Mem_Free(node);
            obj->unk0x1C = res;
            obj->unk0x74 = lbl_80303150 + Tmr_GetTime();
            flag = 0;
        }
    }
    if (flag != 0) {
        res = fn_801090B8(*((s32 * *)&obj->unk0x1C), pos);
        if (res != NULL) {
            ok = 1;
        } else {
            walker = *((s32 * *)&obj->unk0x1C);
            if (walker != NULL) {
                obj->unk0x70 = *(s32 *)walker;
                if (*(s32 *)walker != 0) {
                    CObject_RemoveRefLink(*(void **)walker, walker);
                    *(s32 *)walker = res;
                }
                Mem_Free(walker);
                obj->unk0x1C = res;
                obj->unk0x74 = lbl_80303150 + Tmr_GetTime();
            }
            ok = 0;
        }
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return;
    }
    obj = arg0->unk0x1850;
    node = *((s32 * *)&obj->unk0x1C);
    d12 = arg0->unk0x28;
    d34 = arg0->unk0x30;
    d12 = __builtin_ps_add(d12, node->unk0x60);
    arg0->unk0x28 = d12;
    d34 = __builtin_ps_add(d34, node->unk0x68);
    arg0->unk0x30 = d34;
    node = *((s32 * *)&obj->unk0x1C);
    if (node->unk0xB0 == 0) {
        return;
    }
    {
        f32 x54 = arg0->unk0x54;
        f32 x50 = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x50);
        f32 x58 = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x58);
        f32 x5C = arg0->unk0x5C;
        f32 n70 = node->unk0x70;
        f32 n74 = node->unk0x74;
        f32 n78 = node->unk0x78;
        f32 n80 = node->unk0x80;
        f32 n84 = node->unk0x84;
        f32 n88 = node->unk0x88;
        f32 n90 = node->unk0x90;
        f32 n94 = node->unk0x94;
        f32 n98 = node->unk0x98;

        K = lbl_802AF584;
        fr[0] = x50 * n70 + x54 * n80 + x58 * n90;
        fr[1] = x50 * n74 + x54 * n84 + x58 * n94;
        fr[3] = x5C;
        fr[2] = x50 * n78 + x54 * n88 + x58 * n98;
    }
    d12 = *(__ps_t *)&fr[0];
    ((Unk_5F85C510 *)arg0)->unk0x50 = d12;
    {
        f32 chk = arg0->unk0x54;
        keep01 = *(__ps_t *)&fr[0];
        d34 = *(__ps_t *)&fr[2];
        if (chk == K) {
            return;
        }
        keep23 = d34;
        ((Unk_5F85C510 *)arg0)->unk0x58 = keep23;
    }
    arg0->unk0x54 = K;
    cur = ((Unk_5F85C510 *)arg0)->unk0x50;
    sq = __builtin_ps_merge00(__builtin_ps_mul(d34, d34), *(__ps_t *)&lbl_802AF450);
    sq = __builtin_ps_madd(cur, cur, sq);
    sq = __builtin_ps_sum0(sq, sq, sq);
    inv = sq;
    {
        PSU u;
        u.ps = inv;
        if (!(u.f[0] > K)) {
            return;
        }
    }
    inv = __builtin_ps_rsqrte(inv);
    ((Unk_5F85C510 *)arg0)->unk0x50 = __builtin_ps_muls0(cur, inv);
    sp2C = lbl_802AF588;
    ((Unk_5F85C510 *)arg0)->unk0x58 = __builtin_ps_mul(d34, inv);
}
