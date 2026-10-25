// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D4D94-0x800D4E34 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80299B00;
s32 fn_800D5048(Unk_31DE137E *);
s32 fn_800D5060(Unk_31DE137E *);
void fn_8012EFC0(Unk_C7387A53 *);
void fn_800D4D94(CScript *arg0, Unk_C7387A53 *arg1) {
    s32 temp_r0;

    temp_r0 = arg1->unk0xA4;
    switch (temp_r0) {
    case 5:
        if (fn_800D5048(arg0) == 0) {
            fn_8012EFC0(arg1);
        }
        break;
    case 7:
        if ((arg0->unk0x1C & 0x100) == 0) {
            fn_8012EFC0(arg1);
        }
        break;
    case 9:
        if (fn_800D5060(arg0) == 0) {
            fn_8012EFC0(arg1);
        }
        break;
    case 8:
        if (!(*((f32 *)&arg0->unk0x34) > lbl_80299B00)) {
            fn_8012EFC0(arg1);
        }
        break;
    }
}
