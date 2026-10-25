// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0710-0x800E0890 (384B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct Obj0710 {
    char pad0x0[0xC];
    void *unk0xC;
    char pad0x10[0xC];
    char unk0x1C[0x40];
    s32 unk0x5C;
    f32 unk0x60;
    s32 unk0x64;
    s32 unk0x68;
} Obj0710;

extern f32 lbl_8029A5D4;
extern f64 lbl_8029A5D8;
extern s32 lbl_80303150;

s32 GetString(CStruct *arg0, s32 arg1, u8 **arg2, s32 arg3);
s32 Tmr_GetTime(void);
char *strncpy(char *arg0, char *arg1, s32 arg2);
s32 GetInteger(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetFloat(CStruct *arg0, s32 arg1, f32 *arg2, s32 arg3);
s32 GetChecksum_2(CStruct *arg0, s32 arg1, void *arg2, s32 arg3);
s32 fn_80128978(CStruct *arg0, s32 arg1);

void fn_800E0710(Obj0710 *arg0, CStruct *arg1) {
    u8 *sp8;
    f32 spC;
    s32 var_r0;
    u32 var_u;

    if (arg0->unk0x64 == 0) {
        arg0->unk0x64 = *(s32 *)(*(s32 *)((char *)arg0 + 0xC) + 0x18) + QB_FLOATINGLABEL;
    }
    if (GetString(arg1, QB_STRING, &sp8, 0) != 0) {
        if (*sp8 == 0) {
            var_r0 = lbl_80303150 + Tmr_GetTime();
        } else {
            strncpy((char *)arg0 + 0x1C, (char *)sp8, 0x40);
            var_r0 = 0;
        }
        arg0->unk0x68 = var_r0;
    }
    GetInteger(arg1, QB_COLOR, &arg0->unk0x5C, 0);
    GetFloat(arg1, QB_Y_OFFSET, &arg0->unk0x60, 0);
    GetChecksum_2(arg1, QB_SCREEN_ELEMENT_ID, &arg0->unk0x64, 0);
    if (fn_80128978(arg1, QB_DURATION) != 0) {
        GetFloat(arg1, QB_DURATION, &spC, 0);
        arg0->unk0x68 = (lbl_80303150 + Tmr_GetTime()) + (u32)(spC * lbl_8029A5D4);
    }
}
