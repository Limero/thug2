// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C52EC-0x801C5510 (548B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303150;
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 fn_80141988(Unk_C7387A53 * arg0);
s32 Tmr_GetTime();
extern void fn_8020D190(Unk_CA1C78B1 * arg0);
extern void fn_801F1388(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_801D0EF8(Unk_E5AABED0 * arg0, s32 arg1, Unk_C8FEE62D * arg2, Unk_DB0E2BAB * arg3);
extern void fn_801C0A38(Unk_3190581D * arg0, Unk_18AF37A6 * arg1);
extern void fn_801BBA68(Unk_0C1F2A74 * arg0, s32 *arg1);
extern void fn_801C51A4(Unk_C8FEE62D * arg0, s32 arg1);

void fn_801C52EC(Unk_DB0E2BAB *arg0) {
    s32 sp8[0x16];
    s32 node_a;
    s32 t;
    s32 node_c;
    s32 node_b;
    Unk_CC629601 *vt1;
    Unk_CC629601 *vt2;
    Unk_CC629601 *vt3;
    Unk_CC629601 *vt4;
    s32 f34;
    s32 n2;
    s32 n3;
    s32 n4;
    s32 type;
    s32 flag;
    s32 old_t;
    s32 i;

    if ((*(s32 *)(arg0->unk0x38 + 0x20) != 0)) {
        old_t = arg0->unk0x20;
        arg0->unk0x24 = lbl_80303150 + Tmr_GetTime() - old_t;
        arg0->unk0x20 = lbl_80303150 + Tmr_GetTime();
        node_a = GetChecksum_3(arg0->unk0xC, QB_WALK);
        node_b = GetChecksum_3(t = fn_80141988(arg0->unk0xC), QB_SKATERCAMERA);
        node_c = GetChecksum_3(t, QB_WALKCAMERA);
        fn_8020D190(node_a);
        vt1 = ((Unk_8F9C276C *)node_a)->unk0x18;
        vt1->unk0x44(node_a + vt1->unk0x40, 1);
        vt2 = ((CScript *)node_c)->unk0x18;
        vt2->unk0x44(node_c + vt2->unk0x40, 1);
        fn_801F1388(arg0->unk0x38, 0);
        f34 = arg0->unk0x34;
        vt3 = ((CScript *)f34)->unk0x18;
        vt3->unk0x44(f34 + vt3->unk0x40, 0);
        type = ((Unk_8F9C276C *)node_a)->unk0x808;
        flag = (((Unk_8F9C276C *)node_a)->unk0x1C == 0);
        fn_801D0EF8(arg0->unk0x34, flag,
                    (type == 1) ? node_a + 0x810 : 0,
                    (type == 2) ? node_a + 0x830 : 0);
        n2 = GetChecksum_3(arg0->unk0xC, QB_SKATERROTATE);
        ((s32 (*)(s32, s32))*(s32 *)(((CScript *)n2)->unk0x18 + 0x44))(
            n2 + *(s16 *)(((CScript *)n2)->unk0x18 + 0x40), 0);
        n3 = GetChecksum_3(arg0->unk0xC, QB_SKATERADJUSTPHYSICS);
        ((s32 (*)(s32, s32))*(s32 *)(((CScript *)n3)->unk0x18 + 0x44))(
            n3 + *(s16 *)(((CScript *)n3)->unk0x18 + 0x40), 0);
        n4 = GetChecksum_3(arg0->unk0xC, QB_SKATERFINALIZEPHYSICS);
        ((s32 (*)(s32, s32))*(s32 *)(((CScript *)n4)->unk0x18 + 0x44))(
            n4 + *(s16 *)(((CScript *)n4)->unk0x18 + 0x40), 0);
        vt4 = ((CScript *)node_b)->unk0x18;
        vt4->unk0x44(node_b + vt4->unk0x40, 0);
        for (i = 0; i < 4; i++) {
        }
        fn_801C0A38(node_c, &sp8);
        fn_801BBA68(node_b, &sp8);
        if ((arg0->unk0x1C != 0)) {
            fn_801C51A4(arg0, arg0->unk0x1C);
        }
    }
}
