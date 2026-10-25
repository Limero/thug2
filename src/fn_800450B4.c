// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800450B4-0x80045170 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// The receiver is the same object the promoted sibling src/fn_8004DC78.c calls
// Unk_4313CFEA, but that merged class has no 0xC member (it sits inside
// pad0xC[0x184]) and calls 0x198 an s32, so this file carries the real layout
// for the three slots it touches (see M6.89d-note: a shared Unk_* class's field
// type is the corpus-majority vote, not this function's truth).
typedef struct S450B4 {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x180];
    s32 unk0x190;
    s32 unk0x194;
    Unk_838B6CE3 * unk0x198;
} S450B4;

s32 fn_8005CF80(Unk_9994C3F5 *, s32);
u32 fn_8005C5BC(void *);
u32 fn_8005C5F0(void *);
void fn_8005E660(Unk_838B6CE3 *, void *);
void fn_8003F93C(S450B4 *, s32, f32, f32);
extern Unk_9994C3F5 *lbl_80366474;

void fn_800450B4(S450B4 *arg0, s32 arg1) {
    volatile double _dummy;
    volatile double _dummy1;
    Unk_838B6CE3 *handle;
    f32 temp_f31;

    arg0->unk0x190 = arg1;
    handle = (Unk_838B6CE3 *)fn_8005CF80(lbl_80366474, arg1);
    fn_8005E660(arg0->unk0x198, handle);
    temp_f31 = (f32) (f64) (u32) fn_8005C5BC(handle);
    fn_8003F93C(arg0, 0, temp_f31, (f32) (f64) (u32) fn_8005C5F0(handle));
    arg0->unk0xC = arg0->unk0xC | 0x1000;
}
