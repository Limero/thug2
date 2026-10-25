// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800597DC-0x8005985C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
extern char lbl_80300498[];
extern s32 lbl_80300898;
void fn_800597DC(void) {
    s32 i;
    s32 v;
    i = 0;
    while (i < lbl_80300898) {
        char *o = (char *)(i * 4);
        v = *(s32 *)((char *)o + (s32)lbl_80300498);
        if (v != 0) {
            Mem_Free(v);
            *(s32 *)((char *)o + (s32)lbl_80300498) = 0;
        }
        i += 1;
    }
    lbl_80300898 = 0;
}