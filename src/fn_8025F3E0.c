// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F3E0-0x8025F4AC size=204B
// range 0x8025F3E0-0x8025F4AC size=0xCC (204B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern s32 lbl_803CAB80;
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);
void *OSGetArenaLo(void);
void fn_8025F764(s32 arg0);
void fn_8025F7A8(void);
void fn_8025F7D8(void);
void fn_8025F76C(void);
void fn_8025FCAC(void);
void fn_8025FC10(void);
void fn_8025FBB8(void);

void fn_8025F3E0(s32 arg0) {
    s32 level;
    u32 free;

    if (lbl_803CAB80 != 0) {
        return;
    }

    level = OSDisableInterrupts();
    lbl_803CAB80 = 1;
    fn_8025F764(arg0);

    free = 0x10000 - ((u32)OSGetArenaLo() & 0xFFFF);
    if (free >= 0x5000) {
        fn_8025F7A8();
        fn_8025F7D8();
        fn_8025F76C();
    } else if (free >= 0x4000) {
        fn_8025F7D8();
        fn_8025F76C();
        fn_8025F7A8();
    } else if (free >= 0x1000) {
        fn_8025F7A8();
        fn_8025F76C();
        fn_8025F7D8();
    } else {
        fn_8025F76C();
        fn_8025F7A8();
        fn_8025F7D8();
    }

    fn_8025FCAC();
    fn_8025FC10();
    fn_8025FBB8();

    OSRestoreInterrupts(level);
}
