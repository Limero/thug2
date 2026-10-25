// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD274-0x801CD374 (256B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AD2B4[];
void fn_80007B94(char *);
void fn_8009F53C(void);
void fn_80105BF4(void *);
void fn_8010794C(void *);
extern char lbl_802AD950[];
void *fn_801CD274(Unk_FF487DD2 *arg0) {
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    CStruct *temp_r9;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_802AD950;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_8010794C((char *)arg0 + 0xB0);
    fn_8010794C((char *)arg0 + 0x170);
    temp_r9 = (CStruct *)((char *)arg0 + 0x3CC);
    temp_r9->unk0x4 = 0;
    temp_r9->unk0x8 = 0;
    var_ctr_2 = 4;
    arg0->unk0x3CC = 0;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    fn_80007B94((char *)arg0 + 0x470);
    var_ctr_3 = 4;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    fn_80105BF4((char *)arg0 + 0x578);
    {
        f32 f = (f32) *(f32 *)&lbl_802AD2B4;
        arg0->unk0x4 = QB_SKATERCOREPHYSICS;
        arg0->unk0x368 = -1;
        arg0->unk0x338 = f;
    }
    arg0->unk0x15A0 = 0;
    arg0->unk0x15A4 = 0;
    arg0->unk0x15A8 = 0;
    arg0->unk0x15AC = 0;
    arg0->unk0x15B0 = 0;
    arg0->unk0x15B4 = 0;
    arg0->unk0x15B8 = 0;
    arg0->unk0x15BC = 0;
    arg0->unk0x15C0 = 0;
    arg0->unk0x15C4 = 0;
    arg0->unk0x15C8 = 0;
    arg0->unk0x15CC = 0;
    arg0->unk0x358 = 0;
    arg0->unk0x31C = 0;
    arg0->unk0x334 = 0;
    arg0->unk0x340 = 0;
    arg0->unk0x364 = 0;
    return arg0;
}
