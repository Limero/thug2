// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171B54-0x80171BF4 (160B). Byte-identical.
#include "types.h"
extern char lbl_80305EAC[];
s32 fn_801754AC(s32);
s32 fn_8016F668(s32);
void fn_80171BF4(s32, s32 *);
void fn_80171B54(s32 arg0, s32 arg1) {
    struct todw { char _pad[0xC]; s32 w[5]; };
    s32 sp8[5];
    s32 *w;
    s32 *sp;
    char *h;
    struct todw *s;
    s32 temp_r3;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    if (fn_801754AC(*(s32 *)&lbl_80305EAC) == 0) {
        temp_r3 = fn_8016F668(arg0) * 0x190;
        h = (char *)arg0 + 0xC;
        if (arg1 != *(s32 *)(h + temp_r3)) {
            *(s32 *)(h + temp_r3) = arg1;
            s = (struct todw *)(temp_r3 + arg0);
            w = s->w;
            sp = sp8;
            t0 = s->w[0];
            t1 = w[1];
            t2 = w[2];
            t3 = w[3];
            t4 = w[4];
            sp8[0] = t0;
            sp[1] = t1;
            sp[2] = t2;
            sp[3] = t3;
            sp[4] = t4;
            fn_80171BF4(arg0, sp);
        }
    }
}
