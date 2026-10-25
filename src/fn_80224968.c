// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224968-0x80224B70 (520B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303448;
extern s32 lbl_80305EC0;
extern void* lbl_80305EAC;
extern char lbl_8029F480[];
s32 fn_80137CB4(Unk_9F066EC1 * arg0);
s32 fn_8013F764(s32 arg0);
void fn_8013FB94(Unk_72BBAD33 * arg0, s32 arg1);
void fn_8021B54C(CScript * arg0, s32 arg1);
void fn_80198D08(s32 arg0, s32 arg1);
s32 fn_8021E024(void * arg0);
s32 fn_8013FF5C(s32 arg0, s32 arg1);
s32 GetText(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 fn_802195BC(Unk_C7387A53 * arg0);
s32 fn_80137AD4(Unk_F386DC9F * arg0);
s32 strncpy(char *arg0, char *arg1, s32 arg2);
s32 fn_80174AB8(void * arg0, s32 arg1);
s32 fn_8013E034(s32 arg0, CStruct * arg1);
s32 fn_8013FB8C(Unk_72BBAD33 * arg0);
s32 fn_801A4B88(Unk_31DE137E * arg0, void *arg1, s32 arg2, s32 arg3);
void fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);
void fn_8022019C(CScript * arg0, s32 arg1);

typedef struct {
    u8 f0;
    u8 _p1;
    s16 f2;
    s32 f4;
    u8 _p8[4];
    s32 fc;
    u8 _p10[16];
    u8 f20;
} buf_t;

s32 fn_80224968(Unk_DB0E2BAB *a0) {
    struct loc_t {
        s32 sp8;            /* +0x00 -> r1+8 */
        u8 spC;             /* +0x04 */
        u8 spD;             /* +0x05 */
        u8 spE;             /* +0x06 */
        u8 _p7;
        u8 _p8[8];          /* 0x08..0x10 */
        u8 sp18;            /* 0x10 */
        u8 _p11[15];        /* 0x11..0x20 */
        char sp28[16];      /* 0x20 */
        char sp38[0x1000];  /* 0x30 */
        buf_t buf;          /* 0x1030 */
        u8 _pb[4];
        s32 sp1060[3];      /* 0x1058 */
        u8 _pg[4];
        s32 sp1070;         /* 0x1068 */
        u8 _pt;
    } fr;
    s32 *q;
    register s32 v29 __asm__("r29");
    register s32 v28 __asm__("r28");
    register s32 v27 __asm__("r27");
    s32 t;
    s32 lblv;
    s32 temp_r3;
    register s32 v30 __asm__("r10");

    v29 = lbl_80303448;
    fn_80137CB4(&fr.buf);
    v28 = a0->unk0x18;
    t = a0->unk0x0;
    if (fn_8013F764(a0->unk0x10) != 0) {
        if (((Unk_C04093AF *)t)->unk0x1D != 0) {
            fn_8013FB94(a0->unk0x10, 0);
        } else {
            fn_8013FB94(a0->unk0x10, 1);
        }
        ((CScript *)v28)->unk0x1C4 = *(s32 *)t;
        ((CScript *)v28)->unk0x1C8 = ((Unk_C04093AF *)t)->unk0x4;
        fn_8021B54C(v28, ((Unk_C04093AF *)t)->unk0x8);
    }
    fn_80198D08(lbl_80305EC0, (s8)((Unk_C04093AF *)t)->unk0x1C);
    t = 1;
    GetText(fn_8013FF5C(fn_8021E024(v28), (s32)QB_NETWORK_ID), (s32)QB_UI_STRING, &fr.sp1070, 1);
    fr.spC = (fn_802195BC(v28) == 1);
    fr.sp8 = 0x4000B;
    fr.spD = t;
    temp_r3 = fn_80137AD4(v29);
    if (temp_r3 == 1) {
        v27 = 1;
        fr.sp18 = 0;
    } else {
        fr.sp18 = t;
        v27 = 0;
    }
    t = 0;
    strncpy(fr.sp28, *(char **)&fr.sp1070, 0xF);
    {
        s32 z;
        __asm__("li %0,0" : "=r"(z));
        fr.sp28[15] = z;
        fr.spE = z;
    }
    if (fr.spC == 0) {
        v29 = fn_80174AB8(lbl_80305EAC, 0);
        lblv = (s32)lbl_8029F480;
        q = &fr.sp1060[0];
        fr.sp1060[2] = lblv;
        q[1] = t;
        if (fn_8013FB8C(fn_8013E034(a0->unk0xC, q)) == 1) {
            v27 = 1;
        }
        t = fn_801A4B88(v29, fr.sp38, 0x1000, v27);
        fr.sp1060[2] = lblv;
    }
    temp_r3 = a0->unk0x10;
    fr.buf.f4 = (s32)&fr.sp8;
    v30 = t + 0x30;
    fr.buf.f2 = v30;
    fr.buf.f0 = 0x50;
    fr.buf.f20 = 2;
    if (fn_8013F764(temp_r3) != 0) {
        fr.buf.fc = 2;
    }
    fn_8013DE78(a0->unk0xC, &fr.buf);
    fn_8022019C(v28, 2);
    return 4;
}
