// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801378D0-0x80137950 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013775C(Unk_F386DC9F *, s32);
void fn_801378D0(Unk_F386DC9F *arg0, s32 arg1) {
    if ((s32) arg0->unk0x2134 != arg1) {
        arg0->unk0x2134 = arg1;
        switch (arg1) {
        case 1:
            fn_8013775C(arg0, 0x1068);
            return;
        case 2:
        case 4:
            fn_8013775C(arg0, 0x61A80);
            return;
        case 3:
            fn_8013775C(arg0, 0x493E0);
            break;
        }
    }
}