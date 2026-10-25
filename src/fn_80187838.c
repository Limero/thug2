// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187838-0x801878EC (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 *);
extern void *fn_8018B4C0(Unk_C8FEE62D *, s32 *, s32 *);
extern s32 fn_8018BFAC(Unk_C7387A53 *);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum(CStruct *, s32);
extern void fn_8015010C(void);

void fn_80187838(Unk_9994C3F5 *arg0) {
    s32 i;
    s32 spC;
    void *sp10;
    u32 j;
    u32 jo;
    register void *p10 __asm__("r9");

    i = 0;
    while (i < fn_80184168((void *)arg0)) {
        if (GetArray(fn_8018BFAC(fn_8018B4C0((void *)((char *)arg0 + 4), &i, &spC)), QB_CREATE_GEOMETRY, &sp10, 0) != 0) {
            j = 0U;
            p10 = sp10;
            while (j < *((u32 *)&((CStruct *)p10)->unk0x4)) {
                GetChecksum((s32)sp10, (jo = j, j += 1, jo));
                fn_8015010C();
                p10 = sp10;
            }
        }
        i++;
    }
}
