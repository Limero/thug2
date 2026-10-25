// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022ACE0-0x8022AE98 (440B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C * obj, s32 val);
extern void fn_8000F320(Unk_F12C5E01 * obj);
extern s32 Mem_NewZero(s32 size);
extern s32 fn_800145AC(void);
extern void *fn_8022B810(void);
extern s32 fn_8022B5D0(s32 arg0, s32 arg1, s32 arg2);
extern void fn_8022BA54(void * arg0, void * arg1, s32 arg2);
extern char *strcpy(char *dst, char *src);

s32 fn_8022ACE0(void *arg0) {
    register s32 f18 __asm__("r27");
    register s32 p __asm__("r28");
    register s32 objv __asm__("r30");
    register s32 head __asm__("r31");
    register s32 a0 __asm__("r29");
    s32 ctr;
    s32 v1;
    s32 v2;
    s32 v3;
    Unk_FFAD6788 *t;
    s32 g;
    s32 t2;
    s32 k14;
    u8 b58;

    a0 = (s32)arg0;
    head = ((Unk_0737AFB8 *)a0)->unk0x0;
    f18 = *((char * *)&((Unk_EC9C414C *)a0)->unk0x18);
    if (((Unk_59AB5482_2 *)a0)->unk0x8 != 0xE0) {
        return 4;
    }
    p = head + 8;
    if (fn_8022B5D0(f18, p,
                    *(s32 *)((char *)((Unk_0737AFB8 *)a0)->unk0x10 + 0x4C)) == 0) {
        goto ok;
    }
    return 4;
ok:
    t = lbl_802FFE98;
    fn_8000F2F8(t, t->unk0x134);
    Mem_NewZero(0xC4);
    objv = (s32)fn_8022B810();
    strcpy((char *)objv + 0x18, (char *)p);
    ((Unk_A4BDF65E *)objv)->unk0x28 =
        *(s32 *)((char *)((Unk_0737AFB8 *)a0)->unk0x10 + 0x4C);
    ((Unk_A4BDF65E *)objv)->unk0x30 =
        fn_800145AC() - ((Unk_40E11C10 *)head)->unk0x5C;
    strcpy((char *)objv + 0x44, (char *)head + 0x18);
    strcpy((char *)objv + 0x64, (char *)head + 0x38);
    ((Unk_A4BDF65E *)objv)->unk0x38 = ((Unk_90ACC040 *)head)->unk0x1;
    v1 = 1;
    ((Unk_A4BDF65E *)objv)->unk0x34 = ((Unk_90ACC040 *)head)->unk0x0;
    ((Unk_A4BDF65E *)objv)->unk0x40 = ((Unk_90ACC040 *)head)->unk0x3;
    ((Unk_A4BDF65E *)objv)->unk0x3C = ((Unk_90ACC040 *)head)->unk0x2;
    if (((Unk_90ACC040 *)head)->unk0x4 == 0) {
        v1 = 0;
    }
    ((Unk_A4BDF65E *)objv)->unk0x84 = v1;
    v2 = 1;
    if (((Unk_90ACC040 *)head)->unk0x5 == 0) {
        v2 = 0;
    }
    ((Unk_A4BDF65E *)objv)->unk0x88 = v2;
    v3 = 1;
    ((Unk_A4BDF65E *)objv)->unk0x90 = ((Unk_40E11C10 *)head)->unk0x6;
    if (((Unk_90ACC040 *)head)->unk0x7 == 0) {
        v3 = 0;
    }
    ((Unk_A4BDF65E *)objv)->unk0x94 = v3;
    k14 = 0x141E;
    ctr = 0;
    p = f18 + 0x190;
    b58 = ((Unk_90ACC040 *)head)->unk0x58;
    ((Unk_A4BDF65E *)objv)->unk0x2C = k14;
    ((Unk_A4BDF65E *)objv)->unk0x8C = b58;
    if (ctr < ((Unk_A4BDF65E *)objv)->unk0x34) {
        head = head + 0x60;
        do {
            fn_8022BA54(objv, head, 0);
            head += 0x10;
            ctr++;
        } while (ctr < ((Unk_A4BDF65E *)objv)->unk0x34);
    }

    ((Unk_A4BDF65E *)objv)->unk0x10 = ((Unk_1D62F22E_2 *)p)->unk0x10;
    ((Unk_A4BDF65E *)objv)->unk0xC = p;
    t2 = ((Unk_1D62F22E_2 *)p)->unk0x10;
    g = lbl_802FFE98;
    __asm__ __volatile__("");
    ((Unk_1D62F22E_2 *)t2)->unk0xC = objv;
    ((Unk_1D62F22E_2 *)p)->unk0x10 = objv;
    fn_8000F320(g);
    return 1;
}
