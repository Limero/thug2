// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F7500-0x801F75E0 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AE3AC;
extern f32 lbl_802AE3B0;
extern s32 fn_801F4628(Unk_13D0EFB0 *, f32 *, f32 *, f32 *);
extern s32 CStruct_ctor(void *);
extern void fn_8012788C(CStruct *, u32, f32, f32, f32);
extern void fn_8012772C(CStruct *, u32, f32);
extern void Script_RunScript(u32, void *, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);

register s32 g31 __asm__("r31");

bool fn_801F7500(Unk_F0C166E4 *arg0) {
    f32 quad[4];
    s64 sp18;
    f32 sp20;
    f32 sp24;
    s32 fld = arg0->unk0xAC00;

    if (fld != 0) {
        f32 a, b;
        f32 *q, *h;
        a = lbl_802AE3AC;
        q = quad;
        b = lbl_802AE3B0;
        h = &sp18;

        quad[0] = a;
        q[3] = b;
        q[1] = a;
        q[2] = a;
        sp24 = a;
        sp20 = a;
        fn_801F4628(fld, q, &sp20, &sp24);
        CStruct_ctor(h);
        fn_8012788C((s32)h, QB_POS, quad[0], quad[1] + sp20, q[2]);
        fn_8012772C((s32)h, QB_ANGLE, sp24);
        Script_RunScript(QB_GOAL_EDITOR_UPDATE_CURSOR_POSITION, h, 0, 0, 0);
        CStruct_delete((s32)h, 2);
    }
    return true;
}
