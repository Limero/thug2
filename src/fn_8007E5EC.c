// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E5EC-0x8007E6D4 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* 12-byte stream record. +4 is the composite sort key (see header). */
typedef struct {
    s32 f0;
    s32 fKey;
    s32 f8;
} Rec12;

s32 Mem_Alloc(s32);
s32 fn_8007E4B0(void *, void *);
void fn_8026A07C(void *base, s32 nmemb, s32 size, s32 (*cmp)(void *, void *));

s32 fn_8007E5EC(Unk_FFAD6788 *self, void **cursor_pp) {
    s32 count;
    Rec12 *src;
    void *dst_base;
    s32 dst_off;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    Rec12 *dst;
    s32 res;
    s32 hdr;

    src = (Rec12 *)*cursor_pp;
    hdr = *(s32 *)src;
    src = (Rec12 *)((char *)src + 4);
    if (hdr > 1U) {
        self->unk0xB0 = *(s32 *)src;
        src = (Rec12 *)((char *)src + 4);
    }
    count = *(s32 *)src;
    src = (Rec12 *)((char *)src + 4);
    self->unk0xC4 = count;
    if (count != 0) {
        self->unk0xC0 = Mem_Alloc(count * 0xC);
        i = 0;
        if (i < (u32) self->unk0xC4) {
            dst_off = 0;
            do {
                dst_base = (void *)self->unk0xC0;
                i += 1;
                a = src->f0;
                c = src->fKey;
                dst = (Rec12 *)((char *)dst_off + (s32)dst_base);
                b = src->f8;
                dst->f0 = a;
                src = (Rec12 *)((char *)src + 0xC);
                dst->fKey = c;
                dst_off += 0xC;
                dst->f8 = b;
            } while (i < (u32) self->unk0xC4);
        }
        fn_8026A07C((void *)self->unk0xC0, self->unk0xC4, 0xC, fn_8007E4B0);
    }
    *cursor_pp = (void *)src;
    res = 1;
    if ((s32) self->unk0xC4 == 0) {
        res = 0;
    }
    return res;
}
