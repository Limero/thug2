// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017F5B0-0x8017F614 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_80182F98(CStruct *, s32);
extern void fn_8017F614(Unk_950BD505 *, s32);
void fn_8017F5B0(Unk_FFAD6788 *arg0, s32 arg1) {
    if (((s32)arg0->unk0x68 != 0) &&
        (arg0->unk0x78 >= 0) &&
        !(*(s32 *)((char *)fn_80182F98((char *)arg0 + 0x54, arg0->unk0x78) + 0x18) & 2)) {
        fn_8017F614(arg0, arg1);
    }
}
