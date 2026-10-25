// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80045FA8-0x8004602C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8003F608(void *, s32);
void fn_8004602C(void *);
extern char lbl_80292870[];
void CObject_RemoveRefLink(CStruct *, CStruct *);

// One 0x20-byte embedded element: a ref-link at +0x00 and four f32s at
// +0x10..+0x1C (see the matched sibling src/fn_8004602C.c, which writes them).
typedef struct Unk_45FA8_Elem {
    s32 unk0x0;
    char pad0x4[0xC];
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
} Unk_45FA8_Elem;

// The owning object: vtable slot at +0x08, 25 elements at +0x190, count word
// at +0x4B0.  The corpus class Unk_9994C3F5 stops at 0x168 and cannot be used.
typedef struct Unk_45FA8_Obj {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0x184];
    Unk_45FA8_Elem elems[25];
    s32 unk0x4B0;
} Unk_45FA8_Obj;

void fn_80045FA8(Unk_45FA8_Obj *arg0, s32 arg1) {
    Unk_45FA8_Elem *p;
    s32 v;

    arg0->unk0x8 = (s32)lbl_80292870;
    fn_8004602C(arg0);
    if (&arg0->elems[0] != NULL) {
        p = (Unk_45FA8_Elem *)((char *)arg0 + 0x4B0);
        if (&arg0->elems[0] != p) {
            do {
                p--;
                v = p->unk0x0;
                if (v != 0) {
                    CObject_RemoveRefLink((CStruct *)v, (CStruct *)p);
                    p->unk0x0 = 0;
                }
                /* Recomputed (not a shared local) on purpose — see the header. */
            } while (&arg0->elems[0] != p);
        }
    }
    fn_8003F608(arg0, arg1);
}
