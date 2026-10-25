// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80197FA8-0x80197FE4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
void fn_80197FA8(Unk_D4A84CA9 *arg0) {
    arg0->unk0x528 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
}
