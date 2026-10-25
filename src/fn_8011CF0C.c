// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011CF0C-0x8011D0AC (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8038C8C0[];
extern char lbl_8038A820[];
extern char lbl_8038E248[];
extern char lbl_8029D5B8[];
extern char lbl_8029D5C0[];
extern f32 lbl_8029D5C4;
extern f32 lbl_8029D5C8;
extern char lbl_80302CA8[];
extern char lbl_80302CAC[];
extern bool lbl_80302CBC;
s32 fn_8011BC38(void);
s32 fn_8011BC60(void);
void PCMAudio_Init(void);
s32 Script_GetInteger(s32, s32);
void Pcm_Init(void) {
    volatile double _dummy;
    volatile double _dummy2;
    volatile union {
        u32 w[2];
        f64 d;
    } cvt;
    s32 var_ctr;
    s32 zero;
    s32 var_ctr_2;
    s32 *var_r11;
    s32 var_p;
    s32 var_end;
    s32 temp_r3;
    f32 temp_f0;
    f64 var_f31;
    f32 var_f30;
    register u32 magic __asm__("r30");
    register s32 pg31 __asm__("r9");
    register s32 pg30 __asm__("r10");

    var_ctr = 3;
    var_p = (s32)lbl_8038E248;
    var_p += 8;
    zero = 0;
    do {
        *(s32 *)var_p = zero;
        var_p -= 4;
    } while (--var_ctr != 0);
    if ((fn_8011BC38() == 0) || (fn_8011BC60() == 0)) {
        s32 pg31d;
        PCMAudio_Init();
        magic = QB_INT_TO_DOUBLE_BIAS;
        {
            register s32 hv __asm__("r3");
            __asm__("lis %0,%1" : "=&r"(hv) : "i"(QB_MUSICVOLUME >> 16));
            lbl_80302CBC = 1;
            __asm__("ori %0,%0,%1\n\tli 4,0" : "+r"(hv) : "i"(QB_MUSICVOLUME & 0xFFFF));
            temp_r3 = ((s32 (*)(s32))Script_GetInteger)(hv);
        }
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg31d) : "s"(lbl_80302CA8));
        cvt.w[1] = (u32)temp_r3 ^ 0x80000000U;
        __asm__ volatile("lis %0,%1@ha" : "=&r"(pg31) : "s"(lbl_8029D5B8));
        var_f31 = *(f64 *)((char *)pg31 - 0x2a48);
        __asm__ volatile("lis %0,%1@ha" : "=&r"(pg30) : "s"(lbl_8029D5C0));
        cvt.w[0] = magic;
        var_f30 = *(f32 *)((char *)pg30 - 0x2a40);
        __asm__ volatile("" ::: "memory");
        temp_f0 = (f32)(cvt.d - var_f31);
        *(f32 *)((char *)pg31d + 0x2CA8) = temp_f0;
        if (temp_f0 == var_f30) {
            *(f32 *)((char *)pg31d + 0x2CA8) = lbl_8029D5C4;
        }
        __asm__("lis %0,%1@ha" : "=r"(pg31d) : "s"(lbl_80302CAC));
        temp_r3 = Script_GetInteger(QB_MUSICSTREAMVOLUME, 0);
        cvt.w[1] = (u32)temp_r3 ^ 0x80000000U;
        cvt.w[0] = magic;
        temp_f0 = (f32)(cvt.d - var_f31);
        *(f32 *)((char *)pg31d + 0x2CAC) = temp_f0;
        if (temp_f0 == var_f30) {
            *(f32 *)((char *)pg31d + 0x2CAC) = lbl_8029D5C8;
        }
        var_p = (s32)lbl_8038C8C0;
        var_end = var_p + 0xCB0;
        do {
            ((Unk_76B26A14 *)var_p)->unk0xC80 = 0;
            ((Unk_76B26A14 *)var_p)->unk0xC88 = 0ULL;
            ((Unk_76B26A14 *)var_p)->unk0xC90 = 0ULL;
            ((Unk_76B26A14 *)var_p)->unk0xC98 = 0ULL;
            ((Unk_76B26A14 *)var_p)->unk0xCA0 = 0ULL;
            ((Unk_76B26A14 *)var_p)->unk0xCA8 = 1;
            var_p += 0xCB0;
        } while (var_p <= var_end);
        {
            register s32 pa9 __asm__("r9");
            register s32 pa11 __asm__("r11");
            var_ctr_2 = 3;
            __asm__("lis %0,%1@ha" : "=&r"(pa11) : "s"(lbl_8038E248));
            __asm__("lis %0,%1@ha" : "=&r"(pa9) : "s"(lbl_8038A820));
            pa9 = pa9 - 0x57E0;
            pa11 = pa11 - 0x1DB8;
            zero = 0;
            do {
                *(s32 *)pa11 = 0;
                *(s32 *)pa9 = 0;
                pa11 += 4;
                *(s32 *)((char *)pa9 + 4) = 0;
                pa9 += 0x74;
            } while (--var_ctr_2 != 0);
        }
    }
}
