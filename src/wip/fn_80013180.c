// WIP DRAFT (non-matching) — class-constructor member-init step.
// family=hand range=0x80013180-0x80013204 size=132B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Installs the sentinel / default field values of the class (nine zeros,
// -1 at +0x2C/+0x30/+0x10, 1 at +0x20, 0x10000 at +0x24, 0x64 at +0x28) and
// then dispatches slot-7 of the object's vtable with the adjustor from
// vt+0x18 (vt[7](this + *(s16 *)(vt + 0x18))).
//
// PARKED 2026-10-25: 66.7% (22/33 words).  Store run order now matches want
// word-for-word from +0x2C through +0x28 (five stores and the constant births
// interleaved exactly as retail), which is what the statement-order search
// bought: with the source written in the rotate-left of want's emission the
// first twenty words line up.
//
// RESIDUAL: constant-web REGISTER COLORING plus the 0x10 / 0x38 store pair.
// want holds -1 in r10, 0x10000 in r9, 1 in r8, 0x64 in r11; this build gives
// -1 the lowest free register and shifts the rest by one, so the four
// `li`/`lis` words and their stores differ.  The vcall tail's pointer wants r9
// as well, so the live ranges interleave: pinning the tail pointer or
// permuting the three pointer locals costs the prologue (measured, both
// worse).  The two remaining words are the `stw r0,0x38` / `stw r9,0x10`
// pair, which come out transposed relative to want.
//
// Levers already measured on this body (all <= 66.7%): chained assignments
// for the equal-valued stores (emit left-to-right, no rotation), moving the
// vcall before the store block (prologue grows), 15-statement hill climb over
// adjacent swaps and moves, and the declaration order of the pointer locals.
#include "types.h"

typedef struct T13180 {
    s32 f00, f04, f08, f0C, f10, f14, f18, f1C, f20, f24, f28, f2C, f30, f34, f38;
    void *f3C;
} T13180;

void fn_80013180(T13180 *arg0) {
    void *vt;

    arg0->f20 = 1;
    arg0->f24 = 0x10000;
    arg0->f30 = -1;
    arg0->f10 = -1;
    arg0->f2C = -1;
    arg0->f28 = 0x64;
    arg0->f04 = 0;
    arg0->f08 = 0;
    arg0->f0C = 0;
    arg0->f38 = 0;
    arg0->f14 = 0;
    arg0->f18 = 0;
    arg0->f1C = 0;
    arg0->f00 = 0;
    arg0->f34 = 0;
    vt = arg0->f3C;
    ((void (*)(void *))*(void **)((char *)vt + 0x1C))((char *)arg0 + *(s16 *)((char *)vt + 0x18));
}
