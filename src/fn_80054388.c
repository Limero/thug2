// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054388-0x80054420 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80293010[];
extern char lbl_80293014[];
extern char lbl_80293018[];
extern char lbl_80293024[];
extern char *strstr(const char *, const char *);
extern int sprintf(char *, const char *, ...);
void fn_80054388(char *arg0, char *arg1, char *arg2) {
    char *needle = lbl_80293010;
    __asm__("" : "+r"(arg1));
    do {
        if (strstr(arg0, needle) == 0) {
            if (strstr(arg0, lbl_80293014) == 0) {
                break;
            }
        }
        sprintf(arg2, lbl_80293018, arg0);
        return;
    } while (0);
    sprintf(arg2, lbl_80293024, arg0, arg0, arg1);
}
