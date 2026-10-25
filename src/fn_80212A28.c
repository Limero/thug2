// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80212A28-0x80212B18 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern const f32 lbl_802AF65C;
extern const f32 lbl_802AF660;
extern s32 fn_801D8BA0(Unk_8C41D852 *, s32, CStruct *, CStruct *, CStruct *, Unk_C7387A53 *);
extern s32 fn_800EB67C(Unk_C8FEE62D *, Unk_C7387A53 *);
s32 fn_80212A28(Unk_368EC9DA *arg0) {
    struct { f32 a; f32 b; f32 c; f32 d; } sav;
    Unk_4C649A8C *cp;
    f32 cf;
    f32 temp_f13;
    register s32 two __asm__("r9");
    s32 var_r3;

    if (arg0->unk0xB0 != 0) {
        goto fail;
    }
    if (*(s32 *)(arg0->unk0x184C + 0x28) != 0) {
        goto fail;
    }
    if (*(s32 *)(arg0->unk0x183C + 0x128) == 0) {
        goto fail;
    }
    sav.a = ((Unk_5F85C510 *)arg0)->unk0x38;
    cp = (char *)&sav;
    ((Unk_E266FB50_3 *)cp)->unk0x4 = arg0->unk0x48;
    *((f32 *)&((Unk_E266FB50_3 *)cp)->unk0x8) = ((Unk_5F85C510 *)arg0)->unk0x40;
    cp->unk0xC = lbl_802AF65C;
    if (fn_801D8BA0((void *)arg0->unk0x1858, 0,
                    (char *)arg0 + 0x28, (char *)arg0 + 0x70, cp,
                    (char *)arg0 + 0x830) == 0) {
        goto fail;
    }
    fn_800EB67C((void *)arg0->unk0x1850,
                (s32)((char *)arg0 + 0x1880));
    temp_f13 = sav.b;
    *((__ps_t *)&((Unk_5F85C510 *)arg0)->unk0x38) = *(__ps_t *)&sav;
    cf = lbl_802AF660;
    *((__ps_t *)&((Unk_5F85C510 *)arg0)->unk0x40) = *((__ps_t *)&((Unk_E266FB50_3 *)cp)->unk0x8);
    arg0->unk0x80 = QB_ACIDDROP;
    var_r3 = 1;
    arg0->unk0x3C = cf;
    arg0->unk0x48 = temp_f13;
    two = 2;
    __asm__ __volatile__("" ::: "memory");
    arg0->unk0x808 = two;
    goto done;
fail:
    var_r3 = 0;
done:
    return var_r3;
}
