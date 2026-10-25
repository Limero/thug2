// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A95D4-0x800A95EC (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
// Paired-single pair copy: copies arg0[8..9] (16 bytes at +0x40/+0x48)
// to arg1[0..1], via an arg0 += 4 walk (addi + psq_l/psq_st pair).
// Suggested rename: fn_800A95D4_copy_ps_pair.
#include "types.h"
#include "structs.h"
void fn_800A95D4(__ps_t *arg0, __ps_t *arg1) {
    arg0 += 4;
    arg1[0] = arg0[4];
    arg1[1] = arg0[5];
}