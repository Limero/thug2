// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010C86C-0x8010C8BC (80B). Byte-identical.
#include "types.h"
#include "structs.h"

extern f32 lbl_8029CE24;
extern s32 lbl_80302C34;
extern void fn_8010C6C0(CStruct *, Unk_01476648 *);
extern s32 fn_8011A2AC(void *, void *, s32, f32, s32, f32, s32, f32);

void fn_8010C86C(CStruct *arg0) {
    char ctx[0x84];

    fn_8010C6C0(arg0, ctx);
    fn_8011A2AC(lbl_80302C34, ctx, 0, lbl_8029CE24, 1, *((f32 *)&((Unk_FFAD6788 *)ctx)->unk0x7C), 0, *((f32 *)&((Unk_FFAD6788 *)ctx)->unk0x80));
}
