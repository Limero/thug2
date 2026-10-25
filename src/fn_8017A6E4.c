// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017A6E4-0x8017A79C (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EC0;
extern s32 lbl_80305F1C;
extern s32 lbl_80305F9C;
extern s32 fn_8021F6CC(Unk_2EC243AC *);
extern s32 fn_80198B10(s32);
extern s32 fn_8021D358(s32, s32);
extern void fn_801A9270(s32, s32, s32);

s32 fn_8017A6E4(void **arg0) {
    Unk_2A7B74AF *t;
    s32 g;
    s32 v;
    u32 i;
    s32 tag;

    t = *arg0;
    g = lbl_80305F9C;
    tag = fn_8021F6CC(g);
    if (t->unk0x0 != tag) {
        return 4;
    }
    if (fn_80198B10(lbl_80305EC0) != 0) {
        v = *(s32 *)((char *)fn_8021D358(g, ((Unk_32A87CFA *)t)->unk0x6) + 0x34);
    } else {
        v = t->unk0x4;
    }
    for (i = 0; i < t->unk0x8; i++) {
        fn_801A9270(lbl_80305F1C, *(s32 *)((char *)t + 0xC + i * 4), v);
    }
    return 1;
}
