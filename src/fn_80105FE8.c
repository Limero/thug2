// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80105FE8-0x80106078 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { s32 value; s32 key; } ListEntry;
void fn_80105FE8(void *arg0, s32 arg1) {
    Unk_5CB48605 *self = (Unk_5CB48605 *)arg0;
    s32 i;
    for (i = 0; i < self->unk0xFC4; i++) {
        s32 *p = (s32 *)((char *)arg0 + 0x20 + i * 8);
        if (*p == arg1) {
            s32 j = i + 1;
            s32 c1;
            s32 c2;
            if (j < self->unk0xFC0) {
                char *dst = (char *)(j * 8 + (s32)arg0);
                do {
                    ListEntry *row = (ListEntry *)(dst + 0x18);
                    row[0] = row[1];
                    dst += 8;
                    j++;
                } while (j < self->unk0xFC0);
            }
            c1 = self->unk0xFC4;
            c2 = self->unk0xFC0;
            self->unk0xFC4 = c1 - 1;
            self->unk0xFC0 = c2 - 1;
            return;
        }
    }
}
