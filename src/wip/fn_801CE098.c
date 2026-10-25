// WIP DRAFT (non-matching) — hand-rebuilt from disasm (PS normalize + 4-arm guard chain)
// family=m2c range=0x801CE098-0x801CE380 size=744B
// PARKED (hand-rebuild, DIFF ~5% under -mps-float): full decode done. Structure:
// head = PS normalize of *(obj+152/160) vs rodata pair lbl_802AD278 (mul->merge00
// ->madd->sum0), then guard `if (-dist > lim)` via [ps_neg f13,f0; fcmpu f13,lim;
// ble skip] with NO memory staging; rsqrte path scales staging pair and stages
// {hi,-hi} dir struct at sp18..24; then 4 guard arms (hash getters fn_8014030C
// [f32 ret] / fn_8014036C [s32] / fn_800AA02C(lvl+0x70-class) 1-arg) each writing
// a float slot (sp40/48/50/58) + PS add/sub apply at obj+184/192 (arm 3 subs,
// arms 1/2/4 add + shared tail). WALL: the unstaged neg+compare needs a construct
// plain C lacks - SN_PS_type union member read spills to stack (+8 frame, 2 extra
// insns); *(f32*)&pair and *(double*)&pair ICE cc1 at expmed.c:1115; relational on
// __ps_t ICEs optabs.c:3515; cast-to-union rejected. Suspect C++ operator-inline
// origin (policy: stay in C per AGENTS 4b). Same idiom in fn_801CF0E4 (x2).
// Sweep: test_wip_drafts FAILs without --extra-cflags "-mps-float" (6p-107 tooling
// gap); ps_diff.py 0x801CE098 -mps-float is the real verdict.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 6.3% ([7]rev->4.7% [8]rev->6.3%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD300;
extern f32 lbl_802AD304;
extern char lbl_802AD278[];
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern s32 fn_8014036C(s32, s32, Unk_FFAD6788 *);
extern s32 fn_800AA02C(Unk_9994C3F5 *);

