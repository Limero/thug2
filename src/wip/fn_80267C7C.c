// WIP DRAFT (non-matching) — parked runtime asm, no C body attempted.
// family=hand range=0x80267C7C-0x80267CC8 size=76B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RE-TRIAGED 2026-10-13: still C-UNPRODUCIBLE runtime asm (no mflr
// with blrl calls, LR restored from caller-homed slot). No body change; do not burn rounds.
// PARKED 2026-10-11: atexit/dtor-table runner (calls each fnptr in the
// 0x80310AB8 table via mtlr/blrl until a null entry). C-UNPRODUCIBLE:
// the body makes blrl calls yet the prologue has NO mflr, and the epilogue
// restores LR from 0x14(r1) — above its own 0x10 frame, i.e. a
// caller-homed slot. GCC always emits mflr when it sees calls, so no C
// spelling yields this shape; whole-body asm transcription is banned (§5).
// Likely original hand-written runtime asm (cf. the 0x8027716C
// stack-switcher). Do not burn rounds here; carve only if an asm
// exception is ever granted for runtime units.
#include "types.h"

void fn_80267C7C(void) {
}
