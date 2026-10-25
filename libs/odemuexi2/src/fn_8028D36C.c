// Dolphin db-module (OdemuExi2) - fn_8028D36C
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-09-27; wired as
// a lib object like its siblings (the ngccc game route cannot emit the
// 8x-unrolled mwcc loop). The source idiom that reproduces retail's
// floor-count main loop + n&7 tail (mwcc's own unroller output) is the
// natural align-to-boundary while-loop with the byte store written
// post-increment:  while (pos < 0x20) { *buffer->cursor++ = 0; pos++; }
// (a two-statement *c = 0; p->cursor = c + 1; form lowers differently).
#include "dolphin/types.h"
typedef struct { void *start; void *end; u8 *cursor; void *limit; } buf_t;
extern buf_t *lbl_803CAF18;

void fn_8028D36C(void) {
    u32 pos;

    pos = (u32)lbl_803CAF18->cursor & 0x1F;
    if (pos == 0) return;
    while (pos < 0x20) {
        *lbl_803CAF18->cursor++ = 0;
        pos++;
    }
}
