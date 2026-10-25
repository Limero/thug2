// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C444-0x8016C4B0 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801316D8(void);
extern s32 Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
s32 fn_8016C444(Unk_15EF4A35 *arg0) {
    if (fn_801316D8() != 0) {
        return Script_SpawnScript(arg0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
