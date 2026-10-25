// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E00E8-0x800E021C (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

u32 fn_800145AC(void);
void fn_8009F010(s32, s32, s32);

typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0xC];
    s32 unk0x1C;
    s32 unk0x20;
    char pad0x24[0x500];
    s32 unk0x524;
    s32 unk0x528;
    s32 unk0x52C;
} Arg0_E00E8;

typedef struct {
    char pad0x0[0x20];
    f32 unk0x20;
} Arg6_E00E8;

void fn_800E00E8(Arg0_E00E8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, Arg6_E00E8 *arg6) {
    u32 time;
    u32 limit;
    u8 *base;
    register s32 idx __asm__("r9");

    if (arg6 != NULL) {
        time = fn_800145AC();
        limit = (u32)arg6->unk0x20;
        if (time < limit) {
            return;
        }
    }
    base = arg2;
    idx = arg1 + 1;
    if (*(u8 *)((char *)idx + (s32)base) != 0) {
        if ((arg0->unk0x1C & arg3) == 0 && arg0->unk0x52C != 0 && arg0->unk0x524 == 0 && arg0->unk0x528 == 0) {
            fn_8009F010(arg0->unk0xC, arg4, 0);
        }
        arg0->unk0x20 |= arg3;
        return;
    }
    if ((arg0->unk0x1C & arg3) != 0 && arg0->unk0x52C != 0 && arg0->unk0x524 == 0 && arg0->unk0x528 == 0) {
        fn_8009F010(arg0->unk0xC, arg5, 0);
    }
}
