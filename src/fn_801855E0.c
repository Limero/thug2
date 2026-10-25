// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801855E0-0x8018568C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_80184168(void *arg0);
void *fn_8018B4C0(void *arg0, s32 *arg1, s32 *arg2);
s32 fn_8018E520(void *arg0, s32 arg1);

typedef struct {
    char pad0[0xA8];
    s16 unk0xA8;
    char pad1[2];
    s32 unk0xAC;
} Vt8155E0;

typedef struct {
    char pad0[0x14];
    Vt8155E0 *unk0x14;
} N8155E0;

bool fn_801855E0(char *arg0, s32 arg1) {
    s32 i;
    s32 spC;
    N8155E0 *p;
    Vt8155E0 *vt;

    i = 0;
    for (i = 0; i < fn_80184168(arg0); i++) {
        p = (N8155E0 *)fn_8018B4C0(arg0 + 4, &i, &spC);
        vt = p->unk0x14;
        if (((s32 (*)(char *))vt->unk0xAC)((char *)p + vt->unk0xA8) != 0) {
            if (fn_8018E520(p, arg1) != 0) {
                return true;
            }
        }
    }
    return false;
}
