// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// family=m2c range=0x8021BC54-0x8021BEE0 size=652B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED at NEAR 96.9% (158/163 insns; best of ~30 shapes + flag configs;
// -fno-schedule-insns2 93.3%, others neutral/worse). The ENTIRE body matches:
// frame 0x80 exact (stmw r21@0x54; locals-end round8+4 rule), iterator struct
// @r1+0x10, msg struct @r1+0x20 (0x28B: cmd@20/size@22/data@24/unk2C@2C/
// unk30@30), b48@0x48, flags32@0x4C, hash-probe block (4x fn_8003D9DC with
// QB_BACK_LOGO/QB_DECK_GRAPHIC), both fn_8013CC84 3-arg sites, both
// fn_8013DA08 8-reg-arg + stack-arg sites with u16-clrlwi'd getter results,
// guarded-do enumerator loop with or.-fused copy+latches, exit/final stores.
// Remaining 5 diffs = ONE prologue-window permutation: the want emits the
// two high-half loads, the label address build, the arg0 home copy into
// r26, the r9 address birth and the global load, then a zero into r0, the
// r9-to-r21 copy, the arg1 home copy into r29 and the two word stores.
// This draft keeps the run up to the arg0 home copy, then homes arg1 into
// r29 early, performs the copy and the birth, stores the second word,
// zeroes r0, sinks the global load to last, and stores the first word.
// i.e. arg1-home emits early instead of after COPY; global lwz sinks to the
// call vs want slot 6; store order [8]/[4] swaps. Same doc-15 prologue-window
// family as fn_8021C080 (@89.6%) and parked sibling fn_8021CDA0 (@73.6%).
//
// KEY SHAPES THAT CRACKED THIS BODY (reusable):
// - Double GPR pins split the &iter webs: `register s32 *itv __asm__("r9")
//   register s32 *it __asm__("r21")` + volatile "+r" barrier on itv + hop
//   char*-chain (hop=itv; bar(hop); it=(s32*)hop). Without pins the home web
//   numbers late (web-splitter pseudo -> r24) and ALL constants shift one
//   slot (r21/r22/r23 vs want r22/r23/r24) = 22 diffs. Pins alone took
//   85.9% -> 96.9%. No frame corruption despite mixed barriers (§73-151 did
//   NOT fire here).
// - Pinned DEAD mgr load (`register s32 mgr __asm__("r3"); mgr = *(s32*)
//   lbl_80303448;` with the call site still using the inline expression):
//   the pin keeps the load alive as a side effect, emitting want's
//   global->r3 without any mr at the bl. In C080 the same trick routes the
//   REAL argument; here it is pure placement.
// - lblv staged FIRST pulls [lisA][addi-lbl] above the arg homes.
// - b48 read must be a WORD load staged through an s32 temp then stored u8
//   (recipe §6m-94): direct *(u8*) narrows to lbz vs want lwz+stb.
// - Store-order rotation applies to the init pair: source [it8-store,
//   it4-store] emits [4(r9)][8(r9)] (want's order).
//
// Arity ground truths audited from callee prologues this round:
// fn_80137AD4 leaf getter 1-arg per-site (r4 never set); fn_802297C0 1-arg
// s32 (result captured AND tested -> or. r27,r3,r3 fusion); fn_80229770/
// fn_8022A9B8/fn_8013FB8C 1-arg getters; fn_8003D9DC(s32,u32) 2-arg;
// fn_80137CB4 = 1-ARG msg-init (m2c invented 2 args); fn_8013CC84 3-arg
// (*(arg0+8), ret, &msg) both sites (m2c invented a 5-arg second call);
// fn_8021BEE0 1-arg (reads only r3); fn_8013DA08 = 9-arg with the 9th on
// the CALLER's stack (callee reads its own 0x2a8(r1)) — constant 1 hoisted
// pre-loop into r24; fn_8005C4E4/C47C results truncated u16 at call sites
// (clrlwi) while C4B0/C448 stay s32.
//
// Retry hints for the last window: mgr-stmt position x5 (before/after
// lblv/birth/barrier — all keep the load late or double-load via an r10
// home when unpinned); non-volatile barriers (same score, different perm);
// opaque-use of it (+1 insn DIFF); direct member stores (fold to r1
// displacement - wrong); m2c-literal no-pointer shape (frame re-sorts,
// stores fold to displacement); decl-order swaps; flags above. If another
// function cracks "arg1-home-after-COPY + early-global-lwz", port it here.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern char lbl_802AFE00[];
extern char lbl_802AFE0C[];
extern char lbl_80303448[];
s32 fn_80137AD4(Unk_F386DC9F *);
s32 fn_8022986C(CScript *);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_802297C0(CScript *);
s32 fn_8013FB8C(Unk_72BBAD33 *);
s32 fn_80229770(CScript *);
s32 fn_8003D9DC(s32, u32);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8013DA08(s32, Unk_1EE3EA6A *, s32, s32, void *, char *, s32, s32, s32);
s32 fn_8005C4E4(s32);
s32 fn_8005C4B0(s32);
s32 fn_8005C47C(s32);
s32 fn_8005C448(s32);
s32 fn_8021BEE0(void *);

