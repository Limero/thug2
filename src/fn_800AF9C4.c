// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF9C4-0x800AFA90 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800AB15C(s32, s32);
extern f32 lbl_80298674;
extern s32 lbl_80301B48;
extern char lbl_802986B0[];
void fn_800F28E4(Unk_C7387A53 *, CStruct *);
s32 fn_800F2A48(s32, s32, s32);
void CStruct_delete(s32, s32);
void fn_80059380(f32, f32);
void fn_80059394(s32, f32, f32);
typedef struct {
    char pad0[0x14];
    s32 unk0x14;
    char pad1[0x24];
    s32 unk0x3C;
    s32 unk0x40;
    char pad2[0xC];
    s32 unk0x50;
    f32 unk0x54;
    f32 unk0x58;
    f32 unk0x5C;
    char pad3[0xC];
    s32 unk0x6C;
} Rec_800AF9C4;
void fn_800AF9C4(Rec_800AF9C4 *arg0, s32 arg1) {
    s32 temp_r30;

    arg0->unk0x14 = (s32)lbl_802986B0;
    if (arg0->unk0x50 != 0) {
        CStruct_delete(arg0->unk0x50, 3);
    }
    if (arg0->unk0x6C != 0) {
        if (arg0->unk0x3C != 0) {
            temp_r30 = lbl_80301B48;
            fn_800F28E4(temp_r30, fn_800F2A48(temp_r30, arg0->unk0x40, 1));
            arg0->unk0x3C = 0;
        }
        fn_80059380(arg0->unk0x54, lbl_80298674);
        fn_80059394(0, arg0->unk0x58, lbl_80298674);
        fn_80059394(1, arg0->unk0x5C, lbl_80298674);
    }
    fn_800AB15C(arg0, arg1);
}
