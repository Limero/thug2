// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800423F0-0x800426EC (764B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802924A0;
void CScreenElement_SetProperties();
s32 GetChecksum_2(void *, u32, void *, s32);
void fn_80042768(void *, s32);
s32 GetFloat(void *, u32, f32 *, s32);
void fn_80042924(void *, s32, f32);
s32 CScreenElement_resolve_just(void *, void *, u32, void *, void *);
s32 GetText(void *, u32, void *, s32);
void fn_800427AC(void *, s32);
s32 ContainsFlag(void *, u32);
void CTextElement_AttachBlurEffect(void *);
void CTextElement_DetachBlurEffect(void *);
s32 CScreenElement_resolve_rgba(void *, void *, u32, void *);
void fn_80125000(void *);
s32 GetPair(void *, u32, void *, s32);
void fn_80042F38(void *, f32, f32);
void CTextElement_SetShadowState(void *, s32);
s32 GetArray(void *, u32, void *, s32);
void fn_80042AFC(void *, s32);
void fn_800439B0(void *);

// fn_80125000 writes a byte at +1 and f32s at +4 / +8 of this 12-byte value,
// which GetPair then overwrites in place and fn_80042F38 consumes as f1/f2.
typedef struct {
    s32 unk0x0;
    f32 x;
    f32 y;
} ShadowOffs;

void CTextElement_SetProperties(Unk_5F7A3D4C *arg0, CStruct *arg1) {
    s32 sp28;
    s32 sp24;
    s32 sp20;
    f32 sp1C;
    s32 sp18;
    ShadowOffs shadow_ofs;

    CScreenElement_SetProperties();
    if (GetChecksum_2(arg1, QB_FONT, &sp18, 0) != 0) {
        fn_80042768(arg0, sp18);
    }
    sp1C = lbl_802924A0;
    if (GetFloat(arg1, QB_ROT_ANGLE, &sp1C, 0) != 0) {
        fn_80042924(arg0, 1, sp1C);
    }
    if (CScreenElement_resolve_just(arg0, arg1, QB_INTERNAL_JUST, (char *)arg0 + 0x1C8, (char *)arg0 + 0x1CC) != 0) {
        arg0->unk0xC = arg0->unk0xC | 0x1000;
    }
    if (GetText(arg1, QB_TEXT, &sp20, 0) != 0) {
        fn_800427AC(arg0, sp20);
    }
    if (ContainsFlag(arg1, QB_BLUR_EFFECT) != 0) {
        CTextElement_AttachBlurEffect(arg0);
    }
    if (ContainsFlag(arg1, QB_NO_BLUR_EFFECT) != 0) {
        CTextElement_DetachBlurEffect(arg0);
    }
    if (CScreenElement_resolve_rgba(arg0, arg1, QB_BLUR_RGBA, &sp24) != 0) {
        if (arg0->unk0x1A8 != NULL) {
            arg0->unk0x1A8->unk0x4B8 = sp24;
        }
    }
    fn_80125000(&shadow_ofs);
    if (GetPair(arg1, QB_SHADOW_OFFS, &shadow_ofs, 0) != 0) {
        fn_80042F38(arg0, shadow_ofs.x, shadow_ofs.y);
    }
    if (ContainsFlag(arg1, QB_SHADOW) != 0) {
        CTextElement_SetShadowState(arg0, 1);
    }
    if (ContainsFlag(arg1, QB_NO_SHADOW) != 0) {
        CTextElement_SetShadowState(arg0, 0);
    }
    CScreenElement_resolve_rgba(arg0, arg1, QB_SHADOW_RGBA, (char *)arg0 + 0x1B8);
    if (ContainsFlag(arg1, QB_REMEMBER_OVERRIDE_RGBA_STATE) != 0) {
        arg0->unk0x1C0 = arg0->unk0x1BC;
    }
    if (ContainsFlag(arg1, QB_RESTORE_OVERRIDE_RGBA_STATE) != 0) {
        arg0->unk0x1BC = arg0->unk0x1C0;
    }
    if (ContainsFlag(arg1, QB_OVERRIDE_ENCODED_RGBA) != 0) {
        arg0->unk0x1BC = 1;
    }
    if (ContainsFlag(arg1, QB_DONT_OVERRIDE_ENCODED_RGBA) != 0) {
        arg0->unk0x1BC = 0;
    }
    if (ContainsFlag(arg1, QB_OVERRIDE_ENCODED_ALPHA) != 0) {
        arg0->unk0x1C4 = 1;
    }
    if (ContainsFlag(arg1, QB_DONT_OVERRIDE_ENCODED_ALPHA) != 0) {
        arg0->unk0x1C4 = 0;
    }
    sp28 = 0;
    if (GetArray(arg1, QB_CHAR_INFO, &sp28, 0) != 0) {
        fn_80042AFC(arg0, sp28);
    }
    fn_800439B0(arg0);
}
