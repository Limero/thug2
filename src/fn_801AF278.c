// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF278-0x801AF2F4 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802ABC88[];
extern void *lbl_802FFE98;
extern s32 lbl_803A2F24;
extern void fn_8000F2F8(Unk_9F352E7C *, s32);
extern void fn_8000F320(Unk_F12C5E01 *);
extern s32 fn_80125814(s32, s32);
extern void fn_800F0EF0(CStruct *, s32, s32);
extern void fn_801AF210(void);
register s32 r31_guard __asm__("r31");
void fn_801AF278(s32 *arg0) {
    s32 z;

    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
    lbl_803A2F24 = (s32)arg0;
    *arg0 = 1;
    fn_80125814((z = 0, (s32)lbl_802ABC88), z);
    fn_800F0EF0(QB_TRIGGERSCRIPT, QB_ENDGAP, (s32)fn_801AF210);
    fn_8000F320(lbl_802FFE98);
}
