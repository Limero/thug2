// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184628-0x8018479C (372B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct * arg0);
extern s32 fn_80198F7C(s32 arg0);
extern Unk_C8FEE62D *fn_8018B4C0(void * arg0, s32 * arg1, s32 * arg2);
extern s32 fn_8018BFAC(Unk_C8FEE62D * arg0);
extern s32 ContainsFlag(s32 arg0, s32 arg1);
extern s32 fn_8018D924(Unk_C8FEE62D * arg0);
extern void fn_8018B90C(Unk_C8FEE62D * arg0);
extern void fn_80190764(Unk_C8FEE62D * arg0);
extern s32 fn_8018EC90(Unk_C8FEE62D * arg0);
extern s32 fn_80184168(void * arg0);
void fn_80184628(void *arg0) {
    s32 spC;
    s32 sp8 = 0;
    CStruct *prof = *(CStruct **)&lbl_80305F9C;
    Unk_C8FEE62D *obj;
    s32 *f30;
    s32 flags;

    while (sp8 < fn_80184168(arg0)) {
        obj = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if ((fn_8009CF2C(prof) == 0) || (fn_8018EC90(obj) != 0)) {
            fn_80190764(obj);
            if (fn_8018D924(obj) == 0) {
                if (((s32 (*)(void *))(*(Unk_4AA2E777 **)&obj->unk0x14)->unk0xAC)((char *)obj + (*(Unk_4AA2E777 **)&obj->unk0x14)->unk0xA8) == 0 || ContainsFlag(fn_8018BFAC(obj), QB_ALWAYS_INITIALIZE_GOAL) != 0) {
                    f30 = (s32 *)obj->unk0x30;
                    flags = fn_8018BFAC(obj);
                    if ((*f30 == 0) && ((fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_CLASSIC) || ((s32 (*)(void *))(*(Unk_4AA2E777 **)&obj->unk0x14)->unk0xAC)((char *)obj + (*(Unk_4AA2E777 **)&obj->unk0x14)->unk0xA8) == 0 || ContainsFlag(flags, QB_ALWAYS_INITIALIZE_GOAL) != 0 || ContainsFlag(flags, QB_EDITED_GOAL) != 0)) {
                        fn_8018B90C(obj);
                    }
                }
            }
        }
        sp8++;
    }
}
