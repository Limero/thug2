// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-09-24, unblocked 2026-10-09. family=hand range=0x8025ED48-0x8025ED70 size=40B
// range 0x8025ED48-0x8025ED70 size=0x28 (40B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern char fn_8025EC94[];
extern void fn_8025FAD8(void *arg0);

void fn_8025ED48(void) {
    fn_8025FAD8(fn_8025EC94);
}
