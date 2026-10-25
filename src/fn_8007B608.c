// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B608-0x8007B738 (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// The destination object lives at arg0->unk0x50 and is a different struct from
// arg0: f32 at 0x18/0x1C/0x24/0x28/0x2C/0x30/0x34, u16 at 0x20/0x22, s32 at
// 0x14/0x38/0x3C/0x40.
typedef struct Dst_8007B608 {
    char pad0x00[0x14];
    s32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    u16 unk0x20;
    u16 unk0x22;
    f32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
    f32 unk0x30;
    f32 unk0x34;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
} Dst_8007B608;

extern const f32 lbl_80295B48;  // 1.0f
extern const f32 lbl_80295B4C;  // 0.5f

void fn_8007B608(Unk_5D6BE24B *arg0, s32 arg4) {
    Unk_C7387A53 *src;
    f32 cv;
    f32 one;
    f32 half;

    src = arg0->unk0x0;
    if (src != NULL) {
        ((Dst_8007B608 *)arg0->unk0x50)->unk0x14 = src->unk0xC;
    } else {
        ((Dst_8007B608 *)arg0->unk0x50)->unk0x14 = 0;
    }
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x3C = arg0->unk0x3C;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x40 = arg0->unk0x40;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x18 = arg0->unk0x8;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x1C = arg0->unk0xC;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x20 = arg0->unk0x2C;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x22 = arg0->unk0x2E;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x24 = arg0->unk0x10;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x28 = arg0->unk0x14;
    one = lbl_80295B48;
    half = lbl_80295B4C;
    cv = (f32)(f64)(s32)arg0->unk0x2C;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x2C =
        (arg0->unk0x18 + one) * half * cv;
    cv = (f32)(f64)(s32)arg0->unk0x2E;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x30 =
        (arg0->unk0x1C + one) * half * cv;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x34 = arg0->unk0x20;
    ((Dst_8007B608 *)arg0->unk0x50)->unk0x38 = arg0->unk0x44;
}
