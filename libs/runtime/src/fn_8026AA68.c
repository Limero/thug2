// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026AA68-0x8026AD98 (816B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"

extern f32 lbl_802B2030[];
extern f64 lbl_802B2038;
extern f64 lbl_802B2040;
extern f32 lbl_802B2048[];
extern f32 lbl_8030B1A0[];
extern s32 lbl_803CA3F8; /* max exponent, SDA (want uses signed cmpw) */
struct _reent {
    s32 _errno;
};
extern struct _reent *__getreent(void);

/* NOTE: symbols.txt keeps the raw name (no scope:global); auto-asm atoff.s
   references fn_8026AA68, so the definition must use that symbol, not strtof. */
float fn_8026AA68(const char *string, char **endPtr) {
    int sign, expSign = 0;
    f32 fraction, dblExp, *d;
    register const char *p;
    register int c;
    int exp = 0;
    int fracExp = 0;
    int mantSize;
    int decPt;
    const char *pExp;

    p = string;
    while (isspace(*(u8 *)p)) {
        p += 1;
    }
    if (*p == '-') {
        sign = 1;
        p += 1;
    } else {
        if (*p == '+') {
            p += 1;
        }
        sign = 0;
    }

    decPt = -1;
    for (mantSize = 0;; mantSize += 1) {
        c = *p;
        if (!isdigit(c)) {
            if (c != '.' || decPt >= 0) {
                break;
            }
            decPt = mantSize;
        }
        p += 1;
    }

    pExp = p;
    p -= mantSize;
    if (decPt < 0) {
        decPt = mantSize;
    } else {
        mantSize -= 1;
    }
    if (mantSize > 18) {
        fracExp = decPt - 18;
        mantSize = 18;
    } else {
        fracExp = decPt - mantSize;
    }
    if (mantSize == 0) {
        fraction = lbl_802B2030[0];
        p = string;
        goto done;
    } else {
        int frac1, frac2;

        frac1 = 0;
        for (; mantSize > 9; mantSize -= 1) {
            c = *p;
            p += 1;
            if (c == '.') {
                c = *p;
                p += 1;
            }
            frac1 = 10 * frac1 + (c - '0');
        }
        frac2 = 0;
        for (; mantSize > 0; mantSize -= 1) {
            c = *p;
            p += 1;
            if (c == '.') {
                c = *p;
                p += 1;
            }
            frac2 = 10 * frac2 + (c - '0');
        }
        fraction = (frac1 * lbl_802B2040) + frac2;
    }

    p = pExp;
    if (*p == 'E' || *p == 'e') {
        p += 1;
        if (*p == '-') {
            expSign = 1;
            p += 1;
        } else {
            if (*p == '+') {
                p += 1;
            }
            expSign = 0;
        }
        if (!isdigit(*(u8 *)p)) {
            p = pExp;
            goto done;
        }
        while (isdigit(*(u8 *)p)) {
            exp = exp * 10 + (*p - '0');
            p += 1;
        }
    }
    if (expSign) {
        exp = fracExp - exp;
    } else {
        exp = fracExp + exp;
    }

    if (exp < 0) {
        expSign = 1;
        exp = -exp;
    } else {
        expSign = 0;
    }
    if (exp > lbl_803CA3F8) {
        exp = lbl_803CA3F8;
        __getreent()->_errno = 0x22;
    }
    dblExp = lbl_802B2048[0];
    for (d = lbl_8030B1A0; exp != 0; exp >>= 1, d += 1) {
        if (exp & 1) {
            dblExp *= *d;
        }
    }
    if (expSign) {
        fraction /= dblExp;
    } else {
        fraction *= dblExp;
    }

done:
    if (endPtr != NULL) {
        *endPtr = (char *)p;
    }

    if (sign) {
        return -fraction;
    }
    return fraction;
}
