// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013FEC8-0x8013FF08 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F700[];
s32 CStruct_ctor(void *);
void *fn_8013FEC8(Unk_C7387A53 *arg0) {
    arg0->unk0xC = (s32)lbl_8029F700;
    CStruct_ctor((char *)arg0 + 4);
    return arg0;
}