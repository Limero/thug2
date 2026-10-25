// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80223FA0-0x802241F0 (592B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80303448;
extern s32 lbl_802FFE6C;
s32 fn_8013F764(void *);
s32 fn_8013E2D4(Unk_440CB216 *);
s32 fn_80228568(Unk_9994C3F5 *, s32 *, void *, void *, s32, s32);
s32 fn_8013DEE0(Unk_440CB216 *, s32, s32, void *, s32, s32, s32);
s32 fn_8013BE28(Unk_CA1C78B1 *, s32, s32, s32);
void fn_8013FB94(Unk_72BBAD33 *, s32);
void fn_8013F7F8(Unk_FFAD6788 *, s32);
s32 fn_802198F4(void *);
s32 fn_80137AD4(Unk_F386DC9F *);
s32 fn_80219680(CStruct *);
s32 fn_8021B53C(CScript *);
s32 fn_8021B534(CScript *);
s32 fn_8021B52C(CScript *);
s32 fn_8021E024(void *);
s32 fn_8013FF5C(void *, s32);
s32 GetText(CStruct *, void *, void *, s32);
s32 strncpy(void *, void *, s32);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);

s32 fn_80223FA0(Unk_C8FEE62D *arg0) {
    struct frt {
        union {
            char buf8[0xC];
            s32 vals[3];
        } u8;
        char buf14[0x10];
        u8 f24;
        u8 f25;
        u8 _p26[2];
        struct {
            u8 cmd;
            u8 _p1;
            s16 w2A;
            void *p2C;
            u8 _tail[0x20];
        } sp28;
        u8 rsp50[4];
        u8 f54;
        u8 _p55[3];
        s32 f58;
    } fr;
    void *mgr;
    Unk_A8B25094 *obj;
    void *tmp;
    void *ectx;
    s32 base;
    Unk_1D62F22E *r30;
    s32 be28;
    u8 bval;
    s32 fc;
    s32 gt;

    tmp = *((void * *)&arg0->unk0x10);
    mgr = *((void * *)&arg0->unk0x18);
    obj = *(void **)arg0;
    if (fn_8013F764(tmp) != 0) {
    if ((arg0->unk0x14 & 1) == 0) {
        return 4;
    }
    base = lbl_80303448;
    if (fn_8013E2D4(*((void * *)&arg0->unk0xC)) == 0) {
        return 4;
    }
    r30 = &fr.rsp50[0];
    if (fn_80228568(mgr, r30, obj, *((void * *)&arg0->unk0x10), 1, 1) == 0) {
        fr.f54 = r30->unk0x3;
        fn_8013DEE0(*((void * *)&arg0->unk0xC), 0x47, 1, &fr.f54,
                    ((Unk_04010383 *)arg0->unk0x10)->unk0x4C,
                    ((Unk_04010383 *)arg0->unk0x10)->unk0x50, 0);
        return 2;
    }
    be28 = fn_8013BE28(*((void * *)&arg0->unk0xC),
                       ((Unk_04010383 *)arg0->unk0x10)->unk0x4C,
                       ((Unk_04010383 *)arg0->unk0x10)->unk0x50,
                       2);
    arg0->unk0x10 = be28;
    if (obj->unk0x10 != 0) {
        fn_8013FB94(be28, 0);
        fn_8013F7F8(be28, 0x3E8u / (u32)lbl_802FFE6C * 2);
    } else {
        fn_8013FB94(be28, 1);
        fn_8013F7F8(be28, 0x3E8u / (u32)lbl_802FFE6C * 2);
    }
    fr.f24 = (u8)fn_802198F4(mgr);
    gt = fn_80137AD4(base);
    bval = 1;
    if (gt == 1) {
        bval = 0;
    }
    fr.f25 = bval;
    if (fn_80219680(mgr) != 0) {
        fr.u8.vals[2] = (s32)fn_8021B53C(mgr);
        fr.u8.vals[1] = (s32)fn_8021B534(mgr);
        fr.u8.vals[0] = (s32)fn_8021B52C(mgr);
    }
    { s32 a6; void *a5; s32 t3;
    t3 = fn_8013FF5C(fn_8021E024(mgr), (s32)0x2A5CF019u);
    /* order wedge (non-volatile, operands from C): want li r6 BEFORE
     * addi r5; plain C sinks the addi first. t3 input anchors the window
     * after the nested calls. addi base r1 is ABI-fixed. */
    __asm__("li %0,1\n\taddi %1,1,%3"
            : "=r"(a6), "=r"(a5) : "r"(t3), "i"(0x58));
    GetText(t3, QB_UI_STRING, a5, a6); }
    strncpy(&fr.buf14[0], (void *)fr.f58, 0xF);
    fr.buf14[15] = 0;
    fn_8013DEE0(fc, 0x4F, 0x20, &fr.u8.buf8[0],
                ((Unk_04010383 *)arg0->unk0x10)->unk0x4C,
                ((Unk_04010383 *)arg0->unk0x10)->unk0x50,
                (fc = *((volatile s32 *)&arg0->unk0xC), 0));

    return 1;
    }
    ectx = &fr.sp28;
    fn_80137CB4(ectx);
    fr.f24 = (u8)fn_802198F4(mgr);
    fr.sp28.cmd = 0x4F;
    fr.sp28.p2C = &fr.u8.buf8[0];
    fr.sp28.w2A = 0x20;
    fn_8013CC84(*((void * *)&arg0->unk0xC),
                ((Unk_04010383 *)arg0->unk0x10)->unk0x48,
                ectx);
    return 1;
}
