// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077FEC-0x80078094 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct S77FEC_desc {
    char unk0x0[9];
    u8 unk0x9;
} S77FEC_desc;
typedef struct S77FEC {
    char unk0x0[0xC];
    S77FEC_desc *unk0xC;
} S77FEC;
s32 fn_80077FEC(S77FEC *arg0) {
    s32 t = arg0->unk0xC->unk0x9;
    switch (t) {
    case 0: case 2: case 14: return 4;
    case 1: case 3: case 17: case 39: return 8;
    case 4: case 5: case 19: return 0x10;
    case 6: case 22: break;
    default: break;
    }
    return 0x20;
}
