// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130344-0x801303B4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

u8 *fn_8012B2A0(u8 *);
void fn_80130344(void *arg0);

void fn_80130344(void *arg0) {
    while (*(u8 *)*(u8 **)((char *)arg0 + 0x10) != 0x3D) {
        if (*(u8 *)*(u8 **)((char *)arg0 + 0x10) == 0x3C) {
            *(u8 **)((char *)arg0 + 0x10) = *(u8 **)((char *)arg0 + 0x10) + 1;
            fn_80130344(arg0);
        } else {
            *(u8 **)((char *)arg0 + 0x10) = fn_8012B2A0(*(u8 **)((char *)arg0 + 0x10));
        }
    }
    *(u8 **)((char *)arg0 + 0x10) = *(u8 **)((char *)arg0 + 0x10) + 1;
}
