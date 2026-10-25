// WIP DRAFT (non-matching) — hand-redrafted from want disasm 2026-09-07
// family=c range=0x80057EF4-0x80057F44 size=80B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// WANT shape: tail-call dispatch helper. r9 = arg0 (stays live across the
// call); load r3 = *(r9+0x10) FIRST and test it (cmpwi r3,0 / bne L2 —
// L2 = the bl fn_8005F338 tail block); if zero, r3 = *(r9+0x14), r9 =
// *(r3+0xC), r0 = lha *(r9+0x40), r9 = *(r9+0x44), r3 += r0, mtlr r9,
// blrl, then b back over the fn_8005F338 call so both paths share the
// epilogue. The `lha` at +0x40 means unk0x40 is a SIGNED HALFWORD offset
// field (s16), not the header's s32 — the s32 view would emit lwz.
// Function-ptr field unk0x44 is called 1-arg (r3 only).
// WANT also materializes arg0 into a register first (mr r9,r3 at +0x0c) —
// the pointer must be named before the 0x10 test so it survives into the
// zero-branch; volatile pin reproduces that.
// The 0x40 load and 0x44 load must BOTH go through the same named base
// (want reuses r9 for both: lha r0,0x40(r9) then lwz r9,0x44(r9) — the
// register is reloaded in place); inline member chains fold to r3.
// r9 is pinned for the base so the callee reload goes through it; the
// s16 pun keeps the lha (plain (s16) cast on an s32 field emits lwz+extsh).
// The lha must sit between the base reload (lwz 0xC) and the callee reload
// (lwz 0x44) — want's exact interleave. The arg is computed from the pun
// directly in the call so the lha lands in the middle slot.
// Layout: the non-zero branch must land INSIDE the else block (bne to the
// bl fn_8005F338 block directly after the blrl) — want's `b .+8` skips
// only the blrl. Ours currently jumps to the epilogue instead.
#include "types.h"
#include "structs.h"
void fn_8005F338(void *o);
void fn_80057EF4(Unk_C8FEE62D *arg0) {
    register Unk_C8FEE62D *temp_r9 __asm__("r9");
    register s32 var_r3 __asm__("r3");
    register s32 off __asm__("r0");
    register s32 (*temp_r9_2)(void *) __asm__("r9");

    temp_r9 = arg0;
    var_r3 = temp_r9->unk0x10;
    if (var_r3 == 0) {
        var_r3 = temp_r9->unk0x14;
        __asm__("" : "+r"(var_r3), "+r"(temp_r9));
        temp_r9 = (Unk_C7387A53 *)((Unk_C7387A53 *)var_r3)->unk0xC;
        __asm__("" : "+r"(temp_r9), "+r"(var_r3));
        off = (s16)(*(volatile s16 *)&((Unk_C7387A53 *)temp_r9)->unk0x40);
        temp_r9_2 = (s32 (*)(void *))((Unk_C7387A53 *)temp_r9)->unk0x44;
        __asm__("" : "+r"(temp_r9_2), "+r"(off), "+r"(var_r3));
        var_r3 = var_r3 + off;
        temp_r9_2(var_r3);
        return;
    }
    fn_8005F338(arg0->unk0x10);
    return;
}
