// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145514-0x801455F0 (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_801259C8(s32, s32);
void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
void fn_80145514(s32 arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    if (GetArray(arg1, QB_UNKNOWN_0x8E8EE0C0, &sp8, 0) != 0) {
        fn_80126E28(fn_801259C8(QB_CHAPTER_STATUS, 1), sp8);
    }
    if (GetArray(arg1, QB_UNKNOWN_0xD5F46FDA, &sp8, 0) != 0) {
        fn_80126E28(fn_801259C8(QB_CHAPTER_INTROS_VIEWED, 1), sp8);
    }
    if (GetArray(arg1, QB_UNKNOWN_0x72FC1AE3, &sp8, 0) != 0) {
        fn_80126E28(fn_801259C8(QB_CHAPTER_OUTTROS_VIEWED, 1), sp8);
    }
}
