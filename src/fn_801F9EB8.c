// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9EB8-0x801F9F2C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1
#include "types.h"
#include "structs.h"
void fn_801F9498(Unk_99DF620B *, Unk_2BAD2BE8 *);
s32 fn_801F9EB8(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_C7387A53 *var_r31;
    s32 var_r30;

    var_r31 = *((void * *)&arg0->unk0xC);
    var_r30 = arg1;
    {
        register void *tst __asm__("r0");
        register void *var_r9 __asm__("r9");
        while (var_r31 != NULL) {
            tst = *((void * *)&var_r31->unk0x24);
            var_r9 = tst;
            if (tst == NULL) break;
            var_r31 = var_r9;
        }
    }
    if (var_r31 != NULL) {
        do {
            register s32 a4 __asm__("r4");
            register void *a3 __asm__("r3");
            a4 = var_r30;
            a3 = var_r31;
            fn_801F9498(a3, a4);
            var_r30 += 0xA;
            var_r31 = *((void * *)&var_r31->unk0x28);
        } while (var_r31 != NULL);
    }
    return var_r30;
}
