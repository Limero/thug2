// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1A54-0x801C1A9C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8011A6A8(s32, s32);
extern char lbl_80302C34[];
void fn_801C1A54(Unk_31DE137E *arg0) {
    if ((s32) arg0->unk0x1C != 0) {
        fn_8011A6A8(*(s32 *)&lbl_80302C34, arg0->unk0x1C);
        arg0->unk0x1C = 0;
    }
}
