// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F4E0-0x8002F5AC (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x28];
    f32 unk0x28;
} A2F4E0;

typedef struct {
    char pad0x0[0x2C];
    s32 unk0x2C;
    char pad0x30[4];
    s32 unk0x34;
} T2F4E0;

void fn_8002DDAC(void *, f32 *, f32 *, f32 *);
void AddChecksum(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
extern s32 lbl_80291990[4];

void fn_8002F4E0(s32 arg0, A2F4E0 *arg1, CStruct *arg2) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    T2F4E0 *temp_r30;

    temp_r30 = (T2F4E0 *)((char *)arg1 + 4);
    AddChecksum(arg2, QB_ANIM, temp_r30->unk0x34);
    fn_8012772C(arg2, QB_SPEED, arg1->unk0x28);
    AddChecksum(arg2, QB_LOOPINGTYPE, lbl_80291990[temp_r30->unk0x2C]);
    fn_8002DDAC(temp_r30, &sp8, &spC, &sp10);
    fn_8012772C(arg2, QB_STARTTIME, sp8);
    fn_8012772C(arg2, QB_CURRENTTIME, spC);
    fn_8012772C(arg2, QB_ENDTIME, sp10);
}
