// Dolphin db-module (OdemuExi2) - _DBGReadStatus
// mwcc GC/1.2.5n, cflags_odemuexi2.
// EXI ch2 status read (cmd 0x40000000, 2-byte write, 4-byte read).
// DBGEXIImm is a separate DOL function (0x8028DC7C) -> extern reference;
// DBGEXISelect/Deselect/Sync are inlined at each call site (AGENTS.md 219).
#include "dolphin/types.h"
#include "dolphin/hw_regs.h"
#define IS_TRUE(x) ((x) != FALSE)
#define IS_FALSE(x) !IS_TRUE(x)

inline static u32 DBGEXISelect(u32 v) {
    u32 regs = __EXIRegs[10];
    regs &= 0x405;
    regs |= 0x80 | (v << 4);
    __EXIRegs[10] = regs;
    return TRUE;
}

inline static BOOL DBGEXIDeselect(void) {
    __EXIRegs[10] &= 0x405;
    return TRUE;
}

inline static BOOL DBGEXISync(void) {
    while (__EXIRegs[13] & 1)
        ;
    return TRUE;
}

extern BOOL DBGEXIImm(void* buffer, s32 bytecounter, u32 write);

BOOL _DBGReadStatus(u32* p1) {
    BOOL total = FALSE;
    u32 v;

    DBGEXISelect(4);

    v = 1 << 30;
    total |= IS_FALSE(DBGEXIImm(&v, 2, 1));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIImm(p1, 4, 0));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}