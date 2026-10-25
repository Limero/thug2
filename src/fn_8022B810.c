// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B810-0x8022B8E8 (216B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B0008[];
extern char lbl_802B0410[];
extern char lbl_802B039C[];

void *fn_8022B810(void *arg0) {
    s32 zero = 0;
    char *o = (char *)arg0;
    Unk_4C649A8C *sub;

    ((Unk_43B2646B *)o)->unk0x14 = (s32)lbl_802B0410;
    ((Unk_43B2646B *)o)->unk0x4 = (s32)arg0;
    ((Unk_43B2646B *)o)->unk0x8 = zero;
    ((Unk_1536091C *)o)->unk0xC = (s32)arg0;
    ((Unk_43B2646B *)o)->unk0x10 = (s32)arg0;

    sub = o + 0xAC;
    sub->unk0x14 = (s32)lbl_802B0008;
    sub->unk0x4 = -1;
    ((Unk_41EA2015 *)sub)->unk0xC = (s32)sub;
    sub->unk0x10 = (s32)sub;
    sub->unk0x8 = zero;

    ((Unk_43B2646B *)o)->unk0x9C = zero;
    ((Unk_1536091C *)o)->unk0xA0 = zero;
    ((Unk_43B2646B *)o)->unk0x30 = zero;

    sprintf(o + 0x44, (s32)lbl_802B039C);
    sprintf(o + 0x64, (s32)lbl_802B039C);

    ((Unk_43B2646B *)o)->unk0x38 = 8;
    ((Unk_43B2646B *)o)->unk0x8C = 2;
    ((Unk_43B2646B *)o)->unk0x34 = 1;
    ((Unk_43B2646B *)o)->unk0x40 = 1;
    ((Unk_43B2646B *)o)->unk0x3C = zero;
    ((Unk_43B2646B *)o)->unk0x98 = 1;
    ((Unk_43B2646B *)o)->unk0x90 = zero;
    ((Unk_43B2646B *)o)->unk0x94 = zero;
    ((Unk_43B2646B *)o)->unk0x88 = zero;
    ((Unk_43B2646B *)o)->unk0xA4 = zero;
    ((Unk_43B2646B *)o)->unk0xA8 = zero;
    return arg0;
}
