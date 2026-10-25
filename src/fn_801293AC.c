// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801293AC-0x801293FC (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012935C(void *);
s32 fn_801293AC(Unk_F8A5095F *arg0, s32 arg1) {
    if ((s32) ((Unk_ECD1B899 *)arg0)->unk0x2 == 3) {
        return fn_8012935C(arg0);
    }
    if ((s32) *((s32 *)&arg0->unk0x4) == 1) {
        return *((s32 *)&arg0->unk0x8);
    }
    return *((s32 *)((char *)*((s32 *)&arg0->unk0x8) + (arg1 * 4)));
}
