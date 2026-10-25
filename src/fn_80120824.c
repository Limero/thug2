// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120824-0x80120924 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// NOTE (2026-10-04): this object has a PRIVATE .rodata pool — the
// strcpy(".ogg") literal. tools/fix_fp_pool.py retargets its ONE pool site to
// lbl_8029D820 and empties .rodata. The site's address is used TWICE (an
// `lfs`/`lwz` and an `addi`), i.e. one HA + TWO LO relocs; the old
// proximity-based HA/LO pairing retargeted the second LO to the wrong
// lbl_ and left it dangling against the emptied .rodata (recipes §6gu).
// Spelling the literal as a `static const char[]` does NOT help — mwld's LCF
// has no .sbss2 and GCC always emits those sections.
#include "types.h"
extern char lbl_80302F30[];
extern s32 lbl_80302F28;
extern bool lbl_8037B7A4;
extern char lbl_8039D940[];
s32 fn_801209CC(void);
void fn_8001476C(void);
void fn_801205D0(void);
void fn_8012063C(void);
void fn_80136234(void (*)(void), void (*)(void));
s32 fn_80136BE4(char *path);
u32 strlen(const char *);
char *strcpy(char *, const char *);

bool fn_80120824(char *path, s32 arg1) {
    char *p;
    lbl_80302F28 = arg1;
    if (lbl_8037B7A4 == 0 && fn_801209CC() == 1) {
        fn_8001476C();
        strcpy(&lbl_80302F30[10], path + 10);
        strcpy(&lbl_80302F30[strlen(&lbl_80302F30[0])], ".ogg");
        for (p = &lbl_80302F30[0]; *p != 0; p++) {
            if (*p == '\\') {
                *p = '/';
            }
        }
        fn_80136234(fn_801205D0, fn_8012063C);
        if (fn_80136BE4(&lbl_80302F30[0]) != 0) {
            s32 *o = (s32 *)lbl_8039D940;
            o[0xC4 / 4] = 0;
            o[0xC8 / 4] = 0;
            return true;
        }
    }
    return false;
}
