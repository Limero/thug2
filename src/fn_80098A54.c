// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80098A54-0x80098AB4 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8037B5E8[];
typedef struct RecA98A54 { s32 unk0x0; u16 unk0x4; u16 unk0x6; s32 unk0x8; } RecA98A54;
void fn_80098A54(Unk_1C4D340C *arg0) {
    s32 i;
    u16 flags;
    RecA98A54 **p;
    RecA98A54 **q;
    RecA98A54 *rec;
    char *tbl;
    i = 0;
    p = (RecA98A54 **)arg0->unk0x58;
    if (i < arg0->unk0x5E) {
        q = p;
        tbl = lbl_8037B5E8;
        do {
            rec = *q++;
            flags = rec->unk0x4;
            if ((flags & 2) && (rec->unk0x8 & *(s32 *)(tbl + 0x1C4))) {
                rec->unk0x4 = flags | 8;
            }
            i++;
        } while (i < arg0->unk0x5E);
    }
}
