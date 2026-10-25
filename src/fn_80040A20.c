// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80040A20-0x80040BE8 (456B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_80300434;
#include "qb_constants.h"
s32 GetFloat(void *, s32, f32 *, s32);
s32 fn_8009EE2C(void *, s32, s32, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void CScreenElement_SetChildLockState(void *, s32);
void fn_8004ADC8(void *, s32, s32, s32, void *);
void fn_80130C6C(void *, s32);

typedef struct Sub {
    u8 pad0x0[0x10];
    s16 unk0x10;
    s16 pad0x12;
    void (*unk0x14)(u8 *, s32);
    u8 pad0x18[0x30];
    s16 unk0x48;
    s16 pad0x4a;
    void (*unk0x4c)(u8 *, s32);
    s16 unk0x50;
    s16 pad0x52;
    void (*unk0x54)(u8 *, s32);
} Sub;
typedef struct Obj {
    u8 pad0x0[8];
    Sub *unk0x8;
    u8 pad0xc[0xc];
    s32 unk0x18;
    u8 pad0x1c[0x3c];
    void *unk0x58;
} Obj;
typedef struct TSp8 {
    void *p;
    s32 a;
    s32 b;
} TSp8;

// CScreenElement_CallMemberFunction @ 0x80040A20
s32 CScreenElement_CallMemberFunction(Obj *arg0, s32 arg1, s32 arg2, void *arg3) {
    TSp8 sp8;
    f32 sp18;
    Sub *sub;

    if (arg1 == 0x6C63C7C5) {
        sub = arg0->unk0x8;
        sub->unk0x14((u8 *)arg0 + sub->unk0x10, arg2);
    } else if (arg1 == QB_DOMORPH) {
        if (GetFloat(arg2, 0x906B67BA, &sp18, 0) != 0) {
            fn_80130C6C(arg3, (u32)(sp18 * 1000.0f));
        }
        sub = arg0->unk0x8;
        sub->unk0x54((u8 *)arg0 + sub->unk0x50, arg2);
    } else if (arg1 == 0xC6870028) {
        TSp8 *sp = &sp8;
        void *g = lbl_80300434;
        sp->a = 0;
        sp->b = 0;
        sp->p = arg0->unk0x58;
        if (sp->p) {
            CObject_AddRefLink(sp->p, sp);
        }
        CScreenElement_SetChildLockState(sp->p, 0);
        fn_8004ADC8(g, arg0->unk0x18, 1, 0, arg3);
        CScreenElement_SetChildLockState(sp->p, 1);
        if (sp->p) {
            CObject_RemoveRefLink(sp->p, sp);
            sp->p = 0;
        }
    } else if (arg1 == 0x9492F814) {
        sub = arg0->unk0x8;
        sub->unk0x4c((u8 *)arg0 + sub->unk0x48, *(s32 *)((u8 *)arg3 + 0x18));
    } else {
        return fn_8009EE2C(arg0, arg1, arg2, arg3);
    }
    return 1;
}
