// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006C498-0x8006C584 (236B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_80301428;
extern void *lbl_8030142C;
extern void *lbl_80301430;
extern void *lbl_80301434;
extern void *lbl_80301438;
extern char lbl_80366DDC[];
void *Mem_Alloc2(s32 size);
void *fn_8006EC98(void *self, s32 n);
void *fn_8006ED58(void *self, s32 n);
void *fn_8006EE18(void *self, s32 n);
void *fn_8006EED8(void *self, s32 n);
void *fn_8006EF98(void *self, s32 n);
void fn_8008345C(void);
void fn_8008569C(void);
void fn_8006BC44(void *self);
void fn_8006C498(void) {
    if (lbl_80301428 == 0) {
        lbl_80301428 = fn_8006EC98(Mem_Alloc2(0x18), 4);
    }
    if (lbl_8030142C == 0) {
        lbl_8030142C = fn_8006ED58(Mem_Alloc2(0x18), 4);
    }
    if (lbl_80301430 == 0) {
        lbl_80301430 = fn_8006EE18(Mem_Alloc2(0x18), 4);
    }
    if (lbl_80301434 == 0) {
        lbl_80301434 = fn_8006EED8(Mem_Alloc2(0x18), 4);
    }
    if (lbl_80301438 == 0) {
        lbl_80301438 = fn_8006EF98(Mem_Alloc2(0x18), 4);
    }
    fn_8008345C();
    fn_8008569C();
    fn_8006BC44(lbl_80366DDC);
}
