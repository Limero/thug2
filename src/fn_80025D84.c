// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80025D84-0x80025DF8 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void *fn_80025D50(void);
void fn_80025F9C(CStruct *, s32 *);
extern char lbl_80362CC0[];
void fn_80025D84(s32 arg0) {
    s32 sp8;
    s32 temp_r31;
    CStruct *temp_r3;

    sp8 = arg0;
    temp_r3 = fn_80025D50();
    if (temp_r3 != NULL) {
        temp_r31 = temp_r3->unk0x10 - 1;
        temp_r3->unk0x10 = temp_r31;
        if (temp_r31 == 0) {
            if (temp_r3->unk0x4 != 0) {
                Mem_Free2(temp_r3->unk0x4);
                temp_r3->unk0x4 = temp_r31;
            }
            fn_80025F9C(lbl_80362CC0, &sp8);
            Mem_Free(temp_r3);
        }
    }
}
