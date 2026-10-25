// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130898-0x801309EC (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CStruct_delete(CStruct *, s32);
void fn_801347CC(CScript *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern CScript* lbl_8030342C;

typedef union {
    u32 w;
    struct { u32 b31:1; u32 rest:31; } bf;
} B4_t;

typedef struct {
    char pad0x00[0x10];
    s32 f10;
    char pad0x14[0x4];
    CStruct *f18;
    s32 f1C;
    char pad0x20[0x18];
    s32 f38;
    char pad0x3C[0x58];
    s32 f94;
    s32 f98;
    s32 f9C;
    f32 fA0;
    s32 fA4;
    s32 fA8;
    s32 fAC;
    char pad0xB0[0x4];
    B4_t fB4;
    char pad0xB8[0x4];
    CStruct *fBC;
    char pad0xC0[0x8];
    s32 fC8;
    char pad0xCC[0x1C];
    s32 fE8;
} Obj_t;

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    void *f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    s32 f24;
    u32 f28;
} Rec_t;

u32 fn_80130898(Obj_t *arg0, CStruct *arg1) {
    Rec_t *rec;
    s32 off;
    register s32 bse __asm__("r11");
    void *old;
    void *link;
    char *p28;
    s32 t0;
    u32 ret;

    fn_801347CC(lbl_8030342C, arg0->fC8);
    off = arg0->f38;
    ret = arg0->fB4.w >> 0x1F;
    if (off != 0) {
        arg0->f38 = off - 1;
        if (arg0->f18 != 0) {
            CStruct_delete(arg0->f18, 3);
        }
        off = arg0->f38;
        p28 = (char *)arg0 + 0xBC;
        bse = arg0->f94;
        off = off * 0x2C;
        old = (void *)arg0->fBC;
        arg0->fC8 = *(s32 *)((char *)bse + off);
        rec = (Rec_t *)((char *)bse + off);
        arg0->f18 = (CStruct *)rec->f04;
        arg0->f10 = rec->f08;
        link = rec->f0C;
        if (old != 0) {
            CObject_RemoveRefLink((CStruct *)old, (CStruct *)p28);
            arg0->fBC = 0;
        }
        arg0->fBC = (CStruct *)link;
        if (link != 0) {
            CObject_AddRefLink((CStruct *)link, (Unk_9994C3F5 *)p28);
        }
        arg0->f1C = rec->f10;
        arg0->fE8 = rec->f14;
        t0 = (s32) (rec->f28 >> 0x1C);
        arg0->fA4 = t0;
        if (t0 != 0) {
            arg0->f98 = rec->f24;
            arg0->fA0 = rec->f1C;
            arg0->f9C = (s32) ((rec->f28 >> 0x1B) & 1);
            arg0->fAC = rec->f18;
            arg0->fA8 = rec->f20;
        }
        arg0->fB4.bf.b31 = (rec->f28 >> 0x1A) & 1;
    } else {
        arg0->f10 = off;
    }
    if (arg1 != 0) {
        fn_80126FF4((Unk_80577C09 *)arg0->f18, arg1);
    }
    return ret;
}
