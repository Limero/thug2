// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9CE8-0x800A9E0C (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029828C[];
void fn_800F0FB8(s32);
void *fn_800F0FE4(void);
s32 fn_800F0AFC(void *);
s32 fn_800A9C70(void *);
s32 fn_80128610(void *, char *, void **, s32);
s32 GetChecksum(void *, s32);
void fn_800F100C(void);

s32 fn_800A9CE8(s32 arg0, s32 arg1, s32 arg2) {
    s32 count;
    void *cur;
    s32 off;
    s32 i;
    void *volatile sp8;

    fn_800F0FB8(arg2);
    count = 0;
    if (arg2 != 0) {
        fn_800F0FE4();
    }
    cur = fn_800F0FE4();
    while (cur != 0) {
        off = 0;
        do {
            s32 cs = fn_800F0AFC(cur);
            if (fn_800A9C70(cur) != 0) {
                if (arg0 == 0) {
                    *(s32 *)((char *)(off + (s32)arg1)) = cs;
                    off += 4;
                    count++;
                } else if (fn_80128610(cur, lbl_8029828C, &sp8, 0) != 0) {
                    for (i = 0; i < ((CStruct *)sp8)->unk0x4; i++) {
                        if (GetChecksum(sp8, i) == arg0) {
                            *(s32 *)((char *)arg1 + count * 4) = cs;
                            off += 4;
                            count++;
                        }
                    }
                }
            }
            cur = fn_800F0FE4();
        } while (cur != 0);
    }
    fn_800F100C();
    return count;
}
