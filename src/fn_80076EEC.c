// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80076EEC-0x80076F8C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
s32 fn_80076778(Unk_5D1D68CC *);
void fn_80010D94(s32, s32);
void fn_80010E78(s32);
void *Mem_Alloc(s32);
s32 fn_800768A8(Unk_78674569 *, Unk_9994C3F5 *, s32, s32, s32);
void *memcpy(void *, void *, u32);
void DCFlushRange(void *, u32);

s32 fn_80076EEC(Unk_5D1D68CC *self, Unk_9994C3F5 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 size;
    Unk_78674569 *copy;

    size = fn_80076778(self);
    fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
    /* Zero-code barrier: the allocation must follow the debug print, which
       the scheduler otherwise hoists above it. */
    __asm__ volatile("" ::: "memory");
    copy = (Unk_78674569 *)Mem_Alloc(size);
    fn_80010E78(lbl_802FFE98->unk0x11C);
    memcpy(copy, self, (u32)size);
    DCFlushRange(copy, (u32)size);
    return fn_800768A8(copy, arg1, arg2, arg3, arg4);
}
