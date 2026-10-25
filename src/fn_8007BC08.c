// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BC08-0x8007BC64 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
typedef struct {
    char pad0x0[0x4C];
    void *unk0x4C;
} Rec_8007BC08;
extern void *lbl_80300474;
void *fn_8007B9DC(void);
void fn_8007BC08(u32 arg0) {
    u32 i;
    Rec_8007BC08 *p;
    for (i = 0; i < arg0; i++) {
        Mem_Alloc2(0x58);
        p = fn_8007B9DC();
        p->unk0x4C = lbl_80300474;
        lbl_80300474 = p;
    }
}
