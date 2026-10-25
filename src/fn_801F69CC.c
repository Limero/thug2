// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F69CC-0x801F6A90 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801F5898(void * arg0, CStruct * arg1);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 fn_801F366C(void * arg0, s32 arg1);
extern void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
extern void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);

bool fn_801F69CC(void *arg0, CStruct *arg1, CScript *arg2) {
    s32 sp8;
    s32 mgr;
    Unk_1D62F22E *entry;

    mgr = fn_801F5898(arg0, arg1);
    if (mgr != 0) {
        sp8 = 0;
        GetInteger(arg1, QB_SET_INDEX, &sp8, 0);
        entry = fn_801F366C(mgr, sp8);
        if (entry == 0) {
            return false;
        }
        AddInteger(arg2->unk0x18, QB_SPIN, entry->unk0x2 * 0xB4);
        AddInteger(arg2->unk0x18, QB_NUM_TAPS, entry->unk0x3);
        if (entry->unk0x1 != 0) {
            AddChecksum(arg2->unk0x18, 0, QB_REQUIRE_PERFECT);
        }
    }
    return true;
}
