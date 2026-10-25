// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F234-0x8025F26C size=56B
// range 0x8025F234-0x8025F26C size=0x38 (56B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern char lbl_80308C98[];
int sprintf(char *str, const char *format, ...);
void PPCHalt(void);

void fn_8025F234(u32 addr) {
    char buf[0x408];

    sprintf(buf, (char *)(s32)lbl_80308C98, addr);
    PPCHalt();
}
