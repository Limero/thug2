// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C938-0x8000C9CC (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void PADControlMotor(void *, void *);
void fn_8000C938(Unk_5031FAD7 *self) {
    s32 i;
    s32 flag;
    if (self->unk0xDC != 2)
        return;
    flag = 1;
    if (!(self->unk0xCC & 2))
        flag = 0;
    if (!flag)
        return;
    for (i = 0; i < self->unk0xD4; i++) {
        char *b1 = (char *)self + 0x60;
        char z = 0;
        char *b2 = (char *)self + 0xa0;
        b1[i] = z;
        b2[i] = z;
    }
    PADControlMotor(self->unk0x10,
                   (void *)((self->unk0x60 & QB_UNKNOWN_0xFFFF0000) ? 1 : 0));
}
