// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000DEBC-0x8000DFA0 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE84[];
extern s32 lbl_802FFE88;
s32 fn_8000D150(void *, void *);
s32 fn_8000CFB0(s32, s32);
s32 fn_8000CF10(s32);
s32 fn_8000CFC8(s32, s32);
s32 fn_8000DEBC(void *arg0, u8 *arg1, s32 arg2) {
    s32 temp_r3;
    s32 flag;
    u8 *p;
    u8 c;

    temp_r3 = fn_8000D150(*(void **)&lbl_802FFE84, arg0);
    if (temp_r3 != 0) {
        fn_8000CFB0(*(s32 *)(*(s32 *)&lbl_802FFE84 + 4), arg2);
        p = arg1;
        flag = 0;
        c = *p;
        if (c != 0) {
            do {
                if ((s8) c != 'r' && (s8) c != 'b') {
                    flag = 1;
                }
                c = *++p;
            } while (c != 0);
        }
        if (flag == 0) {
            fn_8000CF10(*(s32 *)(*(s32 *)&lbl_802FFE84 + 4));
            lbl_802FFE88 = 1;
            return temp_r3;
        }
        fn_8000CFC8(*(s32 *)(*(s32 *)&lbl_802FFE84 + 4), arg2);
    }
    lbl_802FFE88 = 0;
    return 0;
}
