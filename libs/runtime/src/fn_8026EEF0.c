// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026EEF0-0x8026F20C (796B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u8 pad_34[0x34];
    const char *current_locale;
} Reent;

typedef enum {
    ESCAPE,
    DOLLAR,
    BRACKET,
    AT,
    B,
    J,
    NUL,
    JIS_CHAR,
    OTHER,
    JIS_C_NUM
} JISCharType;

typedef enum {
    ASCII,
    A_ESC,
    A_ESC_DL,
    JIS,
    JIS_1,
    JIS_2,
    J_ESC,
    J_ESC_BR,
    J2_ESC,
    J2_ESC_BR,
    DONE,
    INV,
    JIS_S_NUM
} JISState;

typedef enum {
    COPYA,
    COPYJ,
    COPYJ2,
    MAKE_A,
    MAKE_J,
    NOOP,
    EMPTY,
    ERROR
} JISAction;

extern s32 strcmp(const char *, const char *);
extern u32 strlen(const char *);
extern char lbl_802B22C4[];
extern char lbl_802B22CC[];
extern char lbl_802B22D4[];
extern s32 lbl_8030B4F0[12][9];
extern s32 lbl_8030B6A0[12][9];

s32 fn_8026EEF0(Reent *r, u32 *pwc, const char *s, u32 n, s32 *state) {
    u32 dummy;
    const u8 *t;
    JISAction action;
    JISCharType ch;
    JISState curr_state;
    const u8 *ptr;
    s32 i;
    s32 curr_ch;

    if (pwc == NULL) {
        pwc = &dummy;
    }
    if (s != NULL && n == 0) {
        return -1;
    }

    t = (const u8 *)s;
    if (r->current_locale == NULL || strlen(r->current_locale) <= 1) {
    } else if (strcmp(r->current_locale, lbl_802B22C4) == 0) {
        s32 char1 = *t;

        if (s == NULL) {
            return 0;
        }
        if ((char1 >= 0x81 && char1 <= 0x9F) ||
            (char1 >= 0xE0 && char1 <= 0xEF)) {
            s32 char2;

            char2 = t[1];
            if (n <= 1) {
                return -1;
            }
            if ((char2 >= 0x40 && char2 <= 0x7E) ||
                (char2 >= 0x80 && char2 <= 0xFC)) {
                *pwc = ((u32)t[0] << 8) + t[1];
                return 2;
            }
            return -1;
        }
    } else if (strcmp(r->current_locale, lbl_802B22CC) == 0) {
        s32 char1 = *t;

        if (s == NULL) {
            return 0;
        }
        if (char1 >= 0xA1 && char1 <= 0xFE) {
            s32 char2;

            char2 = t[1];
            if (n <= 1) {
                return -1;
            }
            if (char2 >= 0xA1 && char2 <= 0xFE) {
                *pwc = ((u32)t[0] << 8) + t[1];
                return 2;
            }
            return -1;
        }
    } else if (strcmp(r->current_locale, lbl_802B22D4) == 0) {
        if (s == NULL) {
            *state = 0;
            return 1;
        }

        curr_state = *state == 0 ? ASCII : JIS;
        ptr = t;
        for (i = 0; i < n; ++i) {
            curr_ch = t[i];
            switch (curr_ch) {
                case 0x1B:
                    ch = ESCAPE;
                    break;
                case '$':
                    ch = DOLLAR;
                    break;
                case '@':
                    ch = AT;
                    break;
                case '(':
                    ch = BRACKET;
                    break;
                case 'B':
                    ch = B;
                    break;
                case 'J':
                    ch = J;
                    break;
                case '\0':
                    ch = NUL;
                    break;
                default:
                    if (curr_ch >= 0x21 && curr_ch <= 0x7E) {
                        ch = JIS_CHAR;
                    } else {
                        ch = OTHER;
                    }
                    break;
            }

            action = lbl_8030B6A0[curr_state][ch];
            curr_state = lbl_8030B4F0[curr_state][ch];
            switch (action) {
                case NOOP:
                    break;
                case EMPTY:
                    *state = 0;
                    *pwc = 0;
                    return i;
                case COPYA:
                    *state = 0;
                    *pwc = *ptr;
                    return i + 1;
                case COPYJ:
                    *state = 0;
                    *pwc = ((u32)ptr[0] << 8) + ptr[1];
                    return i + 1;
                case COPYJ2:
                    *state = 1;
                    *pwc = ((u32)ptr[0] << 8) + ptr[1];
                    return ptr - t + 2;
                case MAKE_A:
                case MAKE_J:
                    ptr = t + i + 1;
                    break;
                case ERROR:
                default:
                    return -1;
            }
        }
        return -1;
    }

    if (s == NULL) {
        return 0;
    }
    *pwc = *t;
    if (*t == '\0') {
        return 0;
    }
    return 1;
}
