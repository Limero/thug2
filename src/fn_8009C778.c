// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C778-0x8009C7F4 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void GX_SetZMode(s32, s32, s32);
void fn_8009C778(s32 arg0, u32 arg1) {
    s32 v;
    v = 0;
    switch (arg0) {
    case 1:
        switch (arg1) {
        case 1: v = 0; break;
        case 2: v = 7; break;
        case 3: v = 2; break;
        case 4: v = 4; break;
        }
        GX_SetZMode(1, v, 1);
        break;
    case 2: v = 0; break;
    case 3: v = 0; break;
    }
}
