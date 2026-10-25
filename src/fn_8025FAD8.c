// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025FAD8-0x8025FB84 size=172B
// range 0x8025FAD8-0x8025FB84 size=0xAC (172B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

typedef struct FAD8Entry {
    /* 0x00 */ u32 a;
    /* 0x04 */ u32 b;
} FAD8Entry;

extern u8 *lbl_803CAB70;
extern u32 fn_8025FB9C(u32 arg0);
extern void fn_8025FBB8(void);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern void DCStoreRangeNoSync(void *addr, u32 len);
extern void PPCSync(void);

void fn_8025FAD8(u32 (*cb)(u32)) {
    u32 off;
    u32 i;
    s32 level;
    FAD8Entry *e;

    level = OSDisableInterrupts();
    for (i = 0, off = 0; i < 0x2000; i++, off += 8) {
        e = (FAD8Entry *)(lbl_803CAB70 + off);
        if ((e->a & 0x80000000) != 0 && (e->b & 0x80) != 0) {
            cb(fn_8025FB9C((u32)e));
            e->b &= ~0x80;
            DCStoreRangeNoSync(&e->b, 4);
        }
    }
    PPCSync();
    fn_8025FBB8();
    OSRestoreInterrupts(level);
}
