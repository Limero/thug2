// WIP DRAFT (non-matching) — hand edit (re-derived from disasm; script-engine loader family)
// family=m2c range=0x80200DA0-0x802010C8 size=808B
// FLAG: -fno-rerun-cse-after-loop
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED: DIFF 29.0% w/ -fno-sched-spec (2026-08-25). Structure fully
// recovered (see body): init-store run, fn_80201C14(arg0, fn_800A398C(
// lbl_80301A38, obj->C->18)) setup pair, chained fn_80187934(Game_GetGoalManager(),1)
// -> +0xA24, v87==1 gate storing THE RETURN REG (stw r3), then guarded
// do-while over fn_801259C8(0x4E46CC28,1) table with 8 hash-gated arms.
// Progress: prologue/frame/stmw span now MATCH (r29-guard var
// exposed the span mechanism; tf staged-first float local fixed the hoisted
// lis/lfs position; whole-run rotate-right applied to the init store run).
// Residual walls: (1) the two tf float stores SWAP emission order under every
// arrangement (scheduler sinks both across the int run; want keeps a54 before
// a60 straddling five int stores); (2) arg0 home lands r29 vs want r30 and the
// loop registers shift one role (want: &lbl=r23 offIV=r24 tbl=r25 cnt=r26 i=r27
// zero=r28 mulli-scratch=r29 ent=r31 — the mulli result is live ACROSS the
// arm calls so it lands in callee-saved r29 inside the stmw range; every C
// shape either DCEs the walking IV or re-homes the mulli into scratch).
// Next hints: try stores via explicit per-site `off2 = i * 0x24`
// staged BEFORE the hash-call of each arm (forces call-spanning liveness),
// or -fno-strength-reduce to keep the IV real.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AEC48[];
extern f32 lbl_802AEC4C;
extern s32 lbl_80301A38;
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern void fn_80201C14(Unk_59E38960 * arg0, Unk_6A70655D * arg1);
extern s32 Game_GetGoalManager();
extern s32 fn_80187934(Unk_6BF95B44 * arg0, s32 arg1);
extern s32 Script_GetInteger(s32 arg0, s32 arg1);
extern void *fn_801259C8(s32 arg0, s32 arg1);
extern void *fn_80129528(CStruct * arg0, s32 arg1);
extern s32 fn_80128978(void *arg0, u32 hash);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_801293FC(CStruct * arg0, s32 arg1);
extern s32 fn_8012935C(Unk_F8A5095F * arg0, s32 arg1);
extern s32 GetChecksum(CStruct * arg0, s32 arg1);

void fn_80200DA0(Unk_09AB3653 *arg0) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 v87;
    s32 i;
    s32 off;
    void *ent;
    CStruct *tbl;
    s32 count;
    s32 zero;
    f32 tf;

    tf = lbl_802AEC4C;
    arg0->unk0x1C = 1;
    arg0->unk0xA54 = tf;
    arg0->unk0xA00 = 0;
    arg0->unk0x9F8 = 0;
    arg0->unk0xA28 = 0;
    arg0->unk0xA2C = 0;
    arg0->unk0xA5C = 0;
    arg0->unk0xA60 = tf;
    arg0->unk0xA58 = 0;
    arg0->unk0xA50 = 0;
    arg0->unk0xA88 = 0;
    arg0->unk0xA8C = 0;
    arg0->unk0xA90 = 0;
    arg0->unk0xA94 = 0;
    fn_80201C14(arg0, fn_800A398C(lbl_80301A38, *(s32 *)(arg0->unk0xC + 0x18)));
    arg0->unk0xA24 = fn_80187934(Game_GetGoalManager(), 1);
    v87 = Script_GetInteger(QB_BUMP_STATS, 1);
    if (v87 == 1) {
        arg0->unk0x9FC = v87;
    }
    i = 0;
    tbl = fn_801259C8(QB_STATS_GOALS, 1);
    count = tbl->unk0x4;
    if (i < count) {
        zero = 0;
        off = 0;
        do {
            ent = fn_80129528(tbl, i);
            if (fn_80128978(ent, QB_GOALTYPE)) {
                GetChecksum_2((s32)ent, QB_GOALTYPE, &sp8, 1);
                *(s32 *)((char *)arg0 + 0x20 + off) = sp8;
            }
            if (fn_80128978(ent, QB_STATTYPE)) {
                GetChecksum_2((s32)ent, QB_STATTYPE, &spC, 1);
                *(s32 *)((char *)arg0 + 0x24 + off) = spC;
            }
            if (fn_80128978(ent, QB_VALUE)) {
                sp10 = zero;
                GetArray((s32)ent, QB_VALUE, &sp10, 1);
                *(s32 *)((char *)arg0 + 0x28 + off) = fn_801293FC(sp10, arg0->unk0xA24);
            }
            if (fn_80128978(ent, QB_VALUE_STRING)) {
                sp14 = zero;
                GetArray((s32)ent, QB_VALUE_STRING, &sp14, 1);
                *(s32 *)((char *)arg0 + 0x38 + off) = fn_8012935C(sp14, arg0->unk0xA24);
            }
            if (fn_80128978(ent, QB_TEXT)) {
                sp18 = (s32)lbl_802AEC48;
                GetString((s32)ent, QB_TEXT, &sp18, 1);
                *(s32 *)((char *)arg0 + 0x34 + off) = sp18;
            }
            if (fn_80128978(ent, QB_COMPLETE)) {
                GetInteger((s32)ent, QB_COMPLETE, &sp1C, 1);
                *(s32 *)((char *)arg0 + 0x30 + off) = zero;
            }
            if (fn_80128978(ent, QB_VALUE_TRICK)) {
                sp20 = zero;
                GetArray((s32)ent, QB_VALUE_TRICK, &sp20, 1);
                *(s32 *)((char *)arg0 + 0x3C + off) = GetChecksum(sp20, arg0->unk0xA24);
            }
            if (fn_80128978(ent, QB_VALUE_TAPS)) {
                sp24 = zero;
                GetArray((s32)ent, QB_VALUE_TAPS, &sp24, 1);
                *(s32 *)((char *)arg0 + 0x40 + off) = fn_801293FC(sp24, arg0->unk0xA24);
            }
            *(s32 *)((char *)arg0 + 0x2C + off) = zero;
            i++;
            off += 0x24;
        } while (i < count);
    }
}
