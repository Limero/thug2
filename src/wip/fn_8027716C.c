// WIP DRAFT (non-matching) — parked runtime asm, no C body attempted.
// family=hand range=0x8027716C-0x802771BC size=80B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-11: run-on-stack trampoline (saves r1 to 0x803CAD3C,
// loads a new SP from 0x803CAD38, mtlr/blrl into arg0, restores r1).
// C-UNPRODUCIBLE: manipulates the stack pointer directly; no C spelling
// yields stw r1,0(r5) / lwz r1,0(r5). Same class as fn_80267C7C — likely
// original hand-written runtime asm. Do not burn rounds here.
#include "types.h"

void fn_8027716C(void) {
}
