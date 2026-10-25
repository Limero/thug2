// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B67CC-0x801B6A60 (660B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
void fn_801B8070(Unk_C7387A53 *, CStruct *);
void fn_801B8120(void *, s32);
void fn_801B92F8(Unk_C7387A53 *, CStruct *, s32);
void fn_801B8CA8(Unk_C7387A53 *, CStruct *, s32);
void fn_801B826C(Unk_C7387A53 *, Unk_80577C09 *);
void fn_801B8168(Unk_C7387A53 *, CStruct *, s32);
void fn_801B92C4(void *, s32);
void fn_801B8598(Unk_C7387A53 *, Unk_80577C09 *);
void fn_801B8608(Unk_C7387A53 *, Unk_80577C09 *);
void fn_801B9080(Unk_C7387A53 *, Unk_80577C09 *);

void fn_801B67CC(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;

    if (((arg0->unk0x24 & 0xC0) == 0) &&
        (GetChecksum_2(arg1, QB_SKATEACTION, &sp8, 0) != 0)) {
        switch ((u32)sp8) {
        case QB_GRIND_BAIL:
        case QB_CONTINUE:
            break;
        case QB_VERT_GRIND:
        case QB_GRIND:
            fn_801B8070(arg0, arg1);
            break;
        case QB_GRIND_OFF:
            fn_801B8120(arg0, arg1);
            break;
        case QB_FLIP_TRICK:
            fn_801B92F8(arg0, arg1, 0);
            break;
        case QB_VERT_FLIP:
            fn_801B92F8(arg0, arg1, 1);
            break;
        case QB_GRAB_TRICK:
            fn_801B8CA8(arg0, arg1, 0);
            break;
        case QB_VERT_GRAB:
            fn_801B8CA8(arg0, arg1, 1);
            break;
        case QB_VERT_LIP:
            fn_801B826C(arg0, arg1);
            break;
        case QB_JUMP:
            fn_801B8168(arg0, arg1, 0);
            break;
        case QB_VERT_JUMP:
            fn_801B8168(arg0, arg1, 1);
            break;
        case QB_ROLL_OFF:
            fn_801B92C4(arg0, arg1);
            break;
        case QB_MANUAL:
            fn_801B8598(arg0, arg1);
            break;
        case QB_MANUAL_DOWN:
            fn_801B8608(arg0, arg1);
            break;
        case QB_STOP:
            fn_801B9080(arg0, arg1);
            break;
        case 0xE0000000u:
            break;
        }
    }
}
