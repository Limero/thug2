// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A730-0x8000A778 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern unsigned int lbl_802FFA3C[];
unsigned int fn_8000A730(const unsigned char *data, int len, unsigned int crc) {
    int i;
    for (i = 0; i < len; i++) {
        unsigned int b = (unsigned char)data[i];
        unsigned int lo = (unsigned char)crc;
        crc = lbl_802FFA3C[lo ^ b] ^ (crc >> 8);
    }
    return crc;
}
