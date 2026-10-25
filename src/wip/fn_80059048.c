// WIP DRAFT (non-matching) — hand-reconstructed from the want bytes
// family=m2c range=0x80059048-0x80059218 size=464B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04. Best measured: 13.08% masked (93 of 107 aligned words),
// object 428B vs want 464B (9 words short — per AGENTS §6es the aligned % is
// meaningless until the length matches).
//
// WHAT IS NOW KNOWN (all verified against the want):
//   * lbl_80364C38 is an array of five 0x1C-byte records. Fields used here:
//     +0x4 (block of count*0x10 bytes), +0x8, +0x14, +0x18 (count*4-byte
//     blocks), +0xC/+0x10 are f32 (fn_80059380), +0x0 is s32 copied from
//     self (fn_80059258). Record 0 is initialised inline, records 1..4 by the
//     4-iteration loop; all four blocks of every record are then memset(0).
//   * lbl_8030047C = count (u32), lbl_80300480 = arg1, lbl_80300494 = f32*
//     filled with lbl_802934A0. All three are *symbol* references (HA16/LO16
//     relocs mask-match the linked `lis rN,0x8030 / stw rN,0x480(rN)` form);
//     writing them as literal integers instead emits lis+ori+stw and diverges.
//   * The four empty counted loops are the house idiom
//         n = count - 1;  if (count != 0) { do { n -= 1; } while (n != -1); }
//     i.e. the matched pattern of src/fn_8000E978.c and src/fn_80026054.c.
//     That form reproduces the want's `cmpwi rX,0 / addi rX,rX,-1 / bne`;
//     `do {} while (n-- != 0)` adds a spurious `mr` copy and `while (n) n--;`
//     adds a duplicated guard + addic. — worth a recipes entry.
//   * The first Mem_Alloc result is live across that loop, so the source has
//     to keep it in a variable and store it *after* the loop (`mr r0,r3`
//     before the loop, `stw r0,4(r30)` after).
//
// BLOCKER (register-allocation / address-form lottery in the 4-iteration
// loop, not semantics):
//   The want hoists five loop-invariant field addresses into r23 (=&a[1]),
//   r20(+4), r21(+0x14), r22(+0x18), r19(+8) and then uses
//   `mulli r31,r28,0x1c` + `stwx/lwzx` indexed accesses, which also forces
//   13 callee-saved registers (frame 0x40, lr@0x44, stmw r19) and 4 separate
//   `lis r9,-0x7fca` rematerialisations of the record base. Every natural
//   spelling of the same C (`a[i+1].unk0x4`, `e[i].unk0x4`,
//   `((void**)(a+1))[i*7]`, `*(void**)(lbl_80364C58 + i*0x1C)`,
//   `lbl_80364C38[i+1].unk0x4`) makes ngccc either strength-reduce the index
//   into a walked pointer with the field offsets folded into the store
//   displacement (428B, this draft), or - with the array-symbol spelling -
//   keep the mulli+stwx form but recompute the index twice per iteration
//   (440B). Measured variants: 428B/13.08%, 440B/4.55%, 440B/4.55%,
//   424B/7.55%, 428B/0.95%; -fno-strength-reduce and -fno-schedule-insns2 do
//   not change the address form, so this is expand/reload cost-model
//   behaviour, not a flag or a mis-decode.
#include "types.h"

typedef struct Unk_80364C38 {
    s32 unk0x0;
    void *unk0x4;
    void *unk0x8;
    char pad0xC[0x8];
    void *unk0x14;
    void *unk0x18;
} Unk_80364C38;

extern s32 lbl_8030047C;
extern s32 lbl_80300480;
extern f32 *lbl_80300494;
extern f32 lbl_802934A0;
extern Unk_80364C38 lbl_80364C38;
void *Mem_Alloc(s32);
void *memset(void *, s32, s32);

void fn_80059048(s32 count, s32 arg1) {
    Unk_80364C38 *a = &lbl_80364C38;
    s32 n1;
    s32 n2;
    s32 k;
    s32 m;
    s32 i;
    s32 sz4;
    s32 sz16;
    void *p1;
    void *p2;
    f32 *arr;

    lbl_80300480 = arg1;
    lbl_8030047C = count;
    sz16 = count * 0x10;
    p1 = Mem_Alloc(sz16);
    n1 = count - 1;
    if (count != 0) {
        do {
            n1 -= 1;
        } while (n1 != -1);
    }
    sz4 = count * 4;
    a->unk0x4 = p1;
    p2 = Mem_Alloc(sz4);
    n2 = count - 1;
    k = n2;
    if (count != 0) {
        do {
            n2 -= 1;
        } while (n2 != -1);
    }
    a->unk0x8 = p2;
    a->unk0x14 = Mem_Alloc(sz4);
    a->unk0x18 = Mem_Alloc(sz4);
    for (i = 0; i <= 3; i++) {
        a[i + 1].unk0x4 = Mem_Alloc(sz16);
        m = k;
        if (k != -1) {
            do {
                m -= 1;
            } while (m != -1);
        }
        a[i + 1].unk0x8 = Mem_Alloc(sz4);
        m = k;
        if (m != -1) {
            do {
                m -= 1;
            } while (m != -1);
        }
        a[i + 1].unk0x14 = Mem_Alloc(sz4);
        a[i + 1].unk0x18 = Mem_Alloc(sz4);
        memset(a[i + 1].unk0x4, 0, sz16);
        memset(a[i + 1].unk0x8, 0, sz4);
        memset(a[i + 1].unk0x14, 0, sz4);
        memset(a[i + 1].unk0x18, 0, sz4);
    }
    arr = Mem_Alloc(sz4);
    lbl_80300494 = arr;
    for (i = 0; i < count; i++) {
        *arr = lbl_802934A0;
        arr++;
    }
}
