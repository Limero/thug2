// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DF68-0x8002E050 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80291954;
extern f32 lbl_80291958;
extern char lbl_80291A48[];
extern char lbl_80291A90[];
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    s32 unk0x8;
    void *unk0xC;
    void *unk0x10;
    void *unk0x14;
} Sub_8002DF68;
typedef struct {
    char pad0x0[0x4];
    void *unk0x4;
    s32 unk0x8;
    void *unk0xC;
    void *unk0x10;
    void *unk0x14;
    Sub_8002DF68 unk0x18;
    s32 unk0x30;
    s32 unk0x34;
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    f32 unk0x44;
    f32 unk0x48;
    char pad0x4C[0x8];
    s32 unk0x54;
    s32 unk0x58;
    char pad0x5C[0x4];
    s32 unk0x60;
    char pad0x64[0x4];
    s32 unk0x68;
    char pad0x6C[0xC];
    s32 unk0x78;
    s32 unk0x7C;
} Rec_8002DF68;
void fn_8002E0F8(Rec_8002DF68 *);
void *fn_8002DF68(Rec_8002DF68 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Sub_8002DF68 *temp_r9;
    arg0->unk0x14 = lbl_80291A48;
    arg0->unk0x4 = arg0;
    temp_r9 = &arg0->unk0x18;
    arg0->unk0x8 = 0;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x14 = lbl_80291A90;
    arg0->unk0x78 = arg1;
    arg0->unk0x7C = arg2;
    arg0->unk0x60 = 0;
    arg0->unk0x68 = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x34 = 0;
    arg0->unk0x54 = 0;
    arg0->unk0x58 = 1;

    if (arg3 != 0) {
        arg0->unk0x38 = lbl_80291954;
        arg0->unk0x3C = lbl_80291954;
        arg0->unk0x40 = lbl_80291954;
        arg0->unk0x44 = lbl_80291958;
        arg0->unk0x48 = lbl_80291958;
    } else {
        arg0->unk0x38 = lbl_80291958;
        arg0->unk0x3C = lbl_80291958;
        arg0->unk0x40 = lbl_80291958;
        arg0->unk0x44 = lbl_80291958;
        arg0->unk0x48 = lbl_80291958;
    }
    fn_8002E0F8(arg0);
    return arg0;
}

