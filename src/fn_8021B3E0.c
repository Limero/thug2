// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B3E0-0x8021B4C0 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80222C2C(void *, void *);
void fn_8021FF74(void *arg0);
void fn_801371D4(void *, void *);
#include "structs.h"
s32 fn_80009C00(s32);
extern char lbl_80303448[];
void fn_8021B3E0(Unk_6A70655D *arg0) {
    char *var_r31;
    s32 temp_r28;
    s32 var_r29;
    void *temp_r11;
    CScript *temp_r9;
    s32 zero27;
    register s32 tn __asm__("r3");

    temp_r28 = *(s32 *)&lbl_80303448;
    var_r29 = 0;
    zero27 = 0;
    var_r31 = (char *)arg0 + 0xC;
    do {
        tn = *((s32 *)var_r31);
        if (tn != 0) {
            if ((var_r29 == 0) && (fn_8013E2BC() == 0)) {
                fn_80009C00(arg0->unk0xDC);
            }
            fn_801371D4(temp_r28, *((s32 *)var_r31));
            *((s32 *)var_r31) = zero27;
        }
        var_r29 += 1;
        var_r31 += 4;
    } while (var_r29 <= 1);
    temp_r11 = arg0->unk0x108;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + *(s16 *)&temp_r9->unk0x18, 3);
        arg0->unk0x108 = NULL;
    }
    fn_80009C00(arg0->unk0xE0);
    fn_80009C00(arg0->unk0xD4);
    fn_80009C00(arg0->unk0xF8);
    fn_8021FF74(arg0);
    fn_80222C2C(arg0, 0);
}
