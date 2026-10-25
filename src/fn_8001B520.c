// Promoted from src/wip (m2c draft hand-refined to exact match).
// range 0x8001B520-0x8001B56C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80290E50[];
void fn_8000B680(void);
void fn_8001B520(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_80290E50;
    fn_8000B680();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
