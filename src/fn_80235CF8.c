// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80235CF8-0x80235D1C (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Validates a 16-bit tag (0x4E24) at arg0+0x13C9A; returns the pointer
// arg0+0x13CB0 when valid, else NULL (arg0+0x10000 base form).
// Suggested rename: fn_80235CF8_validate_tagged_ptr.
#include "types.h"
void *fn_80235CF8(void *arg0) {
    char *v = (char *)arg0 + 0x10000;
    if (v != (char *)-0x3C94) {
        if (*(u16 *)(v + 0x3C9A) == 0x4E24) {
            return v + 0x3CB0;
        }
    }
    return NULL;
}