// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED2DC-0x801ED360 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801ED2DC(Unk_8FAE40CA *arg0) {
    s32 var_r10;
    Unk_FFAD6788 *temp_r11;

    var_r10 = 0;
    temp_r11 = arg0->unk0x15A0;
    if ((s32) arg0->unk0x154C != 0) {
        if ((s32) temp_r11->unk0xBC == 0) {
            arg0->unk0x154C = 0;
        }
    } else {
        if ((s32) temp_r11->unk0xBC != 0) {
            var_r10 = 1;
        }
        if (var_r10 != 0) {
            arg0->unk0x154C = 1;
            Script_RunScript(QB_TOGGLE_BULLETTIME, 0, 0, 0, 0);
        }
    }
}
