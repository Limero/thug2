// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80139450-0x801394C0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029F2E8[];
extern char lbl_8029F2C0[];
void fn_8013B76C(void *);
void fn_8013B4FC(void);
void *Mem_NewZero(s32);
void fn_80009B04(s32, s32);
typedef struct { u8 _0[0x18]; s32 unk18; s32 unk1C; void *unk20; } Obj;
typedef struct { u8 _0[0x1838]; void *unk1838; u8 _b[0xAC4]; s32 unk2300; } S;
void *fn_80139450(S *arg0) {
    Obj *t;
    s32 fnp;

    fn_8013B76C(arg0);
    arg0->unk2300 = (s32)lbl_8029F2E8;
    t = (Obj *)Mem_NewZero(0x24);
    fnp = (s32)fn_8013B4FC;
    fn_80009B04((s32)t, -0x7D0);
    t->unk1C = fnp;
    t->unk20 = arg0;
    t->unk18 = (s32)lbl_8029F2C0;
    arg0->unk1838 = t;
    return arg0;
}
