// Dolphin db-module (OdemuExi2) - DBGFlushBuffer
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-08-26; wired as
// lib objects (the ngccc game route cannot emit the SDK prologue order).
#include "dolphin/types.h"
typedef struct { void *start; void *end; } range_t;
extern range_t *lbl_803CAF18;
extern void DCFlushRange(void *addr, u32 nBytes);
void DBGFlushBuffer(void) {
    range_t *p = lbl_803CAF18;
    DCFlushRange(p->start, (u32)p->end);
}
