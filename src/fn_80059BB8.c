// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059BB8-0x80059C18 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 *lbl_80300498[];
extern s32 lbl_80300898;
s32 fn_80059BB8(s32 arg0) {
    s32 i;
    s32 n;
    s32 off;
    s32 *base;
    s32 *slot;
    s32 node;
    i = 0;
    n = lbl_80300898;
    if (i < n) {
        base = lbl_80300498;
        off = 0;
        slot = base;
        do {
            node = *(s32 *)((char *)off + (s32)base);
            if (node != 0) {
                if (((Unk_C7387A53 *)node)->unk0x2C == arg0) {
                    return (s32)slot;
                }
            }
            i += 1;
            slot += 1;
            off += 4;
        } while (i < lbl_80300898);
    }
    return 0;
}
