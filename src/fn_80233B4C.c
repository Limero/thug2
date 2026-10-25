// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233B4C-0x80233BB8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305FF8;
s32 fn_80233764(s32);
void fn_8012788C(CStruct *, u32, f32, f32, f32);
bool ScriptGetParkEditorCursorPos(s32 arg0, CScript *arg1) {
    volatile f32 sp8[4];
    register s32 src __asm__("r9");
    register f32 *p8 __asm__("r11");
    s32 ret;
    s32 fld;
    register f32 fz __asm__("fr3");

    ret = fn_80233764(*(s32 *)&lbl_80305FF8);
    __asm__("mr %0,%1" : "=&r"(src) : "r"(ret));
    p8 = (f32 *)&sp8[0];
    *(__ps_t *)&sp8[0] = *(__ps_t *)src;
    fld = arg1->unk0x18;
    *(__ps_t *)(p8 + 2) = ((Unk_EA529D06 *)src)->unk0x8;
    fz = ((volatile f32 *)p8)[2];
    fn_8012788C(fld, QB_POS, sp8[0], sp8[1], fz);
    return true;
}
