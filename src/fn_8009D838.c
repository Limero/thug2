// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D838-0x8009D888 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000A1FC(Unk_C8FEE62D *);
void fn_8009DA18(Unk_C8FEE62D *);
void *fn_8009D838(CStruct *arg0) {
    fn_8000A1FC((char *)arg0 + 4);
    fn_8009DA18((char *)arg0 + 0x50);
    arg0->unk0x84 = 0;
    arg0->unk0x8C = 0;
    arg0->unk0x88 = 0;
    *((s32 *)&arg0->unk0x90) = 0;
    return arg0;
}