s32 fn_801CE098(Unk_7258DEBD *arg0) {
    char fr[0x58];
    register void *a0 __asm__("r28");
    register __ps_t *pw __asm__("r31");
    register f32 *fp __asm__("r31");
    Unk_130D31C8 *obj;
    char *lv24;
    f32 lim;
    s32 ret;
    f32 res;
    s32 cnt;
    __ps_t sa;
    __ps_t sb;
    __ps_t rv;
    SN_PS_type dt;
    __ps_t o184;
    __ps_t o192;
    Unk_073F5245 *obj2;

    a0 = arg0;
    obj = ((Unk_7258DEBD *)a0)->unk0xC;
    lim = lbl_802AD300;
    pw = (__ps_t *)(void *)fr;
    fp = (f32 *)(void *)fr;
    lv24 = (char *)((Unk_7258DEBD *)a0)->unk0x15A0 + 0x24;
    *(__ps_t volatile *)&pw[0] = obj->unk0x98;
    pw[0] = obj->unk0xA0;
    fp[1] = lim;
    sb = pw[0];
    sa = pw[0];
    rv = *(__ps_t *)&lbl_802AD278;
    sa = __builtin_ps_mul(sb, sb);
    sa = __builtin_ps_merge00(sa, rv);
    sa = __builtin_ps_madd(sb, sa, sb);
    sa = __builtin_ps_sum0(sa, sa, sa);
    dt.ps = sa;
    if (-dt.flt.hi > lim) {
        rv = __builtin_ps_rsqrte(dt.ps);
        sb = __builtin_ps_muls0(pw[0], rv);
        fp[12] = rv;
        fp[13] = lbl_802AD304;
        pw[0] = __builtin_ps_mul(sb, fp[12]);
    }
    fp[4] = *(f32 *)pw;
    fp[5] = lim;
    fp[6] = -*(volatile f32 *)&pw[0];
    fp[7] = lim;
    if (((Unk_FFAD6788 *)arg0->unk0x15A0)->unk0x98 != 0) {
        return 0;
    }
    if (((Unk_FFAD6788 *)arg0->unk0x15A0)->unk0x128 != 0) {
        obj2 = (void *)((Unk_7258DEBD *)a0)->unk0xC;
        res = fn_8014030C(QB_LIP_SIDE_HOP_SPEED, 1, (s32)obj2);
        ret = 1;
        fp[14] = res;
        sa = pw[0];
        sb = pw[7];
        rv = __builtin_ps_neg(sb);
        pw[4] = __builtin_ps_muls0(sa, rv);
        pw[5] = __builtin_ps_muls0(sa, rv);
        o184 = obj2->unk0xB8;
        o192 = obj2->unk0xC0;
        o184 = __builtin_ps_add(o184, pw[4]);
        goto tail;
    }
    if (((Unk_1D62F22E_2 *)lv24)->unk0x4C != 0) {
        cnt = fn_800AA02C((s32)(lv24 + 0x48));
        if (cnt > fn_8014036C(QB_LIP_HELD_JUMP_OUT_TIME, 1, obj)) {
            obj2 = (void *)((Unk_7258DEBD *)a0)->unk0xC;
            res = fn_8014030C(QB_LIP_SIDE_JUMP_SPEED, 1, (s32)obj2);
            ret = 1;
            fp[16] = res;
            sa = pw[0];
            sb = pw[8];
            rv = __builtin_ps_neg(sb);
            pw[4] = __builtin_ps_muls0(sa, rv);
            pw[5] = __builtin_ps_muls0(sa, rv);
            o184 = obj2->unk0xB8;
            o192 = obj2->unk0xC0;
            o184 = __builtin_ps_add(o184, pw[4]);
            goto tail;
        }
    }
    if (((Unk_1D62F22E_2 *)lv24)->unk0x8 != 0) {
        cnt = fn_800AA02C((s32)(lv24 + 4));
        if (cnt > fn_8014036C(QB_LIP_HELD_JUMP_ALONG_TIME, 1, obj)) {
            obj2 = (void *)((Unk_7258DEBD *)a0)->unk0xC;
            res = fn_8014030C(QB_LIP_ALONG_JUMP_SPEED, 1, (s32)obj2);
            ret = 1;
            fp[18] = res;
            sa = *(__ps_t *)&fp[4];
            sb = pw[9];
            rv = __builtin_ps_neg(sb);
            pw[4] = __builtin_ps_muls0(sa, rv);
            pw[5] = __builtin_ps_muls0(*(__ps_t *)&fp[6], rv);
            o184 = obj2->unk0xB8;
            o192 = obj2->unk0xC0;
            o184 = __builtin_ps_sub(o184, pw[4]);
            obj2->unk0xB8 = o184;
            o192 = __builtin_ps_sub(o192, pw[5]);
            obj2->unk0xC0 = o192;
            return ret;
        }
    }
    if (((Unk_C4D756ED *)lv24)->unk0x2C != 0) {
        cnt = fn_800AA02C((s32)(lv24 + 0x28));
        if (cnt > fn_8014036C(QB_LIP_HELD_JUMP_ALONG_TIME, 1, obj)) {
            o184 = __builtin_ps_add(o184, pw[4]);
            o192 = obj2->unk0xC0;
            o184 = obj2->unk0xB8;
            pw[5] = __builtin_ps_muls0(*(__ps_t *)&fp[6], rv);
            pw[4] = __builtin_ps_muls0(sa, rv);
            rv = __builtin_ps_neg(sb);
            sb = pw[10];
            sa = *(__ps_t *)&fp[4];
            fp[20] = res;
            ret = 1;
            res = fn_8014030C(QB_LIP_ALONG_JUMP_SPEED, 1, (s32)obj2);
            obj2 = (void *)((Unk_7258DEBD *)a0)->unk0xC;
        tail:
            obj2->unk0xC0 = o192;
            o192 = __builtin_ps_add(o192, pw[5]);
            obj2->unk0xB8 = o184;
            return ret;
        }
    }
    return 0;
}
