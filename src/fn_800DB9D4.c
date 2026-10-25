// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DB9D4-0x800DBA78 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

extern const f32 lbl_80299E6C;
extern const f32 lbl_80299E70;
extern const f32 lbl_80299E74;
extern const f32 lbl_80299E78;
extern char lbl_80299ED0[];

void *fn_8009F53C(void *arg0);

typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} Quad;

typedef struct {
    char pad0[0x4];
    s32 unk4;
    char pad8[0x10];
    s32 unk18;
    char pad1c[0x4];
    Quad q20;
    Quad q30;
    Quad q40;
} BBox;

void *fn_800DB9D4(BBox *arg0) {
    f32 v12;
    f32 v11;
    f32 v13;
    f32 v0;
    Quad *p20;
    Quad *p30;
    Quad *p40;

    fn_8009F53C(arg0);
    v12 = lbl_80299E6C;
    arg0->unk18 = (s32)lbl_80299ED0;
    arg0->unk4 = QB_BBOX;
    v11 = lbl_80299E70;
    p20 = &arg0->q20;
    arg0->q20.a = v12;
    p20->b = v12;
    p20->c = v12;
    p20->d = v11;
    v13 = lbl_80299E74;
    p30 = &arg0->q30;
    arg0->q30.a = v13;
    p30->b = v13;
    p30->c = v13;
    p30->d = v11;
    v0 = lbl_80299E78;
    p40 = &arg0->q40;
    arg0->q40.a = v0;
    p40->b = v0;
    p40->c = v0;
    p40->d = v11;
    return arg0;
}
