// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E39C-0x8000E448 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct { char pad0x0[0x14]; void *unk0x14; } E39C_self;

s32 fn_8000CDDC(s32, char *, void *, void *);
void fn_8000EB24(void *);
s32 fn_8000EB38(void *, s32);

s32 fn_8000E39C(E39C_self *arg0, u8 *arg1, void *arg2, void *arg3) {
    char sp8[0x7c];
    u8 *src;
    char *dst;
    char temp;
    s8 c0;
    s32 node;
    s32 var_r3;

    src = arg1;
    dst = sp8;
    c0 = (s8)arg1[0];
    sp8[0] = arg1[0];
    if (c0 != 0) {
        do {
            if (dst[0] == '/') {
                dst[0] = '\\';
            }
            dst[1] = src[1];
            temp = src[1];
            src++;
            dst++;
        } while (temp != 0);
    }
    fn_8000EB24(arg0->unk0x14);
    node = fn_8000EB38(arg0->unk0x14, 0);
    while (node != 0) {
        var_r3 = fn_8000CDDC(node, sp8, arg2, arg3);
        if (var_r3 != 0) {
            goto done;
        }
        node = fn_8000EB38(arg0->unk0x14, 0);
    }
    var_r3 = 0;
done:
    return var_r3;
}
