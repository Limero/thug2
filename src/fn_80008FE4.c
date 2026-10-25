// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80008FE4-0x8000901C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80008FE4(CStruct *arg0) {
    if ((s32) arg0->unk0xC != 0x20) {
        **((s32 * *)&arg0->unk0x0) = arg0->unk0x8;
        arg0->unk0x8 = 0;
        arg0->unk0x0 = (s32 *) (arg0->unk0x0 + 4);
        arg0->unk0xC = 0x20;
    }
}
