// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CA80-0x8012CB2C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012CC30(s32, s32);
s32 fn_8012E710(s32);
s32 fn_8012CC0C(void);
extern char lbl_803032A8[];
extern char lbl_803032AC[];
extern s32 lbl_803032B0;
void *fn_8012CA80(void) {
    Unk_C7387A53 *temp_r31;
    Unk_31DE137E *temp_r3;
    Unk_31DE137E *temp_r3_2;
    Unk_31DE137E *temp_r9;

    if (lbl_803032B0 > 0x63) {
        temp_r3_2 = *(void * *)&lbl_803032AC;
        temp_r31 = temp_r3_2->unk0x60;
        if (temp_r3_2 != NULL) {
            fn_8012CC30(temp_r3_2, 3);
        }
        *(void * *)&lbl_803032AC = temp_r31;
        if (temp_r31 != NULL) {
            temp_r31->unk0x5C = 0;
        }
    }
    fn_8012E710(0x64);
    temp_r3 = (Unk_31DE137E *)fn_8012CC0C();
    temp_r9 = *(void * *)&lbl_803032A8;
    temp_r3->unk0x60 = 0;
    temp_r3->unk0x5C = temp_r9;
    if (temp_r9 != NULL) {
        temp_r9->unk0x60 = temp_r3;
    } else {
        *(s32 *)&lbl_803032AC = temp_r3;
    }
    *(s32 *)&lbl_803032A8 = temp_r3;
    return temp_r3;
}
