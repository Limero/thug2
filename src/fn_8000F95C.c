// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F95C-0x8000F9C4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void *Mem_NewZero(int);
extern void *fn_80011CA4(void *, void *, void *, void *);
void *fn_8000F95C(Unk_FFAD6788 *self, void *a, void *b, void *c) {
    void *obj;
    void **arr;
    s32 count;
    obj = fn_80011CA4(Mem_NewZero(0xb8), a, b, c);
    arr = (void **)((char *)self + 4);
    count = self->unk0xC4;
    arr[count] = obj;
    count++;
    self->unk0xC4 = count;
    return obj;
}
