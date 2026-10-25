// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80164390-0x80164488 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_803A00D8[];
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 ScriptSwapObjectModels(s32, s32);
extern void CStruct_delete(CStruct *, s32);

bool ScriptRestoreAllSwappedObjectModels(s32 arg0, s32 arg1) {
    s32 ctr;
    s32 base;
    s32 end;
    s32 cursor;
    s32 count;
    s32 var_r28;
    s32 temp_r31;

    s32 *p;
    s32 v;
    count = 0;
    p = lbl_803A00D8;
    for (ctr = 5; ctr != 0; ctr--) {
        v = *p;
        p += 3;
        if (v != 0) {
            count++;
        }
    }
    var_r28 = 0;
    if (count != 0) {
        base = (s32)lbl_803A00D8;
        end = base + 0x30;
        do {
            cursor = base;
            do {
                if (*(s32 *)cursor == 0) {
                    goto next_i;
                }
                var_r28 = 1;
                temp_r31 = CStruct_ctor(CStruct_new(8));
                AddChecksum(temp_r31, QB_OBJ_1, ((Unk_4C649A8C *)cursor)->unk0x4);
                AddChecksum(temp_r31, QB_OBJ_2, ((Unk_4C649A8C *)cursor)->unk0x8);
                ScriptSwapObjectModels(temp_r31, arg1);
                if (temp_r31 != 0) {
                    CStruct_delete(temp_r31, 3);
                }
            next_i:
                cursor += 12;
            } while (cursor <= end);
            if (var_r28 == 0) {
                break;
            }
            var_r28 = 0;
        } while (--count != 0);
    }
    return true;
}
