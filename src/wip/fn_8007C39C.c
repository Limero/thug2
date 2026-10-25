// WIP DRAFT (non-matching) — hand-rebuilt 2026-10-04 from the want bytes.
// family=m2c range=0x8007C39C-0x8007C510 size=372B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// BEST MEASURED 2026-10-04: 56.99% masked, object SIZE-EXACT (372B), default
// flags (-O2 -G0 -mcpu=750 -fno-common; no FLAG: line — -Os and the
// -fno-schedule-insns pair all make it shorter and worse).
//
// Semantics (fully reconstructed, from the disassembly + data):
//   pal  = *(u8   **)lbl_80364C40   30-entry table, 4-byte stride, 3 bytes used
//   sc   = *(f32  **)lbl_80300494   30-entry f32 scale table
//   dst  = lbl_8037B5E8 + 0x154      3 adjacent bytes at 4-byte stride
// Per call (index i): for k=0,1,2  dst[i*4+k] = (u8)((f32)((f64)(u32)pal[i*4+k]) * sc[i])
// then saturating double: dst[i*4+k] = (dst[i*4+k] & 0x80) ? 0xFF : dst[i*4+k]*2,
// with the k=0 arm reading the value out of the register (want keeps it in a
// callee-saved register across the whole body) and the k=1,2 arms RELOADING it
// from memory. Returns 1.
//
// PARKED — the HEAD is now structurally byte-for-byte want's (every want insn
// at 0x8007C39C..0x8007C490 has a same-opcode got counterpart in the same
// order; only register NUMBERS differ). What is left is (a) ngccc register
// allocation / reload choices and (b) two final_addr + block-layout ties:
//
//  A. Head renames (23 words) are pure allocation coin-flips:
//     want arg0=r29, i4=r12, pal=r5, sc=r4, 0x43300000-const=r3, p1=r30;
//     got  arg0=r31, i4=r8,  pal=r4, sc=r3, 0x43300000-const=r30, p1=r29.
//     The const only differs because want fits it in a volatile (r3) and got
//     pushes it to a callee-saved reg (r30), which shifts sc/pal down one.
//     Declaration order, `u32` vs `s32` arg0, and inline-vs-named pal/sc make
//     ZERO difference (measured: 40 diffs for all four) — the tie is inside
//     reload, not reachable from C.
//  B. `mr r31,r9` right after the first `stbx` = a copy of the just-stored
//     byte value, used by `andi. r0,r31,0x80` and by the QI shift
//     `rlwinm r0,r31,1,0x18,0x1e`. A `u8 r` local makes ngccc emit the
//     zero-extension `clrlwi r12,r9,0x18` instead (same length, size stays
//     exact). Forcing the QI copy needs an s32 temp for the store AND a QI
//     operand for the test; measured `if (v0 & 0x80) r = 0xFF; else
//     r = (u8)(v0*2);` — test then uses v0's own register (no copy) and the
//     frame grows to 0x28/0x10(r1) (14.3%). Same for the ternary-in-`(u8)`.
//  C. The k=0 tail ternary layout: want `bne / rlwinm / b / li 0xff` (NOT
//     inverted, then-block is the branch target); got `beq / li / b /
//     rlwinm` (branch inverted to skip both arms). Swapping the arms
//     (`if (!(r & 0x80)) r = r*2; else r = 0xFF;`), `r <<= 1`, and
//     `(u8)`-cast ternaries were all measured: none gives want's shape and
//     each costs 1-14 more diffs.
//  D. Tail addressing: want rematerialises the bare anchor per access
//     (`lis; addi` + separate `addi r11,r9,0x155`, i.e. offset on the BASE
//     side) and then uses `lbzx`+`stbx` with that base — the load and store
//     addresses are NOT CSE-unified. The two spellings available in C split
//     that behaviour: `lbl[0x155 + i*4]` keeps lbzx+stbx but folds the offset
//     into the INDEX reg (`addi r10,r0,0x155`, 54.8%); `*((u8*)lbl + 0x155 +
//     i*4)` keeps the offset on the BASE side (2 insns: reloc addend carries
//     0x155) but CSE then unifies load+store into `add r9,r0,r9; stb r0,0(r9)`
//     (this body, 57.0%). A variable base (`dst + 0x155 + i*4`) instead gives
//     `add`+displacement addressing. No spelling found that gets both.
//  E. want also keeps the head's i4 register live into the tail k=0 store
//     (`stbx r0,r28,r12`) AND rematerialises a second copy (`slwi r3,r29,2`)
//     for the k=1/k=2 accesses; got rematerialises once and uses it for all
//     three. Same CSE/reload dead-value mechanism as (B).
// Measured and rejected: m2c's original body (2.8%); one element POINTER
// `&lbl[0x154+i4]` with [0]/[1]/[2] (GCC folds base+index into one `add` and
// switches to displacement stores); `i4` as a variable; tail using the head's
// p1/p2 pointers (they stay live, 24.7%, no rematerialisation); s32 temps with
// a u8 temp only in the tail (19.6%); reading the k=0 tail back from memory
// (23.7%); `(f64)(u32)` vs `(f64)(s32)` — want has NO `xoris`, so the u32 cast
// is load-bearing (the signed one wants a 2^52+2^31 pool double);
// -Os/-fno-schedule-insns*/-fno-gcse/-fno-expensive-optimizations all neutral
// or worse. NOTE: the 4 dead `mr rX,r11` (r11 = 0 on entry) in the middle of
// the head are reproduced by every spelling — do not chase them.
#include "types.h"

extern u8 lbl_8037B5E8[];
extern f32 *lbl_80300494;
extern u8 *lbl_80364C40;

s32 fn_8007C39C(s32 arg0) {
    u8 *dst = lbl_8037B5E8;
    u8 *p0 = dst + 0x154;
    u8 *p1 = dst + 0x155;
    u8 *p2 = dst + 0x156;
    s32 v0, v1, v2;
    u8 r;

    v0 = (f32)((f64)(u32)lbl_80364C40[arg0 * 4]) * lbl_80300494[arg0];
    p0[arg0 * 4] = v0;
    v1 = (f32)((f64)(u32)lbl_80364C40[arg0 * 4 + 1]) * lbl_80300494[arg0];
    p1[arg0 * 4] = v1;
    v2 = (f32)((f64)(u32)lbl_80364C40[arg0 * 4 + 2]) * lbl_80300494[arg0];
    p2[arg0 * 4] = v2;

    r = v0;
    if (r & 0x80) {
        r = 0xFF;
    } else {
        r = r * 2;
    }
    p0[arg0 * 4] = r;
    *((u8 *)lbl_8037B5E8 + 0x155 + arg0 * 4) = (*((u8 *)lbl_8037B5E8 + 0x155 + arg0 * 4) & 0x80) ? 0xFF : *((u8 *)lbl_8037B5E8 + 0x155 + arg0 * 4) * 2;
    *((u8 *)lbl_8037B5E8 + 0x156 + arg0 * 4) = (*((u8 *)lbl_8037B5E8 + 0x156 + arg0 * 4) & 0x80) ? 0xFF : *((u8 *)lbl_8037B5E8 + 0x156 + arg0 * 4) * 2;
    return 1;
}