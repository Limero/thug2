// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80194FAC-0x80195068 (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8019519C(Unk_C7387A53 *);
s32 fn_80195214(Unk_C7387A53 *);
s32 fn_8018C9D0(Unk_C8FEE62D *);
s32 fn_80195068(void *);
s32 Game_GetGoalManager(void);
s32 fn_8018E24C(Unk_C7387A53 *);
s32 fn_80183D68(Unk_C7387A53 *, s32);
s32 fn_801907E0(void *, s32);
void fn_80194FAC(Unk_C8FEE62D *arg0) {
    s32 temp_r30;
    Unk_0E2E8431 *temp_r9;

    if ((fn_8019519C(arg0) != 0) || (fn_80195214(arg0) != 0)) {
        fn_8018C9D0(arg0);
        return;
    }
    if (fn_80195068(arg0) != 0) {
        temp_r30 = Game_GetGoalManager();
        fn_80183D68(temp_r30, fn_8018E24C(arg0));
        return;
    }
    fn_801907E0(arg0, QB_EXPIRE);
    if ((s32) arg0->unk0x28 != 2) {
        temp_r9 = arg0->unk0x14;
        ((s32 (*)(void *, s32, s32))temp_r9->unk0x74)(
            (char *)arg0 + temp_r9->unk0x70, 0, 1);
    }
}
