// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AA60-0x8018AAE8 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Game_GetGoalManager(s32);
s32 fn_80184170(Unk_C7387A53 *, s32);
void *fn_801840F0(Unk_C7387A53 *, s32);
bool ScriptGoalManager_GoalShouldExpire(s32 arg0) {
    Unk_C8FEE62D *item;
    Unk_4E705049 *vtbl;
    s16 off;
    s32 (*fp)(void *);
    s32 i;
    s32 ctx;

    if ((ctx = Game_GetGoalManager(arg0)) != 0) {
        for (i = 0; i < fn_80184170(ctx, 1); i++) {
            item = fn_801840F0(ctx, i);
            vtbl = item->unk0x14;
            off = vtbl->unk0x18;
            fp = (s32 (*)(void *))vtbl->unk0x1C;
            if (fp((char *)item + off) != 0) {
                return true;
            }
        }
    }
    return false;
}
