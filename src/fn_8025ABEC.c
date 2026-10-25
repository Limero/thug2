// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025ABEC-0x8025AC04 (24B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
// The want builds 0xCC006000 (EXI/MMIO) into r3 with a lis of -0x3400
// followed by an ori of 0x6000, loads the status word from 0(r3) into r4,
// applies a record-form andi of 0x14 to r4, then loads immediate 0 into r4
// and returns. The masked value is a dead result (it survives only via an
// asm-consumed phase), the zeroing is a second asm-consumed phase, and r3
// still holds the address at the return.
void fn_8025ABEC(void) {
    register s32 hwi __asm__("r3");
    register u32 t __asm__("r4");
    hwi = (s32)QB_UNKNOWN_0xCC006000;
    t = *(u32 *)hwi & 0x14;
    __asm__ volatile("" :: "r"(t));
    t = 0;
    __asm__ volatile("" :: "r"(t));
}
