// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6E70-0x800B6FAC (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern f32 lbl_802989C8;
extern f32 lbl_802989CC;

typedef struct S6E70_vt {
    char pad0x0[0x40];
    s16 unk0x40;
    void (*unk0x44)(void *, s32);
} S6E70_vt;

typedef struct S6E70_sub {
    char pad0x0[0x210];
    void *unk0x210;
} S6E70_sub;

typedef struct S6E70 {
    char pad0x0[0x18];
    S6E70_vt *unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    u32 unk0x24;
    f32 unk0x28;
    S6E70_sub *unk0x2C;
} S6E70;

void fn_800B6FCC(void *, s32, f32);
s32 fn_80060DE4(void *);
s32 fn_8005B5FC(void *, f32, f32);

void fn_800B6E70(S6E70 *arg0) {
    s32 var_r9;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r11;
    u32 cprev;
    u32 c0;

    var_r9 = 1;
    if (!(arg0->unk0x1C & 2)) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        fn_800B6FCC(arg0, 0, lbl_802989C8);
        arg0->unk0x1C = arg0->unk0x1C | 2;
        return;
    }
    var_r11 = arg0->unk0x20;
    if (var_r11 != 0) {
        c0 = arg0->unk0x24;
        cprev = c0;
        c0++;
        arg0->unk0x24 = c0;
        if (cprev < (u32)var_r11) {
            fn_8005B5FC((void *)fn_80060DE4(arg0->unk0x2C->unk0x210), arg0->unk0x28, lbl_802989CC);
            return;
        }
    }
    arg0->unk0x24 = 0;
    var_r9 = arg0->unk0x1C;
    var_r0 = 1;
    if (!(var_r9 & 1)) {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        var_r0_2 = 1;
        if (!(var_r9 & 2)) {
            var_r0_2 = 0;
        }
        if (var_r0_2 == 0) {
            fn_800B6FCC(arg0, 0, lbl_802989C8);
            arg0->unk0x1C = arg0->unk0x1C | 2;
        }
        arg0->unk0x18->unk0x44((char *)arg0 + arg0->unk0x18->unk0x40, 1);
    } else {
        fn_800B6FCC(arg0, 1, lbl_802989C8);
    }
}
