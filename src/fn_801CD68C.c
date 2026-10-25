// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD68C-0x801CD8D4 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
extern s32 lbl_80303150;
extern s32 lbl_80302BD8;
extern f32 lbl_802AD2C0;
extern f32 fn_800144C8(void);
extern void fn_801EC620(void *);
extern void fn_801D17E4(void *);
extern s32 Tmr_GetTime();
extern void fn_801ED130(void *);
extern void fn_801ED4FC(void *);
extern void fn_801D1B3C(void *);
extern void fn_801DE8BC(void *);
extern void fn_801DEADC(void *);
extern void fn_801E4178(void *);
extern void fn_801E8E04(void *);
extern void fn_801E97CC(void *);
extern void fn_801E5B18(void *);
extern void fn_801DA420(void *);
extern void fn_801E6440(void *, s32);
extern void fn_801ED20C(void *);
extern void fn_801ED2DC(void *);
extern void fn_801ED360(void *);
extern void fn_801ED7D4(void *);
extern void fn_8009F054(s32, s32, s32, f32);

void fn_801CD68C(void *arg0) {
    void *a0;
    s32 zero;
    s32 swval;
    s32 var_r4;
    s32 var_r11;
    s32 nv;
    s32 oc;
    s32 lvl;

    a0 = arg0;
    zero = 0;
    *(f32 *)((char *)a0 + (s32)0x94) = fn_800144C8();
    {
        s32 lv = *(s32 *)((char *)a0 + (s32)0x15BC);
        *(s32 *)((char *)a0 + (s32)0x28C) = zero;
        *(s32 *)((char *)a0 + (s32)0x294) = ((*(s32 *)(lv + (s32)0x1C) ^ 3) == 0);
        *(s32 *)((char *)a0 + (s32)0x290) = *(s32 *)(lv + (s32)0xAC);
    }
    fn_801EC620(a0);
    fn_801D17E4(a0);
    {
        s32 t30 = *(s32 *)((char *)a0 + (s32)0x15BC) + (s32)0xD8;
        if (*(s32 *)(t30 + (s32)4) != 0) {
            *(s32 *)(t30 + (s32)4) = zero;
            *(s32 *)(t30 + (s32)8) = lbl_80303150 + Tmr_GetTime();
        }
    }
    {
        s32 t30 = *(s32 *)((char *)a0 + (s32)0x15BC) + (s32)0xE4;
        if (*(s32 *)(t30 + (s32)4) != 0) {
            *(s32 *)(t30 + (s32)4) = zero;
            *(s32 *)(t30 + (s32)8) = lbl_80303150 + Tmr_GetTime();
        }
    }
    fn_801ED130(a0);
    fn_801ED4FC(a0);
    swval = *(s32 *)(*(s32 *)((char *)a0 + (s32)0x15BC) + (s32)0x1C);
    switch (swval) {
    case 0: {
        s32 o = *(s32 *)((char *)a0 + (s32)0xC);
        *(__ps_t *)((char *)a0 + (s32)0x3A0) = *(__ps_t *)(o + (s32)0x58);
        *(__ps_t *)((char *)a0 + (s32)0x3A8) = *(__ps_t *)(o + (s32)0x60);
        fn_801D1B3C(a0);
        fn_801DE8BC(a0);
        break;
    }
    case 1:
        fn_801DEADC(a0);
        if (*(s32 *)(*(s32 *)((char *)a0 + (s32)0x15BC) + (s32)0x1C) == 0) {
            *(s32 *)((char *)a0 + (s32)0x28C) = swval;
        }
        break;
    case 2:
        fn_801E4178(a0);
        break;
    case 3:
        fn_801E8E04(a0);
        break;
    case 4:
        fn_801E97CC(a0);
        break;
    case 5:
        fn_801E5B18(a0);
        break;
    }
    fn_801DA420(a0);
    fn_801E6440(a0, 0);
    fn_801ED20C(a0);
    fn_801ED2DC(a0);
    fn_801ED360(a0);
    fn_801ED7D4(a0);
    var_r11 = 0;
    {
        s32 lv = *(s32 *)((char *)a0 + (s32)0x15BC);
        if (*(s32 *)(lv + (s32)0x1C) == 1 && *(s32 *)(lv + (s32)0x40) != 0) {
            var_r11 = (*(s32 *)(lv + (s32)0xAC) == 0);
        }
    }
    {
        s32 temp_r0 = *(s32 *)((char *)a0 + (s32)0x570);
        if (temp_r0 != var_r11) {
            nv = temp_r0 ^ 1;
            *(s32 *)((char *)a0 + (s32)0x570) = nv;
            oc = *(s32 *)((char *)a0 + (s32)0xC);
            var_r4 = 0x5E27200A;
            if (nv != 0) {
                var_r4 = 0xF225FE69;
            }
            fn_8009F054(oc, var_r4, 0, lbl_802AD2C0);
        }
    }
    if (*(s32 *)(*(s32 *)((char *)a0 + (s32)0x15BC) + (s32)0x1C) != 1) {
        *(s32 *)((char *)a0 + (s32)0x1558) = 0;
    }
    lbl_80302BD8 = 0;
}
