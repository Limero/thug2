// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EE044-0x800EE0B8 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F674(s32, s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80127C14(CStruct *, s32, CStruct *);
void fn_800EE044(Unk_C7387A53 *arg0, CStruct *arg1) {
    AddChecksum(arg1, QB_UNKNOWN_0x2A19E830, arg0->unk0x30);
    AddChecksum(arg1, QB_UNKNOWN_0xE798FE80, arg0->unk0x34);
    fn_80127C14(arg1, QB_UNKNOWN_0x36FA68D2, arg0->unk0x2C);
    fn_8009F674(arg0, arg1);
}
