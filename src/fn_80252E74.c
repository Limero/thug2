// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80252E74-0x80252EC8 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802533B0(CStruct *);
void fn_80253DBC(Unk_C7387A53 *);
void fn_80253FF4(Unk_31DE137E *);
void fn_80252E74(s32 *arg0) {
    if ((s32) *arg0 != 0) {
        fn_80253DBC((s32 *)((char *)arg0 + 0x88));
        fn_802533B0((s32 *)((char *)arg0 + 0x30));
        fn_80253FF4((s32 *)((char *)arg0 + 0xC));
        *arg0 = 0;
    }
}
