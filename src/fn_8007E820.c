// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E820-0x8007E86C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8007DF14(Unk_9D99273B *);
void fn_8007E820(Unk_FFAD6788 *arg0,Unk_9D99273B * arg1) {
    arg0->unk0xC8 = arg1;
    arg0->unk0xB4 = (s32) *(s32 *)((char *)fn_8007DF14(arg1) + (s32)0x68);
    arg0->unk0xB8 = (s32) *(s32 *)((char *)fn_8007DF14(arg0->unk0xC8) + (s32)0x6C);
}
