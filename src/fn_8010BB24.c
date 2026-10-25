// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010BB24-0x8010BB8C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803830E8[];
extern void fn_8010BF2C(CStruct *);
extern void *fn_8010BF40(CStruct *, s32 *);
u8 fn_8010BB24(s32 arg0, s32 arg1) {
    CStruct *temp_r3;

    fn_8010BF2C(lbl_803830E8);
    while ((temp_r3 = fn_8010BF40(lbl_803830E8, 0)) != NULL) {
        if (temp_r3->unk0x4 == arg0) {
            return *(u8 *)temp_r3;
        }
    }
    return 0;
}
