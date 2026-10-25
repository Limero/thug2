// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F808-0x8025F830 size=40B
// range 0x8025F808-0x8025F830 size=0x28 (40B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

void fn_8025FA60(void);
void fn_8025F988(void);
void fn_8025F830(void);

void fn_8025F808(void) {
    fn_8025FA60();
    fn_8025F988();
    fn_8025F830();
}
