// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145480-0x80145514 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void fn_80145480(s32 arg0, CStruct *arg1) {
    fn_80127AAC(arg1, QB_UNKNOWN_0x8E8EE0C0, fn_801259C8(QB_CHAPTER_STATUS, 1));
    fn_80127AAC(arg1, QB_UNKNOWN_0xD5F46FDA, fn_801259C8(QB_CHAPTER_INTROS_VIEWED, 1));
    fn_80127AAC(arg1, QB_UNKNOWN_0x72FC1AE3, fn_801259C8(QB_CHAPTER_OUTTROS_VIEWED, 1));
}
