// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DA9C-0x8004DC1C (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct { void *f0; void *f4; void *f8; void *fC; } RefNode;
typedef struct { char pad0x0[0x18]; s32 unk0x18; } Elem;

s32 ResolveComplexID(Unk_C7387A53 *, CStruct *, s32, s32);
void GetElement_2(void *, s32, s32, s32);
void CObject_AddRefLink(CStruct *, CStruct *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 fn_8003FFC4(void *);
void fn_8003E7CC(s32);
void *fn_80128F94(void);
void fn_80129068(void *, s32, s32);
void *fn_8003FF64(void *, s32);
void fn_801292A8(void *, s32, s32);
void AddArrayPointer(s32, s32, s32);
extern s32 lbl_80300434;

bool ScriptGetScreenElementChildren(CStruct *pParams, CScript *pScript) {
    RefNode sp8;
    RefNode sp18;
    s32 sp28;
    register RefNode *p __asm__("r11");
    register RefNode *link __asm__("r27");
    CScript *script;
    Unk_C7387A53 *ctx;
    s32 count;
    s32 i;
    void *o;
    void *arr;

    p = &sp8;
    ctx = lbl_80300434;
    script = pScript;
    __asm__("" : "+r"(script));
    p->f4 = 0;
    p->f8 = 0;
    sp8.f0 = 0;
    __asm__("" : "+r"(p));
    link = p;
    if (ResolveComplexID(ctx, pParams, QB_ID, &sp28) != 0) {
        GetElement_2(&sp18, ctx, sp28, 1);
        o = sp18.f0;
        if (sp8.f0 != 0) {
            CObject_RemoveRefLink(sp8.f0, link);
            sp8.f0 = 0;
        }
        sp8.f0 = o;
        if (o != 0) {
            CObject_AddRefLink(o, link);
        }
        if (sp18.f0 != 0) {
            CObject_RemoveRefLink(sp18.f0, &sp18);
            sp18.f0 = 0;
        }
    }
    count = fn_8003FFC4(sp8.f0);
    if (count == 0) {
        if (sp8.f0 != 0) {
            CObject_RemoveRefLink(sp8.f0, link);
            sp8.f0 = 0;
        }
        return false;
    }
    fn_8003E7CC(0xC);
    i = 0;
    arr = fn_80128F94();
    fn_80129068(arr, count, 0xD);
    for (i = 0; i < count; i++) {
        fn_801292A8(arr, i, ((Elem *)fn_8003FF64(sp8.f0, i))->unk0x18);
    }
    AddArrayPointer(script->unk0x18, QB_CHILDREN, (s32)arr);
    if (sp8.f0 != 0) {
        CObject_RemoveRefLink(sp8.f0, link);
        sp8.f0 = 0;
    }
    return true;
}
