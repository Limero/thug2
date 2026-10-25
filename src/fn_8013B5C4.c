// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B5C4-0x8013B6A0 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 Crc_GenerateCRCCaseSensitive(void *, s32);

s32 fn_8013B5C4(Unk_440CB216 *arg0, u16 *arg1, u16 *arg2, s32 arg3) {
    u8 sp8[0x51A];
    s32 len;
    u32 crc;
    s32 i;
    u8 key;
    u32 lo;
    u32 hi;
    u16 hdr;
    u8 *q;
    register u8 *p __asm__("r30");

    if (arg3 > 2) {
        if (!(arg0->unk0x2274 & 0x20)) {
            memcpy(arg2, arg1, arg3);
            return 1;
        }
        ((Unk_69EC0EA5 *)sp8)->unk0x518 = *arg1;
        len = arg3 - 2;
        arg1 += 1;
        p = sp8;
        memcpy(p, arg1, len);
        q = p;
        key = ((Unk_67A63938 *)sp8)->unk0x519;
        if (len > 0) {
            i = len;
            do {
                *p = key ^ *p;
                p += 1;
            } while (--i != 0);
        }
        crc = (u32)Crc_GenerateCRCCaseSensitive(sp8, len);
        lo = (u16)crc;
        crc >>= 0x10;
        crc += lo;
        hdr = ((Unk_69EC0EA5 *)sp8)->unk0x518;
        if ((u16)crc == hdr) {
            memcpy(arg2, q, len);
            return 1;
        }
    }
    return 0;
}
