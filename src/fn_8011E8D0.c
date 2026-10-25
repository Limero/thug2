// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011E8D0-0x8011E930 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038EBB8[];
extern void AXFreeVoice(s32 arg0);
void fn_8011E8D0(void) {
    char *base;
    s32 off;
    s32 i;
    Unk_C3AC2043 *v;
    u16 f;

    off = 0;
    base = lbl_8038EBB8;
    i = 0x3B;
    do {
        v = *(s32 *)(off + (s32)base);
        if (v != 0) {
            f = v->unk0x146;
            if (f == 0) {
                AXFreeVoice(v);
                *(s32 *)(off + (s32)base) = f;
            }
        }
        off += 8;
    } while (--i != 0);
}
