// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C92C0-0x800C9310 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern void fn_800C11AC(Unk_BF454344 *, void *);
bool fn_800C92C0(Unk_BF454344 *arg0, CStruct *arg1) {
    s32 sp8[4];

    GetVector(arg1, QB_OFFSET, &sp8[0], 1);
    fn_800C11AC(arg0, &sp8[0]);
    return true;
}
