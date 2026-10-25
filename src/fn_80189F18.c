// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80189F18-0x8018A038 (288B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void);
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern s32 fn_80184168(Unk_9994C3F5 *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern s32 fn_80183A64(s32, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern s32 fn_8018E24C(Unk_C7387A53 *);
extern void AddChecksum(CStruct *, s32, s32);
extern void AddInteger(CStruct *, s32, s32);
extern void fn_80129314(CStruct *, s32, s32);
extern void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
extern void fn_80126A30(Unk_5AA7B5D7 *);
extern void fn_80128FB4(Unk_F8A5095F *, s32);

bool ScriptGoalManager_GetGoalList(s32 arg0, CScript *arg1) {
    s32 mgr;
    s32 arr;
    s32 i;
    Unk_C8FEE62D *entry;
    s32 node;
    Unk_5BE2D2B7 *vt;

    i = 0;
    mgr = Game_GetGoalManager();
    arr = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(arr, fn_80184168(mgr), 0xA);
    while (i < fn_80184168(mgr)) {
        entry = fn_80183A64(mgr, i);
        node = CStruct_ctor(CStruct_new(8));
        AddChecksum(node, QB_GOALID, fn_8018E24C(entry));
        vt = entry->unk0x14;
        AddInteger(node, QB_HASBEATEN,
            vt->unk0xAC(
                (void *)((char *)entry + vt->unk0xA8)));
        fn_80129314(arr, i, node);
        i += 1;
    }
    fn_80127AAC(arg1->unk0x18, QB_GOALLIST, arr);
    fn_80126A30(arr);
    if (arr != 0) {
        fn_80128FB4(arr, 3);
    }
    return true;
}
