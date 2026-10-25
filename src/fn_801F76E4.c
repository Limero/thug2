// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F76E4-0x801F7748 (100B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80238964(void);
extern s32 fn_8022DCD8(s32, s32, s32, s32, s32);
extern void fn_8024077C(s32);
extern void fn_8022D4C4(Unk_DB0E2BAB *);
extern void fn_800546A0(s32);

void fn_801F76E4(s32 arg0) {
    s32 temp_r30;

    temp_r30 = fn_8022DCD8(*(s32 *)fn_80238964(), arg0, 0, 1, 0);
    fn_8024077C(0);
    fn_8022D4C4(*(s32 *)fn_80238964());
    fn_800546A0(temp_r30);
}
