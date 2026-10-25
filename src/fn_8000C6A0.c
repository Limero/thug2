// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C6A0-0x8000C73C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void PADControlMotor(s32 chan, s32 cmd);
void fn_8000C6A0(Unk_E93B8C39 *self) {
    s32 i, flag;
    char *base;
    if (self->unk0xC8 == 0) {
        if (self->unk0xDC == 2) {
            flag = 1;
            if (!(self->unk0xCC & 2))
                flag = 0;
            if (flag) {
                for (i = 0; i < self->unk0xD4; i++) {
                    char *b = (char *)self + 0x60;
                    b[i] = 0;
                }
                PADControlMotor(self->unk0x10, 0);
            }
        }
        self->unk0xC8 = 1;
    }
}