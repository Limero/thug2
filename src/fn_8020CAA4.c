// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020CAA4-0x8020CCFC (600B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF4A8[];
extern s32 lbl_80303150[];
extern void fn_80214A30(Unk_CABC8719 *);
extern void fn_802144B8(Unk_406D5192 *);
extern f32 fn_800144C8(void);
extern void fn_80214FF0(Unk_9C44AE00 *);
extern void fn_8020D530(Unk_7497A58C *);
extern void fn_80210438(Unk_75ACDAE8 *);
extern void fn_800E76B4(Unk_5ECDC062 *);
extern void fn_800EAC3C(Unk_C4A686EC *);
extern void fn_80212F20(Unk_D538E2BB *);
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, u32, f32 *, s32);
extern s32 Tmr_GetTime(void);
extern void fn_80212B18(Unk_827D1578 *);
extern void fn_80213FA8(Unk_5B67AA84 *);
extern void fn_80214278(Unk_DB0E2BAB *);
extern void fn_80211B70(Unk_8D4662E6 *);
extern void fn_80211E5C(Unk_851C2A88 *);
extern void fn_80214690(Unk_A6C1F93A *);
extern void fn_80211FE8(Unk_3CA4CCE5 *);
extern void fn_802150E4(Unk_28EF92FB *, s32);
extern void fn_8009F010(s32, s32, s32);
extern void fn_8021546C(Unk_27E58CF3 *);
extern void fn_802151B0(Unk_66B68E7E *);
extern void fn_801ED2DC(Unk_8FAE40CA *);
void fn_8020CAA4(Unk_298A0A9D *arg0) {
    f32 sp8;
    f32 cur;
    f32 rate;
    register char *anch __asm__("r9");
    s32 saved80;
    s32 z;
    s32 mode;

    saved80 = arg0->unk0x80;
    if (arg0->unk0xAC != 0) {
        if (*(s32 *)(arg0->unk0x183C + (s32)0x128) == 0) {
            arg0->unk0xAC = 0;
        }
    }
    z = 0;
    arg0->unk0x84 = arg0->unk0x80;
    arg0->unk0x80 = z;
    fn_80214A30(arg0);
    fn_802144B8(arg0);
    arg0->unk0x70 = arg0->unk0x28;
    arg0->unk0x78 = arg0->unk0x30;
    arg0->unk0x88 = fn_800144C8();
    arg0->unk0x7D0 = z;
    ((Unk_F6393DBC *)arg0)->unk0x2C =
        ((Unk_F6393DBC *)arg0)->unk0x2C - arg0->unk0x7CC;
    fn_80214FF0(arg0);
    switch (arg0->unk0x1C) {
    case 0:
        fn_8020D530(arg0);
        break;
    case 1:
        fn_80210438(arg0);
        break;
    case 2:
        fn_800E76B4(arg0);
        break;
    case 3:
        fn_800EAC3C(arg0);
        break;
    case 4:
        fn_80212F20(arg0);
        break;
    }
    if (*(s32 *)(arg0->unk0x184C + (s32)0x30) == 0) {
        if (arg0->unk0x7D0 == 0) {
            GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_CURB_FLOAT_LERP_DOWN_RATE, &sp8, 1);
            anch = (char *)0x802B0000;
            cur = arg0->unk0x7CC;
            rate = sp8;
            __asm__ __volatile__("" : "+f"(rate));
            arg0->unk0x7CC =
                (*(f32 *)(anch - 0xB58) - cur) * (rate * arg0->unk0x88) + cur;
        }
        ((Unk_F6393DBC *)arg0)->unk0x2C =
            ((Unk_F6393DBC *)arg0)->unk0x2C + arg0->unk0x7CC;
        mode = arg0->unk0x1C;
        if (mode == 0) {
            s32 t20 = arg0->unk0x20;
            if ((u32)(*(s32 *)lbl_80303150 + Tmr_GetTime() - t20) > 0x1F4U) {
                fn_80212B18(arg0);
                if (*(s32 *)(arg0->unk0x184C + (s32)0x30) != 0) {
                    return;
                }
            }
        }
        fn_80213FA8(arg0);
        fn_80214278(arg0);
        if ((u32)arg0->unk0x1C <= 1U) {
            fn_80211B70(arg0);
        }
        fn_80211E5C(arg0);
        fn_80214690(arg0);
        fn_80211FE8(arg0);
        fn_802150E4(arg0, saved80);
        fn_8009F010(arg0->unk0xC,
                    arg0->unk0x80, 0);
        fn_8021546C(arg0);
        fn_802151B0(arg0);
        fn_801ED2DC(arg0->unk0x1858);
        {
            s32 cnt = arg0->unk0x7C8;
            if (cnt > 0) {
                s32 dec = cnt - 1;
                arg0->unk0x7C8 = dec;
                if (dec == 0) {
                    arg0->unk0x7C4 = dec;
                }
            }
        }
    }
}
