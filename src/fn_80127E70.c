// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127E70-0x80127F00 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void AddInteger(s32, s32, s32);
void fn_8012772C(f32);
void fn_80127CD4(s32, s32, s32);
void AddArrayPointer(s32, s32, s32);
void AddChecksum(s32, s32, s32);
void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp8;

    switch (arg2) {
    case 1:
        AddInteger(arg0, arg1, arg3);
        return;
    case 2:
        sp8 = arg3;
        fn_8012772C(*((f32 *)&sp8));
        return;
    case 11:
        fn_80127CD4(arg0, arg1, arg3);
        return;
    case 12:
        AddArrayPointer(arg0, arg1, arg3);
        return;
    case 13:
        AddChecksum(arg0, arg1, arg3);
        return;
    }
}
