// Promoted 2026-09-19 (second half of the map-merged 0x80274B10 region).
// range 0x80274B20-0x80274B4C (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Calls the global function pointer at lbl_8030B85C. symbols.txt called this
// address type:label because the map's fn_80274B10 (0x3C) swallowed it; it is
// a real function entry point (fn_802740DC does `bl 0x80274B20`), so it is
// registered here as type:function size:0x2C and given its own split.
#include "types.h"
extern void (*lbl_8030B85C)(void);

void lbl_80274B20(void) {
    lbl_8030B85C();
}
