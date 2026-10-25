// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125320-0x80125354 (52B). Byte-identical.
#include "types.h"
typedef struct { u32 x:9; u32 b:7; u32 y:16; } BitF;
void fn_80125320(BitF *arg0) {
    switch (arg0->b) {
    case 10:
        arg0->b = 0x14;
        return;
    case 12:
        arg0->b = 0x15;
        return;
    }
}
