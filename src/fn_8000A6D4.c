// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A6D4-0x8000A730 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern unsigned int lbl_802FFA3C[];
// Crc_GenerateCRCCaseSensitive @ 0x8000A6D4
unsigned int Crc_GenerateCRCCaseSensitive(const unsigned char *data, int len) {
    unsigned int crc;
    int i;
    if (!data || len <= 0)
        return 0;
    crc = QB_UINT32_MAX;
    for (i = 0; i < len; i++) {
        unsigned int b = (unsigned char)data[i];
        unsigned int lo = (unsigned char)crc;
        crc = lbl_802FFA3C[lo ^ b] ^ (crc >> 8);
    }
    return crc;
}