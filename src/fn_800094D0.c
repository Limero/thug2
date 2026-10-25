// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800094D0-0x800095B8 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#define LowerCh(c) (((c) >= 'A' && (c) <= 'Z') ? ((c) + 'a' - 'A') : (c))
// StrStr @ 0x800094D0
void *StrStr(char *hay, char *ndl) {
    register char lead;
    char cur;
    char *ah;
    char *an;
    char x;
    char y;
    lead = *ndl++;
    if (!lead) {
        return 0;
    }
    lead = LowerCh(lead);
    while (1) {
        while (1) {
            cur = *hay++;
            cur = LowerCh(cur);
            if (cur == lead) {
                break;
            }
            if (!cur) {
                return 0;
            }
        }
        ah = hay;
        an = ndl;
        while (1) {
            x = *an++;
            if (!x) {
                return hay - 1;
            }
            y = *ah++;
            if (LowerCh(x) != LowerCh(y)) {
                break;
            }
        }
    }
}
