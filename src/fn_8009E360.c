// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E360-0x8009E3A4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void AddChecksum(CStruct *, void *, void *);
// SetChecksumTag @ 0x8009E360
void SetChecksumTag(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    fn_8009F134();
    AddChecksum(arg0->unk0x24, arg1, arg2);
}
