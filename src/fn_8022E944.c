// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E944-0x8022EA0C (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

s32 fn_8022E944(void *arg0, CStruct *arg1, s32 *arg2) {
    s32 sp8;
    s32 spC;
    s32 count;
    s32 i;
    s32 next;
    s32 entry;

    count = arg1->unk0x4;
    i = *arg2;
    if (i < count) {
        do {
            entry = fn_80129528((s32)arg1, i);
            sp8 = 0;
            GetChecksum_2(entry, QB_CLASS, &sp8, 0);
            if (sp8 == QB_LEVELGEOMETRY) {
                if (GetChecksum_2(entry, QB_NAME, &spC, 0) != 0) {
                    *arg2 += 1;
                    return spC;
                }
            }
            next = *arg2 + 1;
            *arg2 = next;
            i = next;
        } while (i < count);
    }
    return 0;
}
