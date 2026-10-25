// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010BABC-0x8010BB24 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803830D0[];
extern void fn_8010BE5C(CStruct *);
extern void *fn_8010BE70(CStruct *, s32 *);
s32 fn_8010BABC(s32 arg0) {
    CStruct *temp_r3;

    fn_8010BE5C(lbl_803830D0);
    while ((temp_r3 = fn_8010BE70(lbl_803830D0, 0)) != NULL) {
        if (*(u8 *)temp_r3 == arg0) {
            return temp_r3->unk0x4;
        }
    }
    return 0;
}
