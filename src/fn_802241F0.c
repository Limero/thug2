// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802241F0-0x80224438 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EAC;
extern s32 lbl_80305EC0;
s32 fn_8022AA50(Unk_A9157FE7 *);
s32 fn_8013F764(void *);
s32 fn_80228568(Unk_9994C3F5 *, s32 *, void *, void *, s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
void fn_8013F6E4(Unk_FFAD6788 *);
void fn_8022AABC(Unk_31DE137E *, s32);
s32 strncpy(void *, void *, s32);
s32 fn_8021D184(void *);
s32 fn_80198F7C(void *);
s32 fn_80220484(Unk_C7387A53 *);
s32 fn_8013F74C(void *);
void *Mem_Alloc(s32);
s32 fn_80174AB8(void *, s32);
s32 fn_801A4B88(Unk_31DE137E *, void *, s32, s32);
void fn_801A4C68(Unk_31DE137E *, void *);
s32 Mem_Free(void *);
void fn_8021C4FC(CStruct *, Unk_A1F83658 *, s32);

struct ctx241 {
    u8 pad0;
    char name[0xF];
    u8 b10;
    s8 b11;
    u8 _12[2];
    s32 f14;
    u8 _18[4];
    s32 f1C;
    s32 f20;
    s32 _24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 _3C;
    s32 f40;
};

s32 fn_802241F0(Unk_DB0E2BAB *arg0) {
    struct frt {
        struct ctx241 c;
        u8 _pad44[4];
        union {
            struct {
                u8 cmd;
                u8 _p1;
                s16 w52;
                void *p54;
                u8 _tail[0x20];
            } e50;
            volatile s32 cnt50;
        } u50;
        u8 rsp78[4];
        u8 sp7C;
    } fr;
    s32 base;
    s32 one;
    void *mgr;
    Unk_71EAD930 *obj;
    void *e50;
    u8 b;
    register void *out78 __asm__("r29");

    base = lbl_80305EAC;
    one = 1;
    fn_8022AA50(&fr.c);
    *((s32 *)&arg0->unk0xA0) = one;
    mgr = *((void * *)&arg0->unk0x18);
    obj = *(void **)arg0;
    if (fn_8013F764(*((void * *)&arg0->unk0x10)) != 0 &&
        (out78 = &fr.rsp78[0],
         fn_80228568(mgr, out78, obj, *((void * *)&arg0->unk0x10),
                     0, 0) == 0)) {
        e50 = &fr.u50.e50;
        fn_80137CB4(e50);
        b = ((Unk_1D62F22E *)out78)->unk0x3;
        fr.u50.e50.p54 = (void *)&fr.sp7C;
        fr.u50.e50.w52 = one;
        fr.sp7C = b;
        fr.u50.e50.cmd = 0x47;
        fn_8013CC84(*((void * *)&arg0->unk0xC),
                    ((CStruct *)arg0->unk0x10)->unk0x48,
                    e50);
        fn_8013F6E4(*((void * *)&arg0->unk0x10));
        fn_8022AABC(&fr.c, 2);
        return 2;
    }
    strncpy(&fr.c.name[0], (char *)obj + 0x20, 0xF);
    fr.c.b10 = 0;
    fr.c.b11 = (u8)fn_8021D184(mgr);
    fr.c.f14 = arg0->unk0x10;
    fr.c.f20 = 0;
    fr.c.f2C = obj->unk0x14;
    fr.c.f30 = obj->unk0x18;
    fr.c.f40 = obj->unk0x1C;
    fr.c.f34 = 0;
    if (obj->unk0x4 != 0) {
        fr.c.f20 = 4;
    } else {
        if (fn_80198F7C((void *)lbl_80305EC0) != (s32)QB_NETLOBBY) {
            if (fn_80220484(mgr) == 0) {
                fr.c.f20 |= 0xC;
            }
        }
    }
    if (fn_8013F74C(*((void * *)&arg0->unk0x10)) != 0) {
        void *p = Mem_Alloc(0x1000);
        fn_801A4B88(fn_80174AB8(base, fr.c.b11), p, 0x1000, 0);
        fn_801A4C68(fr.c.f1C, p);
        Mem_Free(p);
        fr.c.f20 = 1;
        fn_8021C4FC(mgr, &fr.c, 0);
    } else {
        if (obj->unk0x4 == 0) {
            fn_801A4C68(fr.c.f1C, (char *)obj + 0x30);
        }
        fn_8021C4FC(mgr, &fr.c, 0xA);
        fr.u50.cnt50 = 1;
        ((CStruct *)arg0->unk0x10)->unk0x68 =
            ((CStruct *)arg0->unk0x10)->unk0x68 & ~1;
        fr.u50.cnt50 = 2;
        ((CStruct *)arg0->unk0x10)->unk0x68 =
            ((CStruct *)arg0->unk0x10)->unk0x68 | 2;
    }
    fn_8022AABC(&fr.c, 2);
    return 1;
}
