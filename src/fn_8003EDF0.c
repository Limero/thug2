// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003EDF0-0x8003EE50 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u32 w[14];
} S38;

void *fn_8003EDF0(void *arg0, char *arg1) {
    *(S38 *)arg0 = *(S38 *)(arg1 + 8);
    return arg0;
}
