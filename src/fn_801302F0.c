// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801302F0-0x80130344 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x10];
    u8 *unk0x10;
} Rec_801302F0;
void fn_8012CB60(void *, ...);
void fn_801302F0(Rec_801302F0 *arg0) {
    u16 sp8;
    u8 *inc = arg0->unk0x10 + 1;
    arg0->unk0x10 = inc;
    fn_8012CB60(&sp8, inc);
    arg0->unk0x10 = arg0->unk0x10 + sp8;
}
