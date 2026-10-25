// range 0x80018178-0x800181A4 (0x2C). Byte-identical.
// Identification: global state OR-gate — returns 1 if either the
// lbl_80300150 state equals 2 or the lbl_8037B7A8 (.bss) counter/(list)
// head is non-zero, else 0. Likely a "should run / is claimed" query.
//
// Matching key: only the boolean `||` form reproduces want's shared
// `li r3,1` destination with a single early beqlr — `return (g1==2) ||\n// (g2 != 0);` — written if/else or with explicit returns, GCC splits the
// two `li r3,1` paths (4-6/11).
#include "types.h"
extern char lbl_80300150[];
extern char lbl_8037B7A8[];
s32 fn_80018178(void) {
    return (*(s32 *)lbl_80300150 == 2) || (*(s32 *)lbl_8037B7A8 != 0);
}