// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036810-0x80036854 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { s32 key; char pad[0x1C]; } Rec36810;
s32 fn_80036810(Unk_C8FEE62D *arg0, s32 arg1) {
    register s32 n __asm__("r11");
    Rec36810 *p;
    s32 cnt = arg0->unk0x14;
    s32 i = 0;

    if (i < cnt) {
        p = (Rec36810 *)arg0->unk0x18;
        __asm__ volatile("mr %0, %1" : "=r"(n) : "r"(cnt));
        do {
            s32 v = p->key;
            p++;
            if (arg1 == v) {
                return i;
            }
            i += 1;
        } while (i < n);
    }
    return -1;
}
