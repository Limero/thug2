// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011DED0-0x8011E04C (380B). Byte-identical.
#include "types.h"
extern f32 lbl_8029D5F4;
extern s32 lbl_80302CA4;
extern f32 lbl_80302CA8;
extern s32 lbl_80302CB0;
extern bool lbl_80302CB8;
extern s32 lbl_80302CC4;
extern char lbl_8038E248[];
extern char lbl_8038A820[];
s32 fn_8011BC38(void);
s32 fn_8011BC60(void);
s32 fn_80120B44(void);
void fn_8011BEAC(s32);
void StopMusic(void);
s32 fn_8011CD70(s32);
s32 fn_80121448(s32);
void fn_8011E824(s32);
void fn_8011D870(void);
void fn_8011DC88(void);

void fn_8011DED0(void) {
    s32 i;
    s32 off;
    s32 t;
    s32 zero;
    s32 cnt;
    char *b2;
    char *w;

    if ((fn_8011BC38() == 0) || (fn_8011BC60() == 0)) {
        t = fn_80120B44();
        if (t != 0) {
            if (t < 0) {
                fn_8011BEAC(-1);
                StopMusic();
            } else {
                fn_8011BEAC(-1);
            }
        }
        lbl_80302CB8 += 1;
        i = 0;
        off = 0;
        do {
            if (*(void ***)((char *)lbl_8038E248 + off) != NULL) {
                char *q;
                t = fn_8011CD70(i);
                if (t == 0) {
                    q = (char *)*(void ***)((char *)lbl_8038E248 + off);
                    q += 0x1C;
                    *(s32 *)(q + off) = t;
                    *(void ***)((char *)lbl_8038E248 + off) = (void **)t;
                }
            }
            i++;
            off += 4;
        } while (i <= 2);
        zero = 0;
        b2 = lbl_8038A820;
        __asm__("" : "+r"(b2));
        cnt = 3;
        w = b2 + 0x30;
        do {
            if ((*(s32 *)w != 0) && (fn_80121448(*(s32 *)(w - 0x20)) == 1)) {
                fn_8011E824(*(s32 *)w);
                *(s32 *)w = zero;
            }
            w += 0x74;
        } while (--cnt != 0);
        if (((lbl_80302CB8 & 0x3F) == 0) && ((lbl_80302CA8 != lbl_8029D5F4) || (lbl_80302CA4 == 1))) {
            if (lbl_80302CC4 == 0) {
                if ((lbl_80302CB0 != 0) || (lbl_80302CA4 == 1)) {
                    fn_8011D870();
                    return;
                }
                fn_8011DC88();
            }
        }
    }
}
