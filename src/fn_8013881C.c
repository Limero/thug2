// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013881C-0x80138BA0 (900B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void *fn_80137CB4(void *);
s32 fn_8013E21C(void *, void *);
s32 fn_8013F764(void *);
s32 fn_8013F734(void *);
s32 fn_8013F74C(void *);
void fn_8013B6F4(void *, s32);
void fn_8013CC84(void *, s32, void *);
s32 fn_8013F818(s32);
s32 fn_8013BF38(void *, void *, s32, s32);
s32 fn_8013FC08(void *);
void fn_8013FC00(void *, s32);
s32 fn_8013DF58(void *, s32, s32, void *, s32, s32);
void fn_8013FC10(void *, s32);
void fn_80137364(void *, void *, void *);
void fn_8013F808(void *, s32);
s32 fn_8013C6F0(void *, void *);
s32 fn_8013E4BC(void *, s32);

extern char lbl_8029F3F8[];
#define PG_OFF (-0xC08)

typedef struct {
    s8 a;
    char p1[1];
    s16 b;
    s32 c;
    s32 d;
    char p2[0x1C];
    s8 e;
    char p3[1];
    s16 f;
    s32 g;
    char p4[0x20];
    s32 h;
    u16 i;
} F_t;

void fn_8013881C(Unk_33E85B70 *arg0, Unk_2DBBFAC5 *arg1) {
    F_t fr;
    register s32 pg __asm__("r26");
    s32 temp_r25;
    register s32 var_r27 __asm__("r27");
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_3;
    s32 temp_r9;
    s32 var_r0;
    s32 var_r4;
    s32 var_r9;
    s32 tmp1;
    s32 tmp2;
    u32 temp_r0;
    u32 var_r4_2;

    fn_80137CB4(&fr.a);
    if (fn_8013E21C(arg0, arg1) != 0) {
        var_r27 = 0;
        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_8029F3F8));
        temp_r25 = *(s32 *)((char *)pg + PG_OFF);
        goto loop_38;
body_38:
    __asm__("" : "+r"(var_r27));
        if ((fn_8013F764(arg1) != 0) && (fn_8013F734(arg1) == 0)) {
            var_r9 = 1;
            if (!(arg0->unk0x2274 & 4)) {
                var_r9 = 0;
            }
            if ((var_r9 != 0) && ((fn_80137CB4(&fr.e), temp_r9 = arg1->unk0x20E4, temp_r30 = arg0->unk0x0, fr.h = temp_r30, ((temp_r9 == 0) != 0)) || ((u32) (temp_r30 - temp_r9) > temp_r25))) {
                if ((u32) temp_r9 > (u32) arg1->unk0x20E8) {
                    var_r4 = (fn_8013F74C(arg1) == 0) ? arg1->unk0x20B4 : 0;
                    temp_r0 = *(s32 *)((char *)pg + PG_OFF);
                    var_r4_2 = var_r4 + 0x64;
                    if (var_r4_2 > temp_r0) {
                        var_r4_2 = temp_r0;
                    }
                    fn_8013B6F4((char *)arg1 + 0x20B4, var_r4_2);
                }
                arg1->unk0x20E4 = temp_r30;
                fr.g = (s32) &fr.h;
                fr.f = 4;
                fr.e = 1;
                fn_8013CC84(arg0, arg1->unk0x48, &fr.e);
            }
        }
        fr.i = *(u16 *)((char *)arg1 + (s32) 0x4936);
        fr.c = (s32) &fr.i;
        fr.b = 2;
        fr.a = 9;
        fr.d = 0xFF;
        fn_8013CC84(arg0, arg1->unk0x48, &fr.a);
        temp_r30_2 = fn_8013F818(arg1);
        if (fn_8013BF38(arg0, arg1, 0, 0) == 0) {
            var_r27 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 2, 1) == 0) {
            var_r27 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 1, 1) == 0) {
            var_r27 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 2, 0) == 0) {
            var_r27 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 1, 0) == 0) {
            var_r27 = 1;
        }
        if (fn_8013F818(arg1) > temp_r30_2) {
            *(s32 *)&fr.e = 1;
            var_r0 = 1;
            if (!(arg1->unk0x68 & 1)) {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                fn_8013B6F4((char *)arg1 + 0x20B4, *(s32 *)((char *)pg + PG_OFF));
                tmp1 = fn_8013FC08(arg1) - 0x1F4;
                fn_8013FC00(arg1, tmp1);
                tmp2 = fn_8013FC08(arg1);
                if (tmp2 <= 0x52F) {
                    fn_8013FC00(arg1, 0x530);
                }
            }
        }
        temp_r30_3 = arg1->unk0x58 - arg1->unk0x54;
        if ((temp_r30_3 > 0) && (fn_8013F764(arg1) != 0)) {
            if (fn_8013DF58(arg0, arg1->unk0x4C, *(u16 *)((char *)arg1 + (s32) 0x50), arg1->unk0x54, temp_r30_3, 0) == 0) {
                fn_8013FC10(arg1, arg1->unk0x4934);
                arg1->unk0x58 = (s32) arg1->unk0x54;
                goto out_loop;
            }
            arg0->unk0x17F0 = (s32) (arg0->unk0x17F0 + temp_r30_3);
            fn_80137364((char *)arg1 + 0x34FC, temp_r30_3 + 0x1C, arg0->unk0x0);
            fn_8013F808(arg1, 0);
            arg1->unk0x78 = (s32) arg0->unk0x0;
            arg1->unk0x58 = (s32) arg1->unk0x54;
        }
        arg1->unk0x4934 = (s32) (arg1->unk0x4934 + 1);
loop_38:
        if ((var_r27 == 0) && (fn_8013C6F0(arg0, arg1) != 0) && (fn_8013E4BC(arg0, arg1) == 0)) {
            goto body_38;
        }
out_loop:
        if ((fn_8013E4BC(arg0, arg1) != 0) && (fn_8013F818(arg1) == 0)) {
            tmp1 = fn_8013FC08(arg1) + 0x3E8;
            fn_8013FC00(arg1, tmp1);
        }
    }
}
