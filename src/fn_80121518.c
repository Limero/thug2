// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121518-0x8012156C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *memset(void *, s32, s32);
typedef struct S121518 { s32 f0; s32 f4; s32 f8; } S121518;
extern S121518 lbl_8039BA58;
void fn_80121518(s32 arg0, s32 arg1, s32 arg2) {
    memset(&lbl_8039BA58, 0, 0x3A0);
    lbl_8039BA58.f0 = arg0;
    lbl_8039BA58.f4 = arg1;
    lbl_8039BA58.f8 = arg2;
}
