// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x80260110-0x80260168 size=88B
// range 0x80260110-0x80260168 size=0x58 (88B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

typedef struct OSContext {
    /* 0x000 */ u32 gpr[32];
    /* 0x080 */ u32 cr;
    /* 0x084 */ u32 lr;
    /* 0x088 */ u32 ctr;
    /* 0x08C */ u32 xer;
    /* 0x090 */ f64 fpr[32];
    /* 0x190 */ u32 fpscr_pad;
    /* 0x194 */ u32 fpscr;
    /* 0x198 */ u32 srr0;
    /* 0x19C */ u32 srr1;
    /* 0x1A0 */ u16 mode;
    /* 0x1A2 */ u16 state;
    /* 0x1A4 */ u16 excID;
    /* 0x1A8 */ u32 gqr[8];
    /* 0x1C8 */ u32 psf_pad;
    /* 0x1D0 */ f64 psf[32];
} OSContext; /* size 0x2D0 */

typedef void (*DbHook)(u32);

extern DbHook lbl_803CAB7C;
void OSClearContext(OSContext *context);
void OSSetCurrentContext(OSContext *context);
void OSLoadContext(OSContext *context);

void fn_80260110(OSContext *ctx) {
    OSContext local;

    OSClearContext(&local);
    OSSetCurrentContext(&local);
    lbl_803CAB7C(ctx->srr0);
    OSSetCurrentContext(ctx);
    OSLoadContext(ctx);
}
