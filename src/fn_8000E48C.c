// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E48C-0x8000E508 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void *fn_8000E45C(void *);
char *fn_8000E48C(Unk_41EA2015 *self, s32 bits) {
    s32 count, left;
    char *alloc, *p;
    count = 1 << bits;
    self->unk0x0 = bits;
    alloc = Mem_Alloc(count * 12);
    p = alloc;
    left = count - 1;
    if (count != 0) {
        do {
            fn_8000E45C(p);
            p += 12;
        } while (--left != -1);
    }
    ((Unk_E266FB50_2 *)self)->unk0x4 = alloc;
    ((Unk_59AB5482_2 *)self)->unk0x8 = 0;
    self->unk0x14 = 0;
    return self;
}