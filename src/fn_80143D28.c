// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143D28-0x80143E14 (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80032088(s32);
s32 fn_8012ED98(s32 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
void fn_801309EC(Unk_DB0E2BAB *);
void CStruct_delete(CStruct *, s32);
void fn_80143D28(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;

    if ((s32) arg0->unk0x14 == 0) {
        arg0->unk0x14 = fn_8012ED98(fn_80032088(0xF8));
    }
    var_r30 = 0;
    if ((arg1 != 0) || (arg2 != 0)) {
        var_r30 = CStruct_ctor(CStruct_new(8));
        if (arg1 != 0) {
            AddChecksum(var_r30, 0, QB_WALK);
        }
        if (arg2 != 0) {
            AddChecksum(var_r30, 0, QB_INCLEANUP);
        }
    }
    fn_8012F260(arg0->unk0x14, QB_SKATERINIT, var_r30, arg0);
    if ((s32) arg0->unk0xC8 != 0) {
        fn_801309EC((void *)arg0->unk0x14);
    }
    if (var_r30 != 0) {
        CStruct_delete(var_r30, 3);
    }
}
