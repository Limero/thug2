// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125354-0x80125388 (52B). Byte-identical.
#include "types.h"
typedef struct { u32 x:9; u32 b:7; u32 y:16; } BitF;
void fn_80125354(BitF *arg0) {
    switch (arg0->b) {
    case 20:
        arg0->b = 0xA;
        return;
    case 21:
        arg0->b = 0xC;
        return;
    }
}
