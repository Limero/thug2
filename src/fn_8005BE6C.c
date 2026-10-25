// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BE6C-0x8005BEEC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
u32 strlen(const char *);
unsigned int fn_8000A778(const char *);
void fn_8005BE6C(char *arg0) {
    s32 len;
    char c;
    len = strlen(arg0);
    if (len > 0) {
        if (arg0[len - 1] != '\\' && arg0[len - 1] != '/') {
            while (--len > 0) {
                c = arg0[len - 1];
                if (c == '\\' || c == '/') {
                    break;
                }
            }
        }
    }
    fn_8000A778(arg0 + len);
}
