// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000D0A4-0x8000D100 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void *fn_8000EAF4(void *, s32);
extern char lbl_802FFE84[];
char *fn_8000D0A4(Unk_7FDC0DE0 *self) {
    void *m = Mem_Alloc2(0x18);
    self->unk0x14 = (s32)fn_8000EAF4(m, 4);
    *(char **)lbl_802FFE84 = self;
    self->unk0x8 = 0;
    self->unk0xC = 0;
    self->unk0x10 = 0;
    self->unk0x23C = 0;
    return self;
}