// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234DDC-0x80234EBC (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802B0928[];
extern char lbl_802B0A2C[];
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80238964(void);
void *fn_80235CF8(void);
void fn_801275D4(CStruct *, void *, void *);
bool ScriptGetCustomParkName(CStruct *arg0, CScript *arg1) {
    char sp8[0x40];
    s32 sp48;
    register s32 temp_r5 __asm__("r5");
    s32 var_r9;
    char *base;
    register char *p __asm__("r10");
    sp48 = -1;
    GetInteger(arg0, 0, &sp48, 0);
    fn_80238964();
    temp_r5 = (s32)fn_80235CF8();
    if (sp48 == -1) {
        if (temp_r5 != 0) {
            ((void (*)(CStruct *, void *))fn_801275D4)(arg1->unk0x18, (s32)lbl_802B0928);
        } else {
            fn_801275D4(arg1->unk0x18, (s32)lbl_802B0928, (s32)lbl_802B0A2C);
        }
    } else {
        var_r9 = 0;
        base = &sp8;
        if (var_r9 < sp48) {
            p = base;
            do {
                p[var_r9] = *((u8 *)temp_r5 + var_r9);
                var_r9 += 1;
            } while (var_r9 < sp48);
        }
        base[sp48] = 0;
        fn_801275D4(arg1->unk0x18, (s32)lbl_802B0928, base);
    }
    return true;
}
