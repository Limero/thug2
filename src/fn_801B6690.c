// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B6690-0x801B67CC (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, u32);
s32 ShouldExecuteAction(s32, CStruct *, u32);
void GetFloat(CStruct *, u32, f32 *, s32);
void AdjustSpeed(Unk_C7387A53 *, f32);
s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
void *Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);

void fn_801B6690(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp10;
    s32 sp14;
    s32 zero;
    void *node;
    void *tail;
    s32 old;
    s32 cur;

    if ((ContainsFlag(arg1, QB_ADJUSTSPEED) != 0) && (ShouldExecuteAction(arg0, arg1, QB_ADJUSTSPEEDWEIGHT) != 0)) {
        GetFloat(arg1, QB_ADJUSTSPEEDPERCENT, &sp10, 1);
        AdjustSpeed(arg0, sp10);
    }
    if ((ContainsFlag(arg1, QB_RUNSCRIPT) != 0) && (ShouldExecuteAction(arg0, arg1, QB_RUNSCRIPTWEIGHT) != 0)) {
        zero = 0;
        GetChecksum_2(arg1, QB_RUNSCRIPTNAME, &sp14, 1);
        node = Script_SpawnScript(sp14, 0, 0, 0, 0, 0, 0, 0, zero, zero);
        old = arg0->unk0xC;
        tail = (char *)node + 0xBC;
        cur = *(s32 *)tail;
        if (cur != 0) {
            CObject_RemoveRefLink(cur, tail);
            *(s32 *)tail = 0;
        }
        *(s32 *)tail = old;
        if (old != 0) {
            CObject_AddRefLink((void *)old, tail);
        }
    }
}
