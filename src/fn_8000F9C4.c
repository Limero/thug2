// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F9C4-0x8000FA54 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
void fn_8000F9C4(Unk_FFAD6788 *self, Unk_C7387A53 *x) {
    s32 i;
    s32 k;
    for (i = 0, k = 0; i < self->unk0xC4; i++, k += 4) {
        char *arr = (char *)self + 4;
        if (*(void **)(arr + k) == x) {
            self->unk0xC4 = self->unk0xC4 - 1;
            *(void **)(arr + k) = *(void **)(arr + 4 * (self->unk0xC4));
            break;
        }
    }
    if (x) {
        void *v = *((void * *)&x->unk0x80);
        void (*fp)(void *, s32) = *(void (**)(void *, s32))((char *)v + 0x1c);
        fp((char *)x + ((Unk_2BAD2BE8 *)v)->unk0x18, 3);
    }
}
