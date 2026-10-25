// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80212B18-0x80212C54 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern const f32 lbl_802AF664;
extern char lbl_802AF808[];
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_800DF004(Unk_C7387A53 *, void *, Unk_D3DFD83F *);
extern s32 fn_801D8BA0(Unk_8C41D852 *, s32, CStruct *, CStruct *, CStruct *, Unk_C7387A53 *);
extern void fn_8020D2E4(Unk_6553C923 *, s32);
s32 fn_80212B18(Unk_827D1578 *arg0) {
    struct { __ps_t a; __ps_t b; } fr;
    __ps_t *pp;
    f32 sp18;
    register s32 two __asm__("r9");
    f32 cf;
    f32 temp_f13;
    s32 temp_r3;
    s32 var_r3;

    if ((arg0->unk0xB0 != 0) ||
        (*(s32 *)(arg0->unk0x184C + 0x28) != 0) ||
        (*(s32 *)(arg0->unk0x183C + 0x128) == 0)) {
        var_r3 = 0;
        goto done;
    }
    fr.a = arg0->unk0x38;
    pp = (__ps_t *)&fr;
    pp[1] = arg0->unk0x40;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_ACID_DROP_JUMP_VELOCITY, &sp18, 1);
    temp_r3 = arg0->unk0x1858;
    ((Unk_560A7BB5 *)&fr)->unk0x4 = sp18;
    if (fn_801D8BA0((void *)temp_r3, 0, (char *)arg0 + 0x28,
                    (char *)arg0 + 0x70, pp, (char *)arg0 + 0x830) == 0) {
        var_r3 = 0;
        goto done;
    }
    if (arg0->unk0x1940 != 0) {
        fn_800DF004((void *)arg0->unk0x1848,
                    (void *)lbl_802AF808, (char *)arg0 + 0x1880);
        var_r3 = 1;
        if (*(s32 *)(arg0->unk0x184C + 0x30) != 0) {
            goto done;
        }
    }
    fn_8020D2E4(arg0, 1);
    cf = lbl_802AF664;
    temp_f13 = ((Unk_560A7BB5 *)&fr)->unk0x4;
    arg0->unk0x38 = fr.a;
    arg0->unk0x80 = QB_ACIDDROP;
    var_r3 = 1;
    ((Unk_F6393DBC *)arg0)->unk0x3C = cf;
    arg0->unk0x40 = pp[1];
    arg0->unk0x48 = temp_f13;
    two = 2;
    arg0->unk0x808 = two;
done:
    return var_r3;
}
