// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044ADC-0x80044C64 (392B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Elem_t {
    char pad0x0[0x70];
    struct Elem_t *next; /* 0x70: sibling element in the list      */
    char pad0x74[0x108];
    f32 unk0x17C; /* 0x17C: measured width of this element */
} Elem_t;

typedef struct Sub81 {
    char pad0x0[0x40];
    s32 color;
} Sub81;

typedef struct Ref {
    Elem_t *sp8;
    s32 u0C;
    s32 u10;
    s32 dummy;
} Ref;

typedef struct Obj_t {
    char pad0x0[0xC];
    s32 flags;  /* 0x0C: bit 0x1000 enables the relayout pass */
    char pad0x10[0x54];
    Elem_t *first; /* 0x64: head of the element list         */
    char pad0x68[0x60];
    s32 unk0xC8;  /* 0xC8: gradient colour handed to CScreenElement_SetRGBA */
    char pad0xCC[0xAC];
    f32 unk0x178; /* 0x178 */
    f32 unk0x17C; /* 0x17C: max usable width               */
    char pad0x180[0x2C];
    f32 unk0x1AC; /* 0x1AC */
    f32 unk0x1B0; /* 0x1B0 */
    f32 unk0x1B4; /* 0x1B4 */
    f32 unk0x1B8; /* 0x1B8 */
    f32 unk0x1BC; /* 0x1BC */
    s32 unk0x1C0; /* 0x1C0: number of relayout passes       */
    char pad0x1C4[0x40];
} Obj_t;

typedef struct Loc {
    Elem_t *sp8; /* +0x08 current element                       */
    s32 unk0C;   /* +0x0C ref-link word, cleared by this function */
    s32 unk10;   /* +0x10 ref-link word, cleared by this function */
    s32 color;   /* +0x18 out-param for CScreenElement_SetRGBA             */
    char pad14[0x24];
} Loc;

void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void CScreenElement_SetPos(void *, f32, f32, s32);
void CScreenElement_SetJust(void *, f32, f32);
void CScreenElement_SetRGBA(Elem_t *, s32 *, s32);
void fn_80044C64(Obj_t *);

extern const f32 lbl_80292520;
extern const f32 lbl_80292524;
extern const f32 lbl_80292528;

void fn_80044ADC(Obj_t *arg0) {
    Ref reflink;
    s32 color;
    s32 i;
    f32 f29;
    f32 f30;
    f32 f31;
    Elem_t *next;
    Sub81 *sub81;
    register Ref *lockR __asm__("r28");
    Ref *sb;
    s32 pad1, pad2, pad3, pad4, pad5;
    s32 pad6, pad7;

    if (arg0->flags & 0x1000) {
        f29 = lbl_80292520;
        f30 = lbl_80292524;
        f31 = (arg0->unk0x1B0 + f29) * (arg0->unk0x17C - arg0->unk0x1BC) * f30;
        sb = &reflink;
        sb->u0C = 0;
        sb->u10 = 0;
        lockR = sb;
        reflink.sp8 = arg0->first;
        if (reflink.sp8 != NULL) {
            CObject_AddRefLink(reflink.sp8, lockR);
        }
        for (i = 0; i < arg0->unk0x1C0; i++) {
            CScreenElement_SetJust(reflink.sp8, arg0->unk0x1AC, lbl_80292528);
        sub81 = (Sub81 *)((char *)arg0 + 0x88);
            color = sub81->color;
            CScreenElement_SetRGBA(reflink.sp8, &color, 1);
            CScreenElement_SetPos(reflink.sp8,
                        (arg0->unk0x1AC + f29) * arg0->unk0x178 * f30, f31, 0);
            next = reflink.sp8->next;
            f31 += reflink.sp8->unk0x17C * arg0->unk0x1B4 * arg0->unk0x1B8;
            if (reflink.sp8 != NULL) {
                CObject_RemoveRefLink(reflink.sp8, lockR);
                reflink.sp8 = NULL;
            }
            reflink.sp8 = next;
            if (next != NULL) {
                CObject_AddRefLink(next, lockR);
            }
        }
        fn_80044C64(arg0);
        if (reflink.sp8 != NULL) {
            CObject_RemoveRefLink(reflink.sp8, lockR);
            reflink.sp8 = NULL;
        }
    }
    /* Frame padding: the want's local area runs to +0x3B with nothing in it
       above the colour word.  Referenced-only so ngccc gives each a slot. */
    __asm__("" : : "m"(pad1), "m"(pad2), "m"(pad3), "m"(pad4), "m"(pad5));
    __asm__(""
            : : "m"(pad6), "m"(pad7));
}
