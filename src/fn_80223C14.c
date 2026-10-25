// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80223C14-0x80223C68 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8021D2C4(s32, s32);
void fn_8022A8E8(CScript *, s32);
bool fn_80223C14(Unk_DB0E2BAB *arg0) {
    void *id;
    s32 ret;

    id = *(void **)arg0;
    *((s32 *)&arg0->unk0xA0) = 1;
    ret = fn_8021D2C4(arg0->unk0x18, arg0->unk0x10);
    if (ret != 0) {
        fn_8022A8E8(ret, *(s32 *)id);
    }
    return true;
}
