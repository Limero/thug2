// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801906C4-0x801906D4 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
/* local view: the goal-flag word at +0x70, bit 6 is a 1-bit field */
typedef struct {
    char _pad[0x70];
    u32 unk70_0_5 : 6;
    u32 unk70_6 : 1;
    u32 unk70_7_31 : 25;
} Goal_801906C4;
void fn_801906C4(Unk_C7387A53 *self, s32 arg) {
    ((Goal_801906C4 *)self)->unk70_6 = arg;
}
