// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192704-0x801927B4 (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
void fn_8018B90C(Unk_C7387A53 *);
s32 fn_80198F7C(s32);
s32 fn_80199968(void);
s32 fn_8018CD64(Unk_C8FEE62D *);
s32 fn_80192704(Unk_C8FEE62D *arg0) {
    Unk_89391A04 *temp_r9;
    Unk_64253088 *temp_r9_2;

    if (arg0->unk0x74 == 0) {
        fn_8018B90C(arg0);
        arg0->unk0x74 = 1;
    }
    if ((fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK) && (fn_80199968() != 0)) {
        temp_r9 = *((void * *)&arg0->unk0x14);
        if (temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20) != 0) {
            temp_r9_2 = *((void * *)&arg0->unk0x14);
            ((s32 (*)(void *))(temp_r9_2->unk0x34))((char *)arg0 + temp_r9_2->unk0x30);
            return 1;
        }
    }
    return fn_8018CD64(arg0);
}
