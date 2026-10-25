// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5DF0-0x801F5E44 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_801F5DF0(Unk_3CA72D64 *arg0) {
    arg0->unk0xAC04 = GetChecksum_3(arg0->unk0xC, QB_INPUT);
    arg0->unk0xAC08 = GetChecksum_3(arg0->unk0xC, QB_EDITORCAMERA);
}
