// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233450-0x802334D4 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8023C598(s32);
void fn_8023EE14(Unk_C7387A53 *);
s32 fn_80238970(void);
s32 fn_8023EFC8(void);
s32 fn_8023897C(void *, s32, s32 *);
void fn_8023F07C(s32, s32, s32, s32);
void fn_80233450(s32 arg0) {
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;

    if (fn_8023C598(0) != 0) {
        s32 o = fn_8023C598(1);
        {
            register s32 f27 __asm__("r27");
            register s32 f28 __asm__("r28");
            f27 = ((CStruct *)o)->unk0x6C;
            f28 = ((CStruct *)o)->unk0x70;
        temp_r30 = fn_80238970();
        temp_r29 = fn_8023EFC8();
            fn_8023F07C(temp_r29, fn_8023897C(temp_r30, f27, 0), f27, f28);
        }
        fn_8023EE14(fn_8023C598(1));
    }
}
