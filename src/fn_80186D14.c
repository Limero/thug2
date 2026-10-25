// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186D14-0x80186DDC (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0xA8];
    s16 unk0xA8;
    s32 unk0xAC;
} Rec_80186D14;
s32 fn_80184168(void *);
void CStruct_new(s32);
s32 CStruct_ctor();
s32 fn_8018B4C0(void *, s32 *, s32 *);
s32 fn_8018EC90(void *);
s32 fn_801903B0(void *);
void AddInteger(void *, s32, s32);
s32 fn_80186D14(char *arg0) {
    s32 spC;
    s32 sp8;
    s32 total;
    s32 n;
    s32 mgr;
    char *obj;
    Rec_80186D14 *rec;
    total = 0;
    n = fn_80184168(arg0);
    CStruct_new(8);
    mgr = CStruct_ctor();
    for (sp8 = 0; sp8 < n; sp8++) {
        obj = (char *)fn_8018B4C0(arg0 + 4, &sp8, &spC);
        if (fn_8018EC90(obj) == 0) {
            rec = *(Rec_80186D14 **)(obj + 0x14);
            if (((s32 (*)(void *))rec->unk0xAC)(obj + rec->unk0xA8) != 0) {
                total += fn_801903B0(obj);
            }
        }
    }
    AddInteger((void *)mgr, QB_TOTALSTARTS, total);
    return mgr;
}
