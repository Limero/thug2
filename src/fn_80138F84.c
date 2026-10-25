// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80138F84-0x8013928C (776B). Byte-identical.
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
s32 fn_8013C548(void *, void *);
s32 fn_8013BF38(void *, void *, s32, s32);
s32 fn_8013DFE4(void *, void *, void *, s32);
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
    u16 x;
    char p3[2];
    s32 y;
} Ev_t;

void fn_80138F84(Unk_33E85B70 *arg0, Unk_2DBBFAC5 *arg1) {
    Ev_t ev;
    register s32 pg __asm__("r27");
    u32 temp_r26;
    register s32 temp_r29 __asm__("r29");
    s32 var_r28;
    s32 temp_r9;
    s32 var_r4;
    s32 var_r9;
    u32 temp_r0;
    u32 var_r4_2;
    s32 tmp_d;

    if (fn_8013E21C(arg0, arg1) != 0) {
        var_r28 = 0;
        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_8029F3F8));
        temp_r26 = *(s32 *)((char *)pg + PG_OFF);
        goto loop_37;
body_37:
        if (fn_8013C548(arg0, arg1) != 0) {
            fn_80137CB4(&ev.a);
            ev.x = *(u16 *)((char *)arg1 + (s32)0x4936);
            ev.c = (s32)&ev.x;
            ev.b = 2;
            ev.a = 9;
            ev.d = 0xFF;
            fn_8013CC84(arg0, arg1->unk0x48, &ev.a);
        }
        if ((fn_8013F764(arg1) != 0) && (fn_8013F734(arg1) == 0)) {
            var_r9 = 1;
            if (!(arg0->unk0x2274 & 4)) {
                var_r9 = 0;
            }
            if ((var_r9 != 0) && ((fn_80137CB4(&ev.a), temp_r9 = arg1->unk0x20E4, temp_r29 = arg0->unk0x0, ev.y = temp_r29, ((temp_r9 == 0) != 0)) || ((u32)(temp_r29 - temp_r9) > temp_r26))) {
                if ((u32)temp_r9 > (u32)arg1->unk0x20E8) {
                    var_r4 = (fn_8013F74C(arg1) == 0) ? arg1->unk0x20B4 : 0;
                    temp_r0 = *(s32 *)((char *)pg + PG_OFF);
                    var_r4_2 = var_r4 + 0x64;
                    if (var_r4_2 > temp_r0) {
                        var_r4_2 = temp_r0;
                    }
                    fn_8013B6F4((char *)arg1 + 0x20B4, var_r4_2);
                }
                arg1->unk0x20E4 = temp_r29;
                ev.c = (s32)&ev.y;
                ev.a = 1;
                ev.b = 4;
                fn_8013CC84(arg0, arg1->unk0x48, &ev.a);
            }
        }
        if (fn_8013BF38(arg0, arg1, 0, 0) == 0) {
            var_r28 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 2, 1) == 0) {
            var_r28 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 1, 1) == 0) {
            var_r28 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 2, 0) == 0) {
            var_r28 = 1;
        }
        if (fn_8013BF38(arg0, arg1, 1, 0) == 0) {
            var_r28 = 1;
        }
        tmp_d = arg1->unk0x58 - arg1->unk0x54;
        if ((tmp_d > 0) && (fn_8013F764(arg1) != 0)) {
            if (arg0->unk0x182C != 0) {
                if (fn_8013DFE4(arg0, arg1->unk0x54, tmp_d, 0) == 0) {
                    goto block_34;
                }
                goto block_35;
            } else {
                if (fn_8013DF58(arg0, arg1->unk0x4C, *(u16 *)((char *)arg1 + (s32)0x50), arg1->unk0x54, tmp_d, 0) == 0) {
                    goto block_34;
                }
                goto block_35;
            }
block_34:
            fn_8013FC10(arg1, arg1->unk0x4934);
            arg1->unk0x58 = (s32)arg1->unk0x54;
            return;
block_35:
            arg0->unk0x17F0 = (s32)(arg0->unk0x17F0 + tmp_d);
            fn_80137364((char *)arg1 + 0x34FC, tmp_d + 0x1C, arg0->unk0x0);
            arg1->unk0x78 = (s32)arg0->unk0x0;
            fn_8013F808(arg1, 0);
            arg1->unk0x58 = (s32)arg1->unk0x54;
        }
        arg1->unk0x4934 = (s32)(arg1->unk0x4934 + 1);
loop_37:
        if ((var_r28 == 0) && (fn_8013C6F0(arg0, arg1) != 0) && (fn_8013E4BC(arg0, arg1) == 0)) {
            goto body_37;
        }
    }
}
