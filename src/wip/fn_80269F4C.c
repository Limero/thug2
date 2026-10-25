// sprintf (0x80269F4C) - SN ProDG newlib runtime, varargs wrapper over the
// printf engine fn_8026BC98(file, fmt, ap). Builds a stack FILE (dst,
// INT_MAX bounds, flags 0x208, _impure_ptr data) plus a 12B va_list copy at
// sp+0x70 from the __builtin_saveregs area at sp+0xE0, calls the engine,
// NUL-terminates through the engine-updated f._p, returns the count.
// family=m2c range=0x80269F4C-0x8026A024 size=216B
// PARKED at 21/54 (38.9%) masked, SIZE-EXACT 216B. Entry (prologue, saveregs
// init+saves, frame 0xF8, r31 const-home), tail (bl..blr) and homes
// (s=r12, imp, r11 copy-dest base, mr r5, CSE'd stw r31,0x70) all exact.
// RESIDUAL: `mr r12,r3` sits BEFORE the GP saves in want (offset 0x24) but
// every explicit copy (plain/pin/barrier/asm-mr, before AND after saveregs,
// all sched-flag combos) sinks to 0x60-0x64 (re-verified 2026-09-13:
// -fno-schedule-insns[-2]/-fno-sched-spec all keep it at 0x60-0x64).
// BREAKTHROUGH 2026-09-13 (vacate mechanism, T6/T10): assigning the saveregs
// result (`register void *sv3 __asm__("r3"); sv3 = __builtin_saveregs();`
// + opaque `__asm__(""::"r"(sv3))` use) forces a COMPILER-generated vacate
// `mr r12,r3` at EXACTLY 0x24 (str must vacate r3 for the return value;
// coalesces to r12 pinned AND unpinned). This SOLVES the anchor sub-problem.
// WALL (floor proof — do not re-grind without a new idea): sv must stay live
// for the vacate, so its materialization `addi r3,r1,0xe0` always emits (+1);
// assigned-form also rotates const-init to the top and breaks the word0
// `stw r31,0x70` CSE (const goes r0, copy via memory: +1). Best shape = 224B,
// cap even with perfect pressure fixes = 220B. Size-exact + mr@0x24 is
// unreachable in ngccc: no want insn writes r3 before 0x94, so only an
// expansion-vacate (costs +1) or a 70-insn upward hoist (ngccc does ALAP,
// SN did AEAP) can place it.
// SOURCES (2026-09-13, online hunt — true source found, still blocked below).
// This is newlib's sprintf.c, stable for decades (eblot/newlib, nacl-newlib,
// sourceware CVS all identical):
//   f._flags = __SWR | __SSTR; f._bf._base = f._p = str;
//   f._bf._size = f._w = INT_MAX; va_start(ap, fmt);
//   ret = _svfprintf_r(_REENT, &f, fmt, ap); va_end(ap); *f._p = 0; return ret;
// SN's copy DIFFERS in two places: (1) it stores impure to f._data (SN
// 3-arg engine takes reent via FILE, not as a param); (2) NO `f._file = -1`
// (want has no 0x8e store) — revision discriminator: SN's tree predates the
// _file=-1 addition (or SN dropped it). So the body above (minus _file, plus
// _data) IS the true source modulo va_start form.
// DECOMPOSITION (nB probe: `...` fn with NO va builtins still emits the full
// save block): the BACKEND emits [GP saves][bne cr1][stfds] unconditionally
// for every varargs fn; `__builtin_saveregs()` adds ONLY the triplet inits.
// The triplet IS the va_list (va-ppc.h SYSV layout {gpr,fpr,overflow,regsave}
// = {0x02000000, r1+0x100, r1+8}: gpr=2 named GP args, fpr=0 — our ap_t
// matches it exactly). va_start common code (va-ppc.h) uses frame_address+
// varargs_offset/next_arg (all inline, no calls) — but ngccc has NO stdarg.h
// and its `__builtin_va_start` is an out-of-line helper CALL for every
// va_list type, so SN's va_start can only be reconstructed, never included.
// UNBLOCK VERDICT (2026-09-13): correctly parked — exhaustive shape census,
// each capped, so no third shape exists in ngccc -O2:
// (a) explicit copy (C/asm/pin/barrier, any position, all sched flags incl.
// -O1/-Os/-O0: copy sinks to first use at 0x60-0x64; -O0 balloons frame);
// (b) expansion-vacate via assigned saveregs (mr@0x24 EXACT, but sv-def +1
// and rotation +1: best 224B, cap 220B); (c) param-home copy (needs saved
// reg, contradicts r12); (d) backend emission (nB proves backend emits NO
// mr); (e) va_start helper (has call); (f) volatile asm inside expansion
// (impossible — opaque block). Root cause class: SN-cc1 schedules
// low-priority copies AEAP (earliest), ngccc ALAP (latest) — same family as
// doc-15 per-site order flips.
// REOPEN TRIPWIRES (only these falsify the verdict — NOT better headers:
// the proof is compiler-structural, perfect SN headers compile through the
// same expander/scheduler): (1) a zero-cost r3-clobber while str is live
// (no want insn writes r3 before 0x94); (2) a MATCHED fn elsewhere showing
// ngccc hoisting an explicit copy far above its first use across a save
// block (port that exact formulation); (3) SN-vs-stock scheduler delta
// characterized to a flag/idiom by future research.
// PROVEN ALONG THE WAY (do not re-derive):
// - __builtin_va_start/va_copy/va_end are NOT recognized by ngccc 2.95
//   with user types (they become out-of-line implicit calls); use
//   __builtin_saveregs() (recognized: emits saves + {0x02000000,
//   frame+8, frame_low+8} init at top-of-frame) + struct assignment.
// - The 0x70 copy is fieldwise-flavored: word0 via r1-direct
//   `stw r31,0x70(r1)` (CSE'd saveregs constant, NO load), words 1-2 via
//   r11-base loads/stores + `mr r5,r11` for the engine arg.
// - The +0x70 in ap2 is frame-coupled (saveregs temp sits 0x70 above aq in
//   the 0xF8 frame); re-derive if the frame ever shifts.
// - Sibling projects have NO copiable source (tww=MSL/mwcc, crashwoc
//   sprintf/printf/vfprintf are placeholder imports, nfsmw=headers only).
// WIRING (when exact): libs/runtime/src/sprintf.c, runtime lib, cflags_game
// (no SDA flags needed - impure via inline r13 asm like rand.c), plus a
// splits.txt range entry; then cmp-verify the DOL.
#include "types.h"
#include "structs.h"

typedef struct { s32 w0; void *o; void *r; } ap_t;
typedef struct {
    u8 *_p;
    s32 _r;
    s32 _w;
    u16 _flags;
    u16 _file;
    u8 *_bf_base;
    s32 _bf_size;
    char _pad[0x5C - 0x18];
    void *_data;
} FILE_t;
extern s32 fn_8026BC98(void *, const char *, void *);
int sprintf(char *str, const char *fmt, ...) {
    ap_t aq;
    FILE_t f;
    ap_t *ap2;
    register s32 s_pin __asm__("r12");
    void *imp;
    int ret;
    __builtin_saveregs();
    __asm__("mr %0, %1" : "=r"(s_pin) : "r"(str));
    __asm__ volatile("lwz %0, -0x7e60(13)" : "=r"(imp));
    f._flags = 0x208;
    f._bf_base = (u8 *)s_pin;
    f._p = (u8 *)s_pin;
    f._bf_size = 0x7FFFFFFF;
    f._w = 0x7FFFFFFF;
    f._data = imp;
    ap2 = (ap_t *)((char *)&aq + 0x70);
    aq = *ap2;
    ret = fn_8026BC98(&f, fmt, &aq);
    *f._p = 0;
    return ret;
}
