// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243B70-0x80243C18 (168B). Byte-identical.
#include "types.h"
extern char lbl_802B12BC[];
extern char lbl_802B12C8[];
void fn_80125A6C(void *, s32);
s32 Script_GenerateCRC(s32);

s32 fn_80243B70(s32 arg0, s32 arg1) {
    s32 sp8[12];
    s32 i;

    arg0 += 0x84;
    for (i = 0; i <= 0x1F; i++) {
        s32 entry = *(s32 *)((char *)arg0 - 0x80);
        if (entry != 0) {
            s32 flag = *(s32 *)arg0;
            s32 b;
            s32 *sel = (s32 *)(entry + 0xC);
            __asm__("" : "=r"(b) : "r"(flag == 0));
            if (sel[b] == arg1) {
                if (i & 1) {
                    fn_80125A6C((s32)lbl_802B12BC, 0);
                }
                sprintf(sp8, (s32)lbl_802B12C8, i);
                return Script_GenerateCRC(sp8);
            }
        }
        arg0 += 4;
    }
    return 0;
}
