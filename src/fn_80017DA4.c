// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80017DA4-0x80017E20 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern bool lbl_8030014C;
void OSRestoreInterrupts(s32);
void OSSleepThread(s32);
s32 queue_length(Unk_D78094DA *);
void fn_800181A4(s32, s32);
extern char lbl_8031E748[];
extern char lbl_8031E7E0[];
void fn_80017DA4(void) {
    s32 temp_r31;

    fn_800181A4(0, 0);
    if (lbl_8030014C != 1) {
        fn_8001CA24();
        temp_r31 = OSDisableInterrupts();
        if (queue_length((s32)lbl_8031E748) > 1U) {
            OSSleepThread((s32)lbl_8031E7E0);
        }
        OSRestoreInterrupts(temp_r31);
        lbl_8030014C = 1;
    }
}
