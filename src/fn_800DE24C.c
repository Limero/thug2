// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE24C-0x800DE2A4 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029A1C0[];
void Mem_NewZero(s32);
void *fn_800DE24C(Unk_C8FEE62D *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_8029A1C0;
    arg0->unk0x4 = QB_CAMERA;
    Mem_NewZero(0xD0);
    arg0->unk0x1C = fn_8002439C();
    return arg0;
}
