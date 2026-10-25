// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241C94-0x80241D58 (196B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
void *fn_80241E38(void * arg0, s32 arg1);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void fn_80241AA4(void *arg0, s32 arg1, s32 arg2);
void fn_8012788C(CStruct * arg0, s32 arg1, f32 f1, f32 f2, f32 f3);
void fn_80129314(CStruct * arg0, s32 arg1, s32 arg2);
void fn_80241C94(Unk_C7387A53 *arg0, s32 arg1) {
    f32 v[3];
    f32 *py;
    register s32 a1 __asm__("r27");
    s32 var_r28;
    Unk_9994C3F5 *var_r29;
    s32 var_r30;

    a1 = arg1;
    var_r28 = 0;
    fn_80129068(a1, arg0->unk0x30, 10);
    while ((u32)var_r28 < *((u32 *)&arg0->unk0x30)) {
        var_r29 = fn_80241E38(arg0, var_r28);
        var_r30 = CStruct_ctor(CStruct_new(8));
        AddChecksum(var_r30, 0, var_r29->unk0x8);
        fn_80241AA4(&v[0], arg0, var_r28);
        py = &v[0];
        fn_8012788C(var_r30, 0, v[0], py[1], py[2]);
        fn_80129314(a1, var_r28, var_r30);
        var_r28 = var_r28 + 1;
    }
}
