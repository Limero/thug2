// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80187424-0x801875CC (424B). Byte-identical.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern void *fn_8018B4C0(Unk_C8FEE62D *, s32 *, s32 *);
extern s32 fn_80184168(Unk_9994C3F5 *);
extern s32 fn_80190738(Unk_C7387A53 *);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_8018BFAC(Unk_C7387A53 *);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 fn_8018E24C(Unk_C7387A53 *);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_SpawnScript(Unk_15EF4A35 *, s32, s32, Unk_80577C09 *, s32, s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern s32 fn_8018DFB4(Unk_C7387A53 *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_80197CF0(void *);

void fn_80187424(Unk_9994C3F5 *arg0) {
    s32 i;
    s32 sp14;
    s32 sp18;
    s32 count;
    Unk_89391A04 *vt;
    s16 vtoff;
    s32 (*vtfp)(void *);
    Unk_C8FEE62D *obj;
    s32 spawned;

    count = fn_80184168((void *)arg0);
    for (i = 0; i < count; i++) {
        obj = fn_8018B4C0((void *)((char *)arg0 + 4), &i, &sp14);
        vt = obj->unk0x14;
        vtoff = vt->unk0x20;
        vtfp = vt->unk0x24;
        if (vtfp((void *)((char *)obj + vtoff)) != 0) {
            if (fn_80190738(obj) != 0) {
                if (ContainsFlag(fn_8018BFAC(obj), QB_COMBO_STARTED) != 0) {
                    spawned = CStruct_ctor(CStruct_new(8));
                    AddChecksum(spawned, QB_GOAL_ID, fn_8018E24C(obj));
                    Script_SpawnScript(QB_GOAL_LOSE_NEXT_FRAME, spawned, 0, 0, 0, 0, 0, 0, 0, 0);
                    if (spawned != 0) {
                        CStruct_delete(spawned, 3);
                    }
                }
            }
            if (fn_8018DFB4(obj) != 0) {
                if ((GetInteger(fn_8018BFAC(obj), QB_TRICK_FLAG, &sp18, 0) != 0) && (sp18 != 0)) {
                    AddInteger(fn_8018BFAC(obj), QB_TRICK_FLAG, 0);
                }
            } else {
                if (ContainsFlag(fn_8018BFAC(obj), QB_TRICKBEAT) != 0) {
                    fn_80197CF0(obj);
                }
            }
        }
    }
}
