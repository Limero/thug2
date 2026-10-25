// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800126DC-0x80012754 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8031349C[];
s32 strcasecmp(const char *, const char *);
void Mem_Free_3(s32);
s32 fn_800126DC(char *arg0) {
    char *base = lbl_8031349C;
    s32 found = 0;
    s32 off = 0;
    s32 count = 0x64;
    do {
        if (*(s32 *)((char *)(off + (s32)base)) != 0) {
            s32 r = strcasecmp((const char *)*(s32 *)((char *)(off + (s32)base)), arg0);
            if (r == 0) {
                found = 1;
                Mem_Free_3(*(s32 *)((char *)(off + (s32)base)));
                *(s32 *)((char *)(off + (s32)base)) = r;
            }
        }
        off += 4;
        count -= 1;
    } while (count != 0);
    return found;
}
