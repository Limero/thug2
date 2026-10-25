// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9E38-0x801F9EB8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801F7608(void *, void *, s32, s32, f32);
void fn_801F9E38(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    struct {
        __ps_t a;
        __ps_t b;
    } sp8;
    volatile double _dummy;
    register __ps_t *pb __asm__("r27");
    register s32 a1 __asm__("r28");
    register s32 a2 __asm__("r29");
    register void *dst __asm__("r30");
    register f32 fa __asm__("fr31");
    Unk_F68EF90C *var_r31;

    var_r31 = *((void * *)&arg0->unk0xC);
    a1 = arg1;
    a2 = arg2;
    fa = farg0;
    if (var_r31 != NULL) {
        __asm__("" : "=r"(pb) : "r"(&sp8));
        do {
            dst = (char *)var_r31 + 8;
            fn_801F7608(&sp8, dst, a1, a2, fa);
            var_r31->unk0x8 = sp8.a;
            ((__ps_t *)dst)[1] = pb[1];
            var_r31 = var_r31->unk0x24;
        } while (var_r31 != NULL);
    }
}
