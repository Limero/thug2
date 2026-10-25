// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176E68-0x80176EE0 (120B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_8005DE90(s32);
void *fn_80024660(void);
extern s32 lbl_80300E00;
void fn_80176E68(Unk_BC2275DF *arg0) {
    if ((lbl_80300E00 > 1) || (fn_8005DE90(0) == 0)) {
        arg0->unk0x430 = 1;
        return;
    }
    arg0->unk0x430 = 0;
    fn_8005DE90(0);
    {
        char *src = (char *)fn_80024660();
        arg0->unk0x438 = ((Unk_C1F9F519 *)src)->unk0x0;
        arg0->unk0x440 = ((Unk_C1F9F519 *)src)->unk0x8;
    }
}
