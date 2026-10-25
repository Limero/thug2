// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012B2A0-0x8012B454 (436B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
u8 *fn_8012B2A0(u8 *p) {
    u8 op = p[0];
    u32 v;
    u32 b2;
    register u32 b3 __asm__("r10");
    u8 c;
    switch (op) {
    case 0x00:
        break;
    case 0x01:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:
    case 0x0C:
    case 0x0D:
    case 0x0E:
    case 0x0F:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2C:
    case 0x2D:
    case 0x30:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x42:
    case 0x45:
        p += 1;
        break;
    case 0x02:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1A:
    case 0x2E:
    case 0x43:
    case 0x44:
    case 0x46:
        p += 5;
        break;
    case 0x1E:
        p += 0xD;
        break;
    case 0x1F:
        p += 9;
        break;
    case 0x1B:
    case 0x1C:
        v = *++p;
        v += *++p << 8;
        b2 = *++p;
        b2 <<= 16;
        v += b2;
        b3 = *++p;
        b3 <<= 24;
        v += b3;
        p += 1;
        p += v;
        break;
    case 0x2B:
        p += 5;
        c = *p;
        if (c != 0) {
            do {
                c = *++p;
            } while (c != 0);
        }
        p += 1;
        break;
    case 0x2F:
    case 0x37:
    case 0x40:
    case 0x41:
        v = *++p;
        v += *++p << 8;
        b2 = *++p;
        b2 <<= 16;
        v += b2;
        b3 = *++p;
        b3 <<= 24;
        v += b3;
        p += 1;
        v *= 6;
        p += v;
        break;
    case 0x47:
    case 0x48:
    case 0x49:
        p += 3;
        break;
    }
    return p;
}
