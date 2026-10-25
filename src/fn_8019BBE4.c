// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019BBE4-0x8019BC64 (128B). Byte-identical.
#include "types.h"
void strcpy(char *, char *);
u32 strlen(char *);
extern void fn_80009218(void *arg0, s32 arg1);
struct fn_8019BBE4_L { char _pad[0x410]; u32 arr[16]; };
s32 fn_8019BBE4(s32 arg0, s32 arg1, s32 arg2) {
    char sp8[0x100];
    struct fn_8019BBE4_L *lo;
    s32 ret;
    u32 i;
    ret = arg0;
    lo = (struct fn_8019BBE4_L *)arg1;
    strcpy(sp8, (char *)(arg1 + 0x10));
    for (i = 0; i < strlen(sp8); i++) {
        if (i >= lo->arr[arg2]) {
            sp8[i] = '-';
        }
    }
    fn_80009218(ret, sp8);
    return ret;
}
