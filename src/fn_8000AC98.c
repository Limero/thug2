// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000AC98-0x8000AF90 (760B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80311288;
extern s32 lbl_8031128C;
extern u8 *lbl_80311290;
extern s32 lbl_802FFE3C;
extern bool lbl_802FFE40;
extern bool lbl_802FFE44;
void fn_8000A868(void);
void fn_8000A924(void);
void fn_8000A990(s32 arg0);
void fn_8000AB40(s32 arg0);
s32 fn_8000AC98(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 code_buf[17];
    s32 j;
    s32 ptr;
    u8 mask;
    s32 r_pos;
    s32 insert_pos;
    s32 srclen;
    s32 last_len;
    s32 n;
    s32 idx;
    s8 c;

    lbl_802FFE3C = 0;
    lbl_802FFE40 = 0;
    lbl_802FFE44 = 0;
    fn_8000A868();
    code_buf[0] = 0;
    ptr = mask = 1;
    insert_pos = 0;
    r_pos = 0xFEE;
    for (j = 0; j < r_pos; j++) {
        lbl_80311290[j] = ' ';
    }
    srclen = 0;
    if (arg2 != 0) {
        do {
            c = *arg0;
            idx = srclen + 0xFEE;
            srclen++;
            arg0++;
            arg2--;
            lbl_80311290[idx] = c;
        } while (srclen <= 0x11 && arg2 != 0);
    }
    lbl_802FFE3C = srclen;
    if (srclen == 0) {
        fn_8000A924();
        return 0;
    }
    __asm__ __volatile__("");
    n = 0xFED;
    j = 0x12;
    do {
        fn_8000A990(n);
        n--;
    } while (--j != 0);
    fn_8000A990(0xFEE);
    do {
        if (lbl_8031128C > srclen) {
            lbl_8031128C = srclen;
        }
        if (lbl_8031128C <= 2) {
            lbl_8031128C = 1;
            code_buf[0] |= mask;
            code_buf[ptr++] = lbl_80311290[r_pos];
        } else {
            code_buf[ptr++] = (u8)lbl_80311288;
            code_buf[ptr++] = (u8)(((lbl_80311288 >> 4) & 0xF0) | (lbl_8031128C - 3));
        }
        if ((mask <<= 1) == 0) {
            for (j = 0; j < ptr; j++) {
                *arg1++ = code_buf[j];
            }
            lbl_802FFE40 += ptr;
            code_buf[0] = 0;
            mask = 1;
            ptr = 1;
        }
        last_len = lbl_8031128C;
        for (j = 0; j < last_len && arg2 != 0; j++) {
            c = *arg0++;
            arg2--;
            fn_8000AB40(insert_pos);
            lbl_80311290[insert_pos] = c;
            if (insert_pos < 0x11) {
                lbl_80311290[insert_pos + 0x1000] = c;
            }
            r_pos = (r_pos + 1) & 0xFFF;
            insert_pos = (insert_pos + 1) & 0xFFF;
            fn_8000A990(r_pos);
        }
        lbl_802FFE3C += j;
        while (j++ < last_len) {
            fn_8000AB40(insert_pos);
            insert_pos = (insert_pos + 1) & 0xFFF;
            r_pos = (r_pos + 1) & 0xFFF;
            if (--srclen != 0) {
                fn_8000A990(r_pos);
            }
        }
    } while (srclen > 0);
    if (ptr > 1) {
        for (j = 0; j < ptr; j++) {
            *arg1++ = code_buf[j];
        }
        lbl_802FFE40 += ptr;
    }
    fn_8000A924();
    return lbl_802FFE40;
}
