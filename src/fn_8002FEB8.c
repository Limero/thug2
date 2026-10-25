// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002FEB8-0x8002FEF0 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801270B4(CStruct *, s32);
void fn_8002FEB8(void *arg0) {
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x78) + 0x24) != 0) {
        fn_801270B4(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x78) + 0x24), QB_ANIMTAGS);
    }
}
