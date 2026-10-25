// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802196B0-0x80219724 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

s32 fn_802196B0(s32 arg0) {
    s32 sp8;

    fn_80128E34(fn_8013FF5C(arg0 + 0x110, QB_RANK_TEST), QB_CHECKSUM, &sp8, 1);
    if (sp8 != QB_RANK_TEST_LESS) {
        return (sp8 == QB_RANK_TEST_GREATER) ? 2 : 0;
    }
    return 1;
}
