// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023F94-0x80024000 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern Unk_9994C3F5 *lbl_802FFE98;
extern s32 lbl_80300368;
extern s32 lbl_8030036C;
extern s32 lbl_80300370;
extern void fn_80010D94(s32, s32);
extern void fn_80010E78(s32);

void fn_80023F94(s32 arg0) {
    fn_80010D94(lbl_802FFE98->unk0x11C, 0x20);
    lbl_80300368 = (s32)Mem_Alloc(arg0);
    fn_80010E78(lbl_802FFE98->unk0x11C);
    lbl_8030036C = 0;
    lbl_80300370 = arg0;
}
