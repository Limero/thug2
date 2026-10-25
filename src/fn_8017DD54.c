// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017DD54-0x8017E020 (716B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-rerun-cse-after-loop
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern void fn_80137CB4(Unk_9F066EC1 * arg0);
extern s32 fn_801A6F44(s32 arg0, s32 arg1);
extern s32 fn_8021B554(Unk_9994C3F5 * arg0);
extern s32 fn_8022A9B8(Unk_31DE137E * arg0);
extern void fn_8013CC84(void * arg0, s32 arg1, Unk_C71E6DE1 * arg2);

void fn_8017DD54(Unk_C7387A53 *arg0, Unk_31DE137E *arg1) {
    struct desc_s { u8 b; u16 hw; void *ptr; u8 pad1[4]; s32 v2; u8 b10; u8 tail[0x17]; };
    struct frame_s { s32 count; s32 arr[10]; u8 pad[0x5C]; struct desc_s d; } f;
    s32 g;

    g = lbl_80305F9C;
    fn_80137CB4(&f.d);
    f.count = 0;
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_ALWAYS_SPECIAL) != 0) {
        f.arr[f.count++] = QB_CHEAT_ALWAYS_SPECIAL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_MANUAL) != 0) {
        f.arr[f.count++] = QB_CHEAT_PERFECT_MANUAL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_RAIL) != 0) {
        f.arr[f.count++] = QB_CHEAT_PERFECT_RAIL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_PERFECT_SKITCH) != 0) {
        f.arr[f.count++] = QB_CHEAT_PERFECT_SKITCH;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_ALWAYS_SPECIAL) != 0) {
        f.arr[f.count++] = QB_CHEAT_ALWAYS_SPECIAL;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_CHEAT_STATS_13) != 0) {
        f.arr[f.count++] = QB_CHEAT_STATS_13;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_REVERTS) != 0) {
        f.arr[f.count++] = QB_FLAG_G_EXPERT_MODE_NO_REVERTS;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_WALKING) != 0) {
        f.arr[f.count++] = QB_FLAG_G_EXPERT_MODE_NO_WALKING;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_FLAG_G_EXPERT_MODE_NO_MANUALS) != 0) {
        f.arr[f.count++] = QB_FLAG_G_EXPERT_MODE_NO_MANUALS;
    }
    if (fn_801A6F44(arg0->unk0x24, QB_NO_G_DISPLAY_BALANCE) != 0) {
        f.arr[f.count++] = QB_NO_G_DISPLAY_BALANCE;
    }
    f.d.b = 0x82;
    f.d.ptr = &f.count;
    f.d.hw = (u16)((f.count * 4) + 4);
    f.d.v2 = 2;
    f.d.b10 = 8;
    fn_8013CC84(fn_8021B554(g), fn_8022A9B8(arg1), (s32)&f.d);
}
