// Dolphin db-module (OdemuExi2) - DBGWrite
// mwcc GC/1.2.5n, cflags_odemuexi2.
// EXI ch2 bulk write: cmd 0xA0000000|count<<8, then 4-byte writes until
// param3 exhausted (clamped at 0).
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

BOOL DBGWrite(u32 count, void* buffer, s32 param3) {
    BOOL total = FALSE;
    u32* buf_p = (u32*)buffer;
    u32 v1;
    u32 v;

    DBGEXISelect(4);

    v1 = (count & 0x1fffc) << 8 | 0xa0000000;
    total |= IS_FALSE(DBGEXIImm(&v1, sizeof(v1), 1));
    total |= IS_FALSE(DBGEXISync());

    while (param3 != 0) {
        v = *buf_p++;

        total |= IS_FALSE(DBGEXIImm(&v, sizeof(v), 1));
        total |= IS_FALSE(DBGEXISync());

        param3 -= 4;
        if (param3 < 0) {
            param3 = 0;
        }
    }

    total |= IS_FALSE(DBGEXIDeselect());
    return IS_FALSE(total);
}
