// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182FB0-0x80183050 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80182FB0(CStruct *arg0, s32 arg1) {
    s32 i;

    Mem_Free(*(s32 *)(*((char * *)&arg0->unk0x4) + arg1 * 4));
    for (i = arg1; i < arg0->unk0xC - 1; i++) {
        *(s32 *)(*((char * *)&arg0->unk0x4) + i * 4) =
            *(s32 *)(*((char * *)&arg0->unk0x4) + (i + 1) * 4);
    }
    *(s32 *)(*((char * *)&arg0->unk0x4) + arg0->unk0xC * 4 - 4) = 0;
    arg0->unk0xC = arg0->unk0xC - 1;
}
