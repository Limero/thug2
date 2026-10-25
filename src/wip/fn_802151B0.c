// PARKED DIFF 8.6% (-mps-float): compiles clean now (was FAIL — m2c sinf/cosf
// arity garbage replaced with fn_80271170/80271070 + __builtin_ps_* math).
// Byte-match needs a full rebuild: (a) want's compare tree roots cmpw/beq with
// case bodies OUT-OF-LINE at function end -> goto-dispatch form (§6ag-1);
// (b) frame 0x50 wants ~0x30 bytes of live stack slots (pairA/pairB/cos/sin/
// k1/k2 per case x2 sets) — needs frame-template struct (§6q-86); (c) want
// homes &sp8 in saved r30 (addi r30,r1,8) feeding psq round-trips; (d) two
// near-twin trig+PS case bodies share merged tail @15370 (ps_mul/madds0/
// merge01/msub sequence decoded OK via ps_diff.dec). Next: rebuild
// with slot-struct + goto dispatch before touching PS scheduling.
// family=m2c range=0x802151B0-0x8021546C size=700B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 6.9% ([1]rev->6.9%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF724;
extern f32 lbl_802AF728;
extern f32 lbl_802AF72C;
extern f32 lbl_802AF730;
extern f32 cosf(f32);
extern f32 sinf(f32);
void fn_802151B0(Unk_66B68E7E *arg0) {
    f32 blkA[2];
    f32 blkB[2];
    f32 cos_s;
    f32 sin_s;
    f32 cos_s2;
    f32 sin_s2;
    f32 sp2C;
    f32 sp34;
    f32 k1;
    f32 k2;
    s32 temp_r9;
    s32 var_r0;
    s32 *sub;

    temp_r9 = arg0->unk0x80;
    if (temp_r9 == QB_ANIMWAIT) {
        sub = arg0->unk0x182C;
        sub[33] = 1;
        k1 = lbl_802AF72C;
        if (arg0->unk0x1A30 != 0) {
            ((Unk_61ECF642 *)sub)->unk0x88 = arg0->unk0x1A08;
            ((Unk_61ECF642 *)sub)->unk0x90 = arg0->unk0x1A10;
        } else {
            ((Unk_61ECF642 *)sub)->unk0x88 = ((Unk_5F85C510 *)arg0)->unk0x50;
            ((Unk_61ECF642 *)sub)->unk0x90 = ((Unk_5F85C510 *)arg0)->unk0x58;
        }
        ((Unk_61ECF642 *)sub)->unk0x98 = k1;
        return;
    }
    if ((u32)temp_r9 > QB_ANIMWAIT) {
        if (temp_r9 == (s32)QB_LADDER || temp_r9 == (s32)QB_LADDERMOVEUP || temp_r9 == (s32)QB_LADDERMOVEDOWN) {
            goto set_one_copy;
        }
        sub[33] = 0;
        sub = arg0->unk0x182C;
        return;
    }
    if (temp_r9 == (s32)QB_HANGMOVELEFT) {
        k1 = lbl_802AF724;
        sin_s = sinf(k1);
        cos_s = cosf(k1);
        sp2C = lbl_802AF728;
        blkA[0] = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x50);
        blkA[1] = arg0->unk0x54;
        blkB[0] = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x58);
        blkB[1] = arg0->unk0x5C;
        {
            __ps_t pa = *(__ps_t *)&blkA[0];
            __ps_t pk = *(__ps_t *)&cos_s;
            __ps_t ps = *(__ps_t *)&sin_s;
            __ps_t pb = *(__ps_t *)&blkB[0];
            __ps_t pc = *(__ps_t *)&cos_s;
            __ps_t t, u, m, v, w;
            t = __builtin_ps_mul(pa, pk);
            u = __builtin_ps_madds0(ps, t, pb);
            m = __builtin_ps_merge01(u, pa);
            *(__ps_t *)&blkA[0] = m;
            v = __builtin_ps_mul(pa, ps);
            w = __builtin_ps_msub(pc, pb, v);
            *(__ps_t *)&blkB[0] = w;
        }
        sub = arg0->unk0x182C;
        sub[33] = 1;
        k2 = lbl_802AF72C;
        ((Unk_61ECF642 *)sub)->unk0x88 = *(__ps_t *)&blkA[0];
        ((Unk_61ECF642 *)sub)->unk0x90 = *(__ps_t *)&blkB[0];
        ((Unk_61ECF642 *)sub)->unk0x98 = k2;
        return;
    }
    if (temp_r9 == (s32)QB_HANGMOVERIGHT) {
        k2 = lbl_802AF730;
        sin_s2 = sinf(k2);
        cos_s2 = cosf(k2);
        sp34 = lbl_802AF728;
        blkA[0] = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x50);
        blkA[1] = arg0->unk0x54;
        blkB[0] = *((f32 *)&((Unk_5F85C510 *)arg0)->unk0x58);
        blkB[1] = arg0->unk0x5C;
        {
            __ps_t pa = *(__ps_t *)&blkA[0];
            __ps_t pk = *(__ps_t *)&cos_s2;
            __ps_t ps = *(__ps_t *)&sin_s2;
            __ps_t pb = *(__ps_t *)&blkB[0];
            __ps_t pc = *(__ps_t *)&cos_s2;
            __ps_t t, u, m, v, w;
            t = __builtin_ps_mul(pa, pk);
            u = __builtin_ps_madds0(ps, t, pb);
            m = __builtin_ps_merge01(u, pa);
            *(__ps_t *)&blkA[0] = m;
            v = __builtin_ps_mul(pa, ps);
            w = __builtin_ps_msub(pc, pb, v);
            *(__ps_t *)&blkB[0] = w;
        }
        sub = arg0->unk0x182C;
        sub[33] = 1;
        k1 = lbl_802AF72C;
        ((Unk_61ECF642 *)sub)->unk0x88 = *(__ps_t *)&blkA[0];
        ((Unk_61ECF642 *)sub)->unk0x90 = *(__ps_t *)&blkB[0];
        ((Unk_61ECF642 *)sub)->unk0x98 = k1;
        return;
    }
    if (temp_r9 == (s32)QB_HANG) {
        goto set_one_copy;
    }
    sub = arg0->unk0x182C;
    sub[33] = 0;
    return;
set_one_copy:
    sub = arg0->unk0x182C;
    sub[33] = 1;
    k1 = lbl_802AF72C;
    ((Unk_61ECF642 *)sub)->unk0x88 = ((Unk_5F85C510 *)arg0)->unk0x50;
    ((Unk_61ECF642 *)sub)->unk0x90 = ((Unk_5F85C510 *)arg0)->unk0x58;
    ((Unk_61ECF642 *)sub)->unk0x98 = k1;
}
