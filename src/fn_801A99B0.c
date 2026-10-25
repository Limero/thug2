// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A99B0-0x801A9A4C (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F1C;
extern s32 fn_801A8A38(s32, s32);
u32 fn_801A99B0(Unk_03123917 *arg0, s32 *arg1, u32 arg2) {
    register s32 *out __asm__("r28");
    register u32 lim __asm__("r23");
    u32 count;
    u32 n;
    s32 tbl;
    u32 i;
    u32 off;
    out = arg1;
    count = *((u32 *)&arg0->unk0x804);
    lim = arg2;
    if (count > 0x200U) {
        count = 0x200U;
    }
    n = 0;
    tbl = lbl_80305F1C;
    i = 0;
    off = 0;
    while (i < count) {
        s32 *base = (s32 *)((char *)arg0 + 4);
        if (fn_801A8A38(tbl, *(s32 *)((char *)base + off)) != 0) {
            *out = *(s32 *)((char *)base + off);
            out += 1;
            n += 4;
        }
        if (n >= lim) {
            break;
        }
        off += 4;
        i++;
    }
    return n;
}
