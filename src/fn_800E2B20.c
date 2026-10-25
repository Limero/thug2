// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2B20-0x800E2B7C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80069C78(s32, s32, s32);
s32 fn_80128E34(CStruct *, s32, void *, s32);
bool fn_800E2B20(CScript *arg0, CStruct *arg1) {
    fn_80128E34(arg1, 0, (char *)arg0 + 0x1C, 1);
    if ((s32) arg0->unk0x20 != 0) {
        fn_80069C78(arg0->unk0x20, arg0->unk0x1C, *(s32 *)((char *)(*(s32 *)((char *)arg0 + 0xC)) + 0x18));
    }
    return true;
}
