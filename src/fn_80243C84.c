// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243C84-0x80243CE8 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80241580(s32 *, s32);
void fn_80243C84(s32 arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r31;
    Unk_C7387A53 *temp_r3;

    temp_r30 = arg1 * 4;
    temp_r31 = arg0 + 4;
    temp_r3 = *(s32 *)((char *)temp_r31 + temp_r30);
    if (temp_r3 != NULL) {
        if ((s32) temp_r3->unk0xC != 0) {
            fn_80241580(temp_r3->unk0xC, 1);
        }
        if ((s32) *(s32 *)((char *)*(s32 *)((char *)temp_r31 + temp_r30) + (s32)0x10) != 0) {
            fn_80241580(*(s32 *)((char *)*(s32 *)((char *)temp_r31 + temp_r30) + (s32)0x10), 1);
        }
    }
}
