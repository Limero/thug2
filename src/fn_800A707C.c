// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A707C-0x800A7138 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800A707C(void *arg0, s32 *arg1) {
    void *head;
    s32 limit;
    s32 ok;
    s32 c;
    void *entry;
    void *next;
    void *h;

    head = *(void **)((char *)arg0 + 0x10);
    limit = 1 << *(s32 *)((char *)arg0 + 0);
    if (head == NULL) {
        if (*(s32 *)((char *)arg0 + 0xC) >= 0) {
            ok = 0;
            goto join;
        }
    } else {
        *(void **)((char *)arg0 + 0x10) = *(void **)((char *)head + 8);
    }
    if (*(void **)((char *)arg0 + 0x10) != NULL) {
        ok = 1;
    } else {
        for (;;) {
            c = *(s32 *)((char *)arg0 + 0xC) + 1;
            *(s32 *)((char *)arg0 + 0xC) = c;
            if (c >= limit) {
                ok = 0;
                break;
            }
            entry = (char *)*(void **)((char *)arg0 + 4) + c * 0xC;
            *(void **)((char *)arg0 + 0x10) = entry;
            if (*(s32 *)((char *)entry + 4) != 0) {
                ok = 1;
                break;
            }
            next = *(void **)((char *)entry + 8);
            if (next == NULL) {
                continue;
            }
            *(void **)((char *)arg0 + 0x10) = next;
            ok = 1;
            break;
        }
    }
join:
    if (ok == 0) {
        return 0;
    }
    h = *(void **)((char *)arg0 + 0x10);
    if (h == NULL) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = *(s32 *)h;
    }
    return *(s32 *)((char *)*(void **)((char *)arg0 + 0x10) + 4);
}
