// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6578-0x800B6634 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0x210];
    s32 unk0x210;
    char pad0x214[0x20];
    f32 unk0x234;
} Unk_800B6578;

s32  fn_80107D30(void *);
f32  fn_80107D7C(void *);
s32  fn_80060DE4(s32);
void fn_8005B5FC(s32, f32, f32);
s32  fn_8005B65C(s32, f32);
void fn_8005955C(f32);

extern f32 lbl_802988D8;
extern f32 lbl_802988DC;

void fn_800B6578(Unk_800B6578 *arg0, void *arg1, s32 arg2, f32 farg0) {
    volatile double _dummy;
    s32 t;
    f32 v;

    if (fn_80107D30(arg1) != 0) {
        t = fn_80060DE4(arg0->unk0x210);
        if (t != 0) {
            v = fn_80107D7C(arg1);
            v = 2.0f * v;
            arg0->unk0x234 = v;
            if (arg2 != 0) {
                fn_8005B5FC(t, v * lbl_802988D8, farg0 * lbl_802988DC);
            } else {
                fn_8005B65C(t, v * lbl_802988D8);
            }
        } else {
            fn_8005955C(fn_80107D7C(arg1));
        }
    }
}
