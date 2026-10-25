// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062934-0x80062988 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800071D4(void *);
#include "structs.h"
extern char lbl_80293FD0[];
void *fn_80062934(Unk_9994C3F5 *arg0) {
    arg0->unk0xBC = (s32)lbl_80293FD0;
    fn_800071D4((char *)arg0 + 0x90);
    arg0->unk0xB0 = 0;
    arg0->unk0xB4 = 0;
    arg0->unk0xB8 = 0;
    *((u8 *)&arg0->unk0x8) = 0;
    return arg0;
}
