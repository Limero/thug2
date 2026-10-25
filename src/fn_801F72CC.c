// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F72CC-0x801F7320 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801F5898(void);
s32 fn_801F43E4(void);
s32 fn_801F5AA4(Unk_F0C166E4 *);
s32 fn_801F559C(Unk_F0C166E4 *);
bool fn_801F72CC(Unk_F0C166E4 *arg0) {
    s32 temp_r3;

    temp_r3 = fn_801F5898();
    arg0->unk0xAC00 = temp_r3;
    if (temp_r3 != 0) {
        fn_801F43E4();
        fn_801F5AA4(arg0);
        fn_801F559C(arg0);
    }
    return true;
}
