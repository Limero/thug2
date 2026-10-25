// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010794C-0x80107998 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800063B4(void);
void fn_80107A28(Unk_C5652918 *);
void *fn_8010794C(Unk_C7387A53 *arg0) {
    CStruct *temp_r9;

    fn_800063B4();
    temp_r9 = (char *)arg0 + 0xA8;
    temp_r9->unk0x4 = 0;
    temp_r9->unk0x8 = 0;
    arg0->unk0xA8 = 0;
    fn_80107A28(arg0);
    return arg0;
}
