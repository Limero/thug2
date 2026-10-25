// Dolphin db-module (OdemuExi2) - DBGEXIImm
// mwcc GC/1.2.5n, cflags_odemuexi2.
// thug2 inlines DBGEXISync into DBGEXIImm (AGENTS.md #219): the
// while (__EXIRegs[13] & 1) spin follows the CSR write directly.
#include "dolphin/types.h"
#include "dolphin/hw_regs.h"
#define IS_TRUE(x) ((x) != FALSE)
#define IS_FALSE(x) !IS_TRUE(x)
#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))

BOOL DBGEXIImm(void* buffer, s32 bytecounter, u32 write) {
    u8* tempPointer;
    u32 writeOutValue;
    int i;

    if (write) {
        tempPointer = buffer;
        writeOutValue = 0;
        for (i = 0; i < bytecounter; i++) {
            u8* temp = ((u8*)buffer) + i;
            writeOutValue |= *temp << ((3 - i) << 3);
        }
        __EXIRegs[14] = writeOutValue;
    }

    __EXIRegs[13] = 1 | write << 2 | (bytecounter - 1) << 4;
    while (__EXIRegs[13] & 1)
        ;

    if (!write) {
        writeOutValue = __EXIRegs[14];
        tempPointer = buffer;
        for (i = 0; i < bytecounter; i++) {
            *tempPointer++ = writeOutValue >> ((3 - i) << 3);
        }
    }

    return TRUE;
}