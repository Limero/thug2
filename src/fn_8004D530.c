// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004D530-0x8004D704 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80300434[];
extern char lbl_80301A78[];

/* 12-byte object reference: {object, refcount, flags}. Layout proven by the
   promoted callee GetElement_2 (src/GetElement_2.c), which zero-fills f4/f8 and
   then stores the object into f0 of its out-param. */
typedef struct { void *f0; s32 f4; s32 f8; } Ref_t;

s32 ResolveComplexID(CStruct *, CStruct *, s32, void *);
void *GetElement_2(Ref_t *, CStruct *, s32, s32);
s32 fn_800A5308(CStruct *, s32);
void CObject_AddRefLink(CStruct *, Ref_t *);
void CObject_RemoveRefLink(CStruct *, Ref_t *);
void fn_8012772C(CStruct *, s32, f32);
s32 ContainsFlag(CStruct *, s32);

bool ScriptGetScreenElementProps(CStruct *arg0, CScript *arg1) {
    Ref_t sp8;                            /* r1+0x08, 12 bytes */
    Ref_t sp18;                           /* r1+0x18, 12 bytes */
    s32 sp28;                             /* r1+0x28 */
    s32 temp_r30;
    s32 temp_r3;
    Unk_C8FEE62D *temp_r9;
    register Ref_t *p8 __asm__("r26");    /* want's home copy of &sp8 */
    register CScript *a1 __asm__("r29");  /* want's arg1 home */
    Ref_t *t8;
    s32 zero;

    a1 = arg1;
    zero = 0;
    t8 = &sp8;                            /* volatile scratch for the stores */
    t8->f4 = zero;
    t8->f8 = zero;
    p8 = t8;                              /* want's `mr r26, r9` */
    temp_r30 = *(s32 *)&lbl_80300434;     /* screen-element registry */
    sp8.f0 = (void *)zero;
    if (ResolveComplexID((CStruct *)temp_r30, arg0, QB_ID, &sp28) != 0) {
        GetElement_2(&sp18, (CStruct *)temp_r30, sp28, 0);
        temp_r30 = (s32)sp18.f0;
        if (sp8.f0 != NULL) {            /* drop any previous reference */
            CObject_RemoveRefLink(sp8.f0, p8);
            sp8.f0 = (void *)zero;
        }
        sp8.f0 = (void *)temp_r30;
        if (temp_r30 != 0) {             /* take a reference for ourselves */
            CObject_AddRefLink((CStruct *)temp_r30, p8);
        }
        if (sp18.f0 != NULL) {           /* release the out-param's own ref */
            CObject_RemoveRefLink(sp18.f0, &sp18);
            sp18.f0 = (void *)zero;
        }
    }
    temp_r30 = (s32)sp8.f0;
    if (temp_r30 != 0) {
        temp_r9 = *(Unk_C8FEE62D **)((char *)temp_r30 + 8);
        /* virtual: se->Setup(arg) at the s16 object offset stored in the vtable */
        ((void (*)(void *, void *))temp_r9->unk0x4C)(
            (void *)((char *)temp_r30 + *(s16 *)((char *)temp_r9 + 0x48)),
            (void *)a1->unk0x18);
        if (((Unk_C8FEE62D *)sp8.f0)->unk0x1C == QB_ELEMENT3D) {
            /* a 3D element caches its euler angles on the screen element */
            temp_r3 = fn_800A5308(*(s32 *)&lbl_80301A78, sp28);
            fn_8012772C((CStruct *)a1->unk0x18, QB_ANGLEX, *(f32 *)((char *)temp_r3 + 0x4B8));
            fn_8012772C((CStruct *)a1->unk0x18, QB_ANGLEY, *(f32 *)((char *)temp_r3 + 0x4BC));
            fn_8012772C((CStruct *)a1->unk0x18, QB_ANGLEZ, *(f32 *)((char *)temp_r3 + 0x4C0));
        }
        if (sp8.f0 != NULL) {
            CObject_RemoveRefLink(sp8.f0, p8);
            sp8.f0 = NULL;                /* want's fresh `li r0, 0` */
        }
        return true;
    }
    /* nothing bound: assert unless the script opted out */
    zero = ContainsFlag(arg0, QB_DONT_ASSERT);
    if (zero != 0) {
        if (sp8.f0 != NULL) {
            CObject_RemoveRefLink(sp8.f0, p8);
            sp8.f0 = (void *)temp_r30;
        }
    } else {
        if (sp8.f0 != NULL) {
            CObject_RemoveRefLink(sp8.f0, p8);
            sp8.f0 = (void *)zero;
        }
    }
    return false;
}
