// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80140120-0x80140164 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
bool fn_80140120(Unk_80577C09 *arg0, s32 arg1) {
    s32 temp_r3;

    temp_r3 = GetStructure(arg1, 1);
    __asm__("" : "+r"(arg0));
    fn_80126FF4((char *)arg0 + 4, temp_r3);
    return true;
}
