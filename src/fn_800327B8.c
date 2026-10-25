// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800327B8-0x800328BC (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80291B30;
extern f32 lbl_80291B34;
extern s32 fn_80032A60(void *);
extern f32 fn_800144C8(void);
extern void fn_80032A68(void *, s32);

typedef struct {
    char pad0x0[0x30];
    s16 unk0x30;
    s32 (*unk0x34)(void *);
} VtLocal;

typedef struct {
    char pad0x0[0x34];
    s32 unk0x34;
    char pad0x38[0x40 - 0x38];
    void *unk0x40[6];
    s32 unk0x58;
    f32 unk0x5C;
    f32 unk0x60;
    f32 unk0x64;
} ObjLocal;

void fn_800327B8(ObjLocal *arg0) {
    f32 temp_f13;
    s32 var_r29;
    void **var_r31;
    void *temp_r11;
    VtLocal *temp_r9;

    arg0->unk0x34 = 0;
    if (fn_80032A60(arg0) == 1) {
        temp_f13 = arg0->unk0x60 - (arg0->unk0x5C * (fn_800144C8() * lbl_80291B30));
        arg0->unk0x60 = temp_f13;
        if (temp_f13 <= lbl_80291B34) {
            fn_80032A68(arg0, 0);
        } else if ((temp_f13 * arg0->unk0x64) < lbl_80291B34) {
            fn_80032A68(arg0, 0);
        }
    }
    if ((fn_80032A60(arg0) == 2) || (fn_80032A60(arg0) == 1)) {
        var_r29 = 0;
        if (var_r29 < arg0->unk0x58) {
            var_r31 = arg0->unk0x40;
            do {
                temp_r11 = *var_r31;
                var_r29 += 1;
                var_r31 += 1;
                temp_r9 = *(VtLocal **)((char *)temp_r11 + 0x14);
                temp_r9->unk0x34(temp_r11 + temp_r9->unk0x30);
            } while (var_r29 < arg0->unk0x58);
        }
    }
}