typedef struct {
    s32 it0;
    s32 it4;
    s32 it8;
    char _p0[4];
    u8 cmd;
    char _p1[1];
    u16 size;
    void *data;
    char _p2[4];
    s32 unk2c;
    u8 unk30;
    char _p3[0x17];
    u8 b48;
    char _p5[3];
    s32 v4c;
} fr_t;

void fn_8021BC54(Unk_9994C3F5 *arg0, Unk_31DE137E *arg1) {
    fr_t fr;
    register s32 *itv __asm__("r9");
    register s32 *it __asm__("r21");
    CScript *entry;
    s32 temp_r27;
    s32 var_r28;
    s32 temp_r30;
    u16 temp_r30a;
    s32 temp_r7;
    u16 temp_r30b;
    s32 temp_r7b;
    s32 t8;
    s32 t8b;
    s32 temp_b48;
    char *hop;
    s32 lblv;
    register s32 mgr __asm__("r3");

    lblv = (s32)lbl_802A83F8;
    mgr = *(s32 *)lbl_80303448;
    itv = &fr.it0;
    __asm__ volatile("" : "+r"(itv));
    itv[2] = lblv;
    hop = (char *)itv;
    __asm__ volatile("" : "+r"(hop));
    it = (s32 *)hop;
    itv[1] = 0;
    if ((fn_80137AD4(*(s32 *)lbl_80303448) == 1) || (fn_8022986C(arg1) != 0)) {
        it[2] = (s32)lbl_802A83F8;
        return;
    }
    entry = fn_8021D454((s32)arg0, it, 0);
    if (entry != 0) {
        do {
            temp_r27 = fn_802297C0(entry);
            if (temp_r27 != 0) {
                if (entry != arg1) {
                    if (fn_8013FB8C(arg1->unk0x1C) != 1) {
                        if (fn_80229770(entry) != 0) {
                            var_r28 = 0;
                            temp_r30 = arg1->unk0x50 + 4;
                            if (fn_8003D9DC(temp_r30, QB_HAT_LOGO) != 0) {
                                var_r28 = 1;
                            }
                            if (fn_8003D9DC(temp_r30, QB_FRONT_LOGO) != 0) {
                                var_r28 |= 2;
                            }
                            if (fn_8003D9DC(temp_r30, QB_BACK_LOGO) != 0) {
                                var_r28 |= 4;
                            }
                            if (fn_8003D9DC(temp_r30, QB_DECK_GRAPHIC) != 0) {
                                var_r28 |= 8;
                            }
                            fn_80137CB4(&fr.cmd);
                            temp_b48 = *(s32 *)(entry->unk0x18 + (s32)0x18);
                            fr.data = &fr.b48;
                            fr.b48 = (u8)temp_b48;
                            fr.cmd = 0x96;
                            fr.size = 1;
                            t8 = arg0->unk0x8;
                            fr.unk2c = 2;
                            fr.unk30 = 0xA;
                            fn_8013CC84(t8, fn_8022A9B8(arg1), &fr.cmd);
                            temp_r30a = fn_8005C4E4(temp_r27);
                            temp_r7 = fn_8005C4B0(temp_r27);
                            fn_8013DA08(arg0->unk0x8,
                                        arg1->unk0x1C, 0x98,
                                        temp_r30a, temp_r7, (s32)lbl_802AFE00, 0xA, 0, 1);
                            temp_r30b = fn_8005C47C(temp_r27);
                            temp_r7b = fn_8005C448(temp_r27);
                            fn_8013DA08(arg0->unk0x8,
                                        arg1->unk0x1C, 0x97,
                                        temp_r30b, temp_r7b, (s32)lbl_802AFE0C, 0xA, 0, 1);
                            fr.v4c = var_r28;
                            fr.cmd = 0x9A;
                            fr.data = &fr.v4c;
                            fr.size = 4;
                            t8b = arg0->unk0x8;
                            fr.unk2c = 2;
                            fr.unk30 = 0xA;
                            fn_8013CC84(t8b, fn_8022A9B8(arg1), &fr.cmd);
                        }
                    }
                }
            }
            entry = fn_8021D4E8((s32)arg0, &fr.it0, 0);
        } while (entry != 0);
    }
    it[2] = (s32)lbl_802A83F8;
}
