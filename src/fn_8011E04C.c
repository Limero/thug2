// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E04C-0x8011E078 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038C8C0[];
void fn_8011E04C(void *arg0, void *arg1) {
    Unk_76B26A14 *base = lbl_8038C8C0;
    __asm__("" : "+r"(base));
    *(u64 *)arg0 = base->unk0xC88;
    *(u64 *)arg1 = base->unk0xC90;
}
