// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017C0F8-0x8017C170 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80301A38[];
s32 fn_800A398C(s32, s8);
void fn_80144B90(Unk_31DE137E *);
void fn_80144BDC(Unk_31DE137E *);
bool fn_8017C0F8(Unk_D42E3F3A *arg0) {
    s32 temp_r3;
    u8 temp_r3_2;

    temp_r3 = fn_800A398C(*(s32 *)&lbl_80301A38, *(s8 *)(*((void * *)&arg0->unk0x0)));
    if (temp_r3 != 0) {
        temp_r3_2 = *((u8 *)&arg0->unk0x4);
        switch (temp_r3_2) {
        case 0x37:
            fn_80144B90(temp_r3);
            break;
        case 0x38:
            fn_80144BDC(temp_r3);
            break;
        }
    }
    return true;
}
