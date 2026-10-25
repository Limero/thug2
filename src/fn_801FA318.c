// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA318-0x801FA494 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Object/level data builder: iterates a u16 count table (offset 0x38/0x3A)
// and for each entry walks a per-entry record list (offset 0x1CA, stride 0xA),
// constructing nodes via fn_801F9820 and filling fixed-point fields with
// (raw - 0x43300000-double-trick) * scale from rodata lbl_802AE598/A5A0/A5A4.
// Suggested rename: BuildObjectDataTable.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801FB15C(Unk_C7387A53 * arg0);
extern void *fn_801FB248(Unk_C7387A53 * arg0);
extern void *fn_801F9820(Unk_C7387A53 * arg0);

void fn_801FA318(Unk_57FB3CEB *arg0) {
    f32 temp_f29;
    f32 temp_f30;
    f64 temp_f31;
    s32 temp_r25;
    Unk_4BCBB3F6 *temp_r3;
    s32 var_r9;
    u32 inA;
    s16 inB;
    s16 inC;
    s16 inD;
    u16 *var_r27;
    char *var_r31;
    u16 temp_r23;
    u16 temp_r28;
    u32 var_r29;
    u32 nxt;
    register u32 var_r30 __asm__("r30");
    register u32 k4330 __asm__("r30");
    register char *p20 __asm__("r20");
    register char *p21 __asm__("r21");
    register char *p22 __asm__("r22");
    struct {
        char _p[0x18];
        union {
            u32 w[2];
            volatile f64 d;
        } cvt;
    } fr;

    var_r30 = 0U;
    var_r27 = (u16 *)((char *)arg0 + 0x3A);
    fn_801FB15C(arg0);
    var_r31 = (char *)arg0 + 0x1CA;
    temp_r23 = *((u16 *)&arg0->unk0x38);
    if (var_r30 < temp_r23) {
        p20 = (char *)0x802B0000;
        p21 = (char *)0x802B0000;
        p22 = (char *)0x802B0000;
        __asm__ volatile("" ::: "memory");
        do {
            temp_r28 = *var_r27;
            temp_r25 = (s32)fn_801FB248(arg0);
            __asm__("" : "+r"(temp_r25));
            var_r29 = 0U;
            nxt = var_r30 + 1U;
            var_r27 += 1;
            if (var_r29 < temp_r28) {
                k4330 = QB_INT_TO_DOUBLE_BIAS;
                temp_f31 = *(f64 *)(p20 - 0x1A68);
                temp_f29 = *(f32 *)(p21 - 0x1A60);
                temp_f30 = *(f32 *)(p22 - 0x1A5C);
                do {
                    temp_r3 = (s32)fn_801F9820((void *)temp_r25);
                    if (temp_r3 != 0) {
                        var_r9 = 1;
                        if (((Unk_F5487039 *)var_r31)->unk0x8 == 0) {
                            var_r9 = 0;
                        }
                        ((Unk_1D62F22E_2 *)temp_r3)->unk0x18 = var_r9;
                        inA = ((Unk_F5487039 *)var_r31)->unk0x6;
                        {
                            register s32 dc11 __asm__("r11");
                            register s32 dc10 __asm__("r10");
                            register s32 dc8 __asm__("r8");
                            __asm__ volatile("mr %0,%1" : "=r"(dc11) : "r"(var_r9));
                            __asm__ volatile("mr %0,%1" : "=r"(dc10) : "r"(var_r9));
                            __asm__ volatile("mr %0,%1" : "=r"(dc8) : "r"(var_r9));
                        }
                        fr.cvt.w[1] = inA ^ 0x80000000U;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[0] = k4330;
                        temp_r3->unk0x20 = (f32)((fr.cvt.d - temp_f31)) * temp_f29;
                        inB = ((Unk_F5487039 *)var_r31)->unk0x0;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[1] = ((u32)(s32)inB) ^ 0x80000000U;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[0] = k4330;
                        temp_r3->unk0x8 = (f32)((fr.cvt.d - temp_f31)) * temp_f30;
                        inC = ((Unk_F5487039 *)var_r31)->unk0x2;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[1] = ((u32)(s32)inC) ^ 0x80000000U;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[0] = k4330;
                        temp_r3->unk0xC = (f32)((fr.cvt.d - temp_f31)) * temp_f30;
                        inD = ((Unk_F5487039 *)var_r31)->unk0x4;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[1] = ((u32)(s32)inD) ^ 0x80000000U;
                        __asm__ volatile("" ::: "memory");
                        fr.cvt.w[0] = k4330;
                        temp_r3->unk0x10 = (f32)((fr.cvt.d - temp_f31)) * temp_f30;
                    }
                    var_r29 += 1U;
                    var_r31 += 0xA;
                } while (var_r29 < temp_r28);
            }
            var_r30 = nxt;
        } while (var_r30 < temp_r23);
    }
}
