// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80274B10-0x80274B20 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// MATCHED 2026-09-19: the map's 0x3C "function" at 0x80274B10 is really TWO
// functions — this noreturn `abort()` stub plus lbl_80274B20 (0x2C, its own
// split in src/lbl_80274B20.c), which fn_802740DC calls directly. `abort` is
// noreturn, so CW keeps the LR-save prologue but drops the unreachable
// epilogue and the next function's prologue follows immediately; that is why
// the map's size (distance to the next function symbol) covers both and the
// second entry point shows up as a "label inside fn_80274B10".
// Kept as separate objects because dtk rejects a function symbol that overlaps
// a split range, and objdiff only resolves relocations for functions inside
// the unit's own range (the merged single-object form scored 26.67%).
#include "types.h"
extern void abort(void);

void fn_80274B10(void) {
    abort();
}
