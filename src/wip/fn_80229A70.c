// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-25
// PARKED @96.6% NEAR (57/59): sole residue = prologue pair-order tie
// [ori][mr r3,r30][stw 0x1d8(r31)] vs got [ori][stw][mr] — expand_call
// arg-move vs independent store scheduling coin-flip. Resisted: both
// statement orders, "+r" barrier on mgr, -fno-sched-spec/-interblock/
// -schedule-insns(2) singles+pairs (best 96.6% flagless), RMW-first
// (93.2%: aliasing sinks global load). Register pins r31(self)/r30(mgr)
// + phantom case 0: are REQUIRED — removing either loses roles/tree.
// Latest revision hands the first callee a named copy of mgr taken before
// the flag store (`first = mgr`), so the argument move has a source
// position ahead of the store instead of being born at call expansion.
// family=m2c range=0x80229A70-0x80229B5C size=236B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 fn_8009CF2C(CStruct * mgr);
s32 fn_80219698(CStruct * mgr);
s32 fn_8022986C(CScript * arg0);
s32 fn_80219638(Unk_C7387A53 * mgr);
void fn_80137CB4(Unk_9F066EC1 * cmd);
s32 fn_8021B554(Unk_9994C3F5 * mgr);
s32 fn_8022A9B8(Unk_31DE137E * arg0);
void fn_8013CC84(void * obj, s32 val, Unk_C71E6DE1 * cmd);
s32 fn_8021D7F0(s32 mgr);
void fn_8021CDA0(Unk_9994C3F5 * mgr);

struct cmd_s {
    u8 b0;
    char pad0[0xB];
    s32 w0C;
    u8 b10;
    char pad1[0x17];
};

void fn_80229A70(void *arg0) {
    struct cmd_s cmd;
    register void *self __asm__("r31");
    register s32 mgr __asm__("r30");
    s32 first;

    self = arg0;
    mgr = lbl_80305F9C;
    /* Named copy for the first call's argument: the copy is born before the
       flag store, so the argument move can be emitted ahead of the store
       (the residual orders mr r3,r30 before stw 0x1d8(r31)). */
    first = mgr;
    ((CScript *)self)->unk0x1D8 |= 0x20;
    if (fn_8009CF2C(first) == 0) {
        return;
    }
    if (fn_80219698(mgr) == 0) {
        return;
    }
    if (fn_8022986C(self) != 0) {
        return;
    }
    switch (fn_80219638(mgr)) {
    case 0:
        break;
    case 1:
        fn_80137CB4(&cmd);
        mgr = fn_8021B554(mgr);
        cmd.b0 = 0x5E;
        cmd.w0C = 2;
        cmd.b10 = 8;
        fn_8013CC84(mgr, fn_8022A9B8(self), &cmd);
        break;
    case 2:
        if (fn_8021D7F0(mgr) == 0) {
            fn_8021CDA0(mgr);
        }
        break;
    }
}
