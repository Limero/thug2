// Dolphin db-module (OdemuExi2) - DBWrite
// mwcc GC/1.2.5n, cflags_odemuexi2.
// EXI ch2 bulk write entry: busy-wait status, bump SendCount, write payload
// via DBGWrite, mailbox-write the size header, busy-wait again.
// _DBGReadStatus/DBGWriteMailbox are INLINED here (DOL has them inline);
// DBGEXIImm is a separate DOL function (0x8028DC7C) -> extern reference.
#include "dolphin/types.h"
#include "dolphin/hw_regs.h"
#define IS_TRUE(x) ((x) != FALSE)
#define IS_FALSE(x) !IS_TRUE(x)
#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))

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
extern BOOL DBGWrite(u32 count, void* buffer, s32 param3);
extern u8 lbl_803CAA58;

inline static BOOL _DBGReadStatus(u32* p1) {
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

inline static BOOL DBGWriteMailbox(u32 p1) {
    u32 cmd = 0xc0000000;
    u32 v;
    u32 base = p1;
    BOOL total = FALSE;

    DBGEXISelect(4);
    v = (base & 0x1fffffff) | (cmd);
    total |= IS_FALSE(DBGEXIImm(&v, sizeof(v), 1));
    total |= IS_FALSE(DBGEXISync());
    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}

BOOL DBWrite(void* src, u32 size) {
    u32 v;
    u32 busyFlag;
    BOOL interrupts = OSDisableInterrupts();

    do {
        _DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    lbl_803CAA58++;
    v = ((lbl_803CAA58 & 1) ? 0x1000 : 0);

    while (!DBGWrite(v | 0x1c000, src, ROUND_UP(size, 4)))
        ;

    do {
        _DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    v = lbl_803CAA58;
    while (!DBGWriteMailbox((0x1f000000) | v << 0x10 | size))
        ;

    do {
        while (!_DBGReadStatus(&busyFlag))
            ;
    } while (busyFlag & 2);

    OSRestoreInterrupts(interrupts);

    return 0;
}
