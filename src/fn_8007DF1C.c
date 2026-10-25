// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007DF1C-0x8007DFC0 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x0[0xD0];
    void *unk0xD0;
} DF1C;
extern void fn_800577A0(void *);
extern s32 fn_800577B4(void *, s32 *);
extern s32 fn_80057CA0(void *);
extern void fn_8007EAE8(void *);
extern s32 fn_8007EC1C(void *, s32);
extern s32 fn_8007DF14(DF1C *);
extern void fn_8009951C(s32);
extern void fn_800997BC(s32);
void fn_8007DF1C(DF1C *arg0) {
    void *temp_r3;
    void *temp_r3_2;
    void *v;

    fn_800577A0(arg0->unk0xD0);
    for (temp_r3 = fn_800577B4(arg0->unk0xD0, 0); temp_r3 != 0;
         temp_r3 = fn_800577B4(arg0->unk0xD0, 0)) {
        v = fn_80057CA0(temp_r3);
        fn_8007EAE8(v);
        fn_8007EC1C(v, 1);
    }
    fn_8009951C(fn_8007DF14(arg0));
    fn_800577A0(arg0->unk0xD0);
    for (temp_r3_2 = fn_800577B4(arg0->unk0xD0, 0); temp_r3_2 != 0;
         temp_r3_2 = fn_800577B4(arg0->unk0xD0, 0)) {
        fn_8007EC1C(fn_80057CA0(temp_r3_2), 0);
    }
    fn_800997BC(fn_8007DF14(arg0));
}
