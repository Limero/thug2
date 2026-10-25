// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C9404-0x801C9464 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801C8DEC(Unk_47DE0370 *);
void fn_801C6B00(Unk_C7387A53 *);
void fn_801C9404(Unk_C7387A53 * arg0) {
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x2AC) + 0x1C) > 0x13) {
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x2B8) + 0x1C) == 4) {
            fn_801C7ABC();
            return;
        }
        fn_801C8DEC(arg0);
        fn_801C6B00(arg0);
    }
}
