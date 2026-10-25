// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054EE8-0x80054F08 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void *fn_80054EE8(void) {
    register CStruct *p __asm__("r11");

    p = *(CStruct **)&lbl_80364C28;
    if (p->unk0x4 != -1) {
        return p;
    }
    return 0;
}
