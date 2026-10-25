// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014248-0x8001428C (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: increments two u64 counters at 0x802FFF38 / 0x802FFF40
// (addic/addze idiom). m2c had emulated the 64-bit adds via a static
// M2C_CARRY global; the real source is volatile u64 label accesses — the
// volatile forces sequential per-counter codegen, the labels give lis+addi.
#include "types.h"
extern volatile u64 lbl_802FFF38;
extern volatile u64 lbl_802FFF40;

// Tmr_IncrementVblankCounters @ 0x80014248
void Tmr_IncrementVblankCounters(void) {
    lbl_802FFF38 += 1;
    lbl_802FFF40 += 1;
}
