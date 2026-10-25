// Dolphin db-module (OdemuExi2) - DBQueryData
// mwcc GC/1.2.5n, cflags_odemuexi2.
// Returns RecvDataLeng; if 0, checks the mailbox with interrupts disabled.
// _DBGReadStatus/DBGReadMailbox are separate DOL functions (0x8028D96C/
// 0x8028DBD0) -> extern references; CheckMailBox is inlined.
#include "dolphin/types.h"
extern s32 lbl_803CAF2C;
extern u32 lbl_803CAF28;
extern u8 lbl_803CAF34;
extern BOOL _DBGReadStatus(u32* p1);
extern BOOL DBGReadMailbox(u32* p1);

u32 DBQueryData(void) {
    u32 v;
    BOOL interrupts;

    lbl_803CAF34 = 0;
    if (!lbl_803CAF2C) {
        interrupts = OSDisableInterrupts();
        _DBGReadStatus(&v);
        if (v & 1) {
            DBGReadMailbox(&v);
            v &= 0x1fffffff;
            if ((v & 0x1f000000) == 0x1f000000) {
                lbl_803CAF28 = v;
                lbl_803CAF2C = v & 0x7fff;
                lbl_803CAF34 = 1;
            }
        }
        OSRestoreInterrupts(interrupts);
    }
    return lbl_803CAF2C;
}