// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F2D8-0x8001F738 (1120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { s8 n; u8 b1; u8 b2; u8 b3; s32 *o; s32 *r; } ap_t;

extern s32 lbl_80300284;
extern s32 lbl_80300288;

void fn_8001F2D8(s32 arg0, ...) {
    ap_t *sv;
    ap_t ap;
    s32 *p;
    s32 *q;
    s32 op;
    s32 val;
    s32 i;
    s32 b;
    s32 f31, f28, f29, f27, m4, m30, f6, f11, f12, f23, f26, f25, f24, f22, f21, f20, f19;
    __builtin_saveregs();
    sv = (ap_t *)((char *)&ap + 0x10);
    ap = *sv;
    f31 = 0;
    f28 = 0;
    f29 = 0;
    f27 = 0;
    m4 = 0;
    m30 = 1;
    f6 = 0;
    f11 = 0;
    f12 = 0;
    f23 = 0;
    f26 = 0;
    f25 = 0;
    f24 = 0;
    f22 = 0;
    f21 = 0;
    f20 = 0;
    f19 = 0;
    for (i = 0; i < arg0; i++) {
        if ((unsigned)(ap.n + 1) <= 8) {
            p = ap.r + ap.n;
            ap.n = (s8)((u8)ap.n + 1);
        } else {
            if (ap.n <= 7) { p = ap.o; ap.n = 8; ap.o = p + 1; }
            else { p = ap.o; ap.o = p + 1; }
        }
        op = *p;
        if ((unsigned)(ap.n + 1) <= 8) {
            q = ap.r + ap.n;
            ap.n = (s8)((u8)ap.n + 1);
        } else {
            if (ap.n <= 7) { q = ap.o; ap.n = 8; ap.o = q + 1; }
            else { q = ap.o; ap.o = q + 1; }
        }
        val = *q;
        switch (op) {
        case 0:
            f27 = val;
            break;
        case 1:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFFE) | val;
            break;
        case 2:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFFD) | (val << 1);
            break;
        case 3:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFFB) | (val << 2);
            break;
        case 4:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFF7) | (val << 3);
            break;
        case 5:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFEF) | (val << 4);
            break;
        case 6:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFDF) | (val << 5);
            break;
        case 7:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFFBF) | (val << 6);
            break;
        case 8:
            m4 = (m4 & QB_UNKNOWN_0xFFFFFF7F) | (val << 7);
            break;
        case 9:
            m30 = val;
            break;
        case 10:
            if (val != 0) {
                f6 = val;
                f28 = 1;
            }
            break;
        case 25:
            if (val != 0) {
                f6 = val;
                f28 = 2;
            }
            break;
        case 11:
            b = 1;
            f11 = val;
            if (f11 == 0) b = 0;
            f29 += b;
            break;
        case 12:
            b = 1;
            f12 = val;
            if (f12 == 0) b = 0;
            f29 += b;
            break;
        case 13:
            b = 1;
            f23 = val;
            if (f23 == 0) b = 0;
            f31 += b;
            break;
        case 14:
            b = 1;
            f26 = val;
            if (f26 == 0) b = 0;
            f31 += b;
            break;
        case 15:
            b = 1;
            f25 = val;
            if (f25 == 0) b = 0;
            f31 += b;
            break;
        case 16:
            b = 1;
            f24 = val;
            if (f24 == 0) b = 0;
            f31 += b;
            break;
        case 17:
            b = 1;
            f22 = val;
            if (f22 == 0) b = 0;
            f31 += b;
            break;
        case 18:
            b = 1;
            f21 = val;
            if (f21 == 0) b = 0;
            f31 += b;
            break;
        case 19:
            b = 1;
            f20 = val;
            if (f20 == 0) b = 0;
            f31 += b;
            break;
        case 20:
            b = 1;
            f19 = val;
            if (f19 == 0) b = 0;
            f31 += b;
            break;
        }
    }
    ((s32 (*)(s32, s32))lbl_80300284)(0x50, f27 | (m4 << 1) | (m30 << 9) | (f6 << 0xB) | (f11 << 0xD) | (f12 << 0xF));
    ((s32 (*)(s32, s32))lbl_80300284)(0x60, f23 | (f26 << 2) | (f25 << 4) | (f24 << 6) | (f22 << 8) | (f21 << 0xA) | (f20 << 0xC) | (f19 << 0xE));
    ((s32 (*)(s32, s32))lbl_80300288)(0x1008, f29 | (f28 << 2) | (f31 << 4));
}
