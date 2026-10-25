// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80132104-0x80132140 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80132104(Unk_ECDFFADA *arg0) {
    s32 c = arg0->unk0x38;
    s32 off;
    arg0->unk0xE8 = 0;
    if (0 == c--) return;
    off = c * 0x2C;
    do {
        *(s32 *)((char *)off + (s32)arg0->unk0x94 + 0x14) = 0;
        off = off - 0x2C;
    } while (0 != c--);
}
