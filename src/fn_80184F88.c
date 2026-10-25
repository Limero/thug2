// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184F88-0x8018505C (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *fn_801840F0(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_8018BFAC(Unk_C7387A53 * arg0);
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
bool fn_80184F88(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 count;
    CStruct *walker;
    s32 i;
    Unk_C8FEE62D *obj;
    Unk_89391A04 *vt;

    count = 0;
    walker = arg0->unk0x2C;
    for (; (walker->unk0x4 == -1 && (walker = 0, 1), walker != NULL); ) {
        walker = walker->unk0xC;
        count += 1;
    }
    i = 0;
    while (i < count) {
        obj = fn_801840F0(arg0, i);
        vt = obj->unk0x14;
        if (vt->unk0x24((char *)obj + vt->unk0x20) != 0) {
            if (GetArray(fn_8018BFAC(obj), (sp8 = 0, QB_REQUIRED_GAPS), &sp8, 0) != 0) {
                return true;
            }
        }
        i++;
    }
    return false;
}
