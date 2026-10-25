# 35 — cr1-call-preserved + individual-save prologue convention

**Status: OPEN (zone convention wall).** Members: fn_802511DC (6.2%),
fn_80250F2C (3.4%), fn_80251490, fn_802518D8 — pool/bitstream zone,
11 DOL sites with this prologue shape, none matched DOL-wide.

## Symptom (two coupled artifacts)

1. Prologue: want emits `[stwu r1,-N][stw rHigh,8(r1) FIRST][individual
   stw saves r14..r26][mflr r27]` — no stmw, and the high saved reg is
   stored before mflr lands. A DOL-wide scan of every `[stwu][stw
   rHigh,8]` opener found ZERO matched exemplars; ngccc always emits
   stmw + mflr r0 (+ mtcrf when CR is live).
2. cr1 treated as CALL-PRESERVED: want caches a compare result in cr1
   BEFORE a `bl` and consumes it AFTER another `bl` with no mfcr/mtcrf.
   cc1 moves such values to saved-CR fields + mfcr/mtcrf pairs.

## What was tried

All spellings/flags across all five ProDG versions for the compare
placement; explicit mr-wedges (see AGENTS.md §6aw-175); register pins;
hand-ordered save sequences. The prologue shape and the cr1 liveness are
not reachable from C under any in-tree compiler build.

## Interpretation

The game's runtime/allocator objects were likely compiled with a
different ABI flag or compiler pass that (a) spills callee-saves
individually with the high reg first and (b) honors cr1 as
call-preserved (ProDG's own convention differs from GCC 2.95's
"cr1 is call-clobbered" model). Not fixable per-source.

## Unpark condition

A dtk-side carve-out cannot fix codegen; needs either a ProDG build whose
cc1 honors these two conventions or hand-written asm coverage for the 11
sites. Until then: park immediately on the prologue signature +
cr1-across-bl pattern; do NOT grind shapes.
