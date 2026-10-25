// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207538-0x80207574 (60B). Byte-identical.
#include "types.h"
s32 fn_8009D2B0(s32);
typedef struct { char pad[0xA04]; s32 arr[1]; } S;
s32 fn_80207538(S *arg0, s32 arg1) {
    return arg0->arr[fn_8009D2B0(arg1)];
}
