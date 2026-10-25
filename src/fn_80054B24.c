// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054B24-0x80054C00 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80293140[];
void fn_80054894(void *, s32, s32);
unsigned int Script_GenerateCRC(const char *);
void *fn_80054DC4(s32);
s32 strcmp(const char *, const char *);
s32 fn_80055CB0(Unk_CFB386B2 *);
unsigned int fn_8000A778(const char *);
Unk_897A0ACF *fn_8005D7A0(s32);
s32 fn_8005D734(Unk_897A0ACF *);
Unk_897A0ACF *fn_8005D60C(void *, s32, s32, s32, s32);
void fn_80077088(void *, s32);
void fn_800562B0(Unk_CFB386B2 *, s32, s32);
Unk_CFB386B2 *fn_80054B24(void *arg0, s32 arg1) {
    char sp8[0x80];
    char sp88[0x80];
    Unk_897A0ACF *t;
    register Unk_CFB386B2 *p __asm__("r29");
    Unk_CFB386B2 *q;
    Unk_897A0ACF *var_r30;

    p = (Unk_CFB386B2 *)sp88;
    fn_80054894(sp8, arg1, 0);
    sprintf((char *)p, (s32)lbl_80293140, arg1, arg1);
    q = p;
    p = (Unk_CFB386B2 *)fn_80054DC4((s32)Script_GenerateCRC((char *)arg0));
    if (strcmp((char *)p + 0x164, sp8) == 0) {
        fn_80055CB0(p);
        t = fn_8005D7A0((s32)fn_8000A778((char *)q));
        if (t != NULL) {
            fn_8005D734(t);
        }
    }
    var_r30 = fn_8005D60C((void *)q, 1, 0, 0, 0);
    fn_80077088(p, (s32)sp8);
    fn_800562B0(p, (s32)sp8, (s32)var_r30);
    return p;
}
