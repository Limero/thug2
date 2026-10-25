// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021A8C8-0x8021A910 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Stores fn_800145AC() into lbl_803A3148 and forwards (lbl_80303148 + 8,
// arg0->unk0x100) to fn_8000A578 (uses register pins r29/r30).
// Suggested rename: UpdateStatusAndForward
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
extern s32 lbl_803A3148;
s32 fn_800145AC(void);
void fn_8000A578(s32 arg0, s32 arg1);
void fn_8021A8C8(void *arg0) {
    register s32 temp_r29 __asm__("r29");
    register void *a0 __asm__("r30");

    a0 = arg0;
    temp_r29 = lbl_80303148;
    lbl_803A3148 = fn_800145AC();
    fn_8000A578(temp_r29 + 8, ((Unk_6A70655D *)a0)->unk0x100);
}
