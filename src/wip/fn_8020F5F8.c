// WIP DRAFT — decode-documented park (groupB PS zone, 2026-08-25)
// PARKED (m2c husk retained; hand rebuild not completed).
// 832B, frame 0x168, saves f29-f31 + r28-r31. Family variant:
//   r30=&sp8 desc; NO fn_8010794C init visible at head; first call is
//   fn_80005854(desc, arg0+0x1860) after pair copies arg0+0x50->sp8,
//   +0x58->sp10. Then clamp idiom: spC = min(spC, const@lbl_802AF574-ish
//   [-0xa8c page 802B]); ps_sum0 dot vs lbl_802AF450 const pair
//   (word 0x10000032 = ps_sum1 f0,f0,f0). 13 calls, 22 op4 words all
//   standard emittable PS, ~44 psq pairs. Node-cleanup tail present.
// Walls: same allocator/scheduler classes as siblings in zone.
// family=m2c range=0x8020F5F8-0x8020F938 size=832B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CObject_RemoveRefLink(CStruct *, CStruct *);
static s32 sp120;
static s32 sp98;
static s32 spA4;

void fn_8020F5F8(Unk_BAF2D600 *arg0) {
    f32 sp118;
    f32 sp110;
    f32 sp10C;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    s32 spC0;
    f32 sp34;
    f32 sp2C;
    f32 sp24;
    f32 sp1C;
    s32 sp18;
    f32 spC;
    s32 sp8;
    f32 temp_f11;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f13;

    0;
    fn_80005854(&sp8, (char *)arg0 + 0x1860, 0);
    temp_f30 = *(f32 *)0x802AF574;
    var_f13 = spC;
    if (spC < temp_f30) {
        var_f13 = temp_f30;
    }
    spC = var_f13;
    0;
    if (var_f13 > temp_f30) {
        0;
        0;
        sp10C = *(f32 *)0x802AF578;
        0;
    }
    fn_8010794C(&sp18);
    temp_f31 = *(f32 *)0x802AF57C;
    0;
    sp24 = temp_f30;
    sp1C += temp_f31;
    GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(arg0, QB_CURB_FLOAT_FEELER_LENGTH, &spF8, 1);
    sp110 = spF8;
    0;
    0;
    0;
    0;
    sp2C += temp_f31;
    sp34 = temp_f30;
    if (fn_80107B20(&sp18, 1, 0) != 0) {
        sp118 = temp_f31;
        0;
        0;
        0;
        0;
        0;
        GetStructure(QB_WALK_PARAMETERS, 0);
        GetFloat(QB_SNAP_UP_HEIGHT, &spFC, 1);
        sp1C = arg0->unk0x2C + spFC;
        if (fn_80107B20(&sp18, 1, 0) != 0) {
            temp_f29 = (*(s32 *)0x802AF578 - sp98) * (spA4 - arg0->unk0x2C);
            if (!(fabs(arg0->unk0x7CC) < *(f32 *)0x802AF580) || (arg0->unk0xA0 != temp_f30) || (0, GetStructure(QB_WALK_PARAMETERS, 0), GetFloat(QB_MIN_CURB_HEIGHT_ADJUST_VEL, &sp100, 1), ((sp120 < (sp100 * sp100)) == 0))) {
                GetStructure(QB_WALK_PARAMETERS, 0);
                GetFloat(QB_CURB_FLOAT_LERP_UP_RATE, &sp104, 1);
                temp_f11 = arg0->unk0x7CC;
                arg0->unk0x7CC = (f32) (((temp_f29 - temp_f11) * (sp104 * arg0->unk0x88)) + temp_f11);
            }
            arg0->unk0x7D0 = 1;
        }
    }
    if (spC0 != 0) {
        CObject_RemoveRefLink(spC0, &spC0);
        spC0 = 0;
    }
}
