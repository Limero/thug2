// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019BB98-0x8019BBE4 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
char *strcpy(char *, const char *);
s32 fn_800093A4(s32);
void fn_800092B0(s32, s32);
void fn_8019BB98(s32 arg0, Unk_9994C3F5 *arg1) {
    strcpy(arg0 + 0x10, fn_800093A4(arg1));
    fn_800092B0(arg1, 2);
}