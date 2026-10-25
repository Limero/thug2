// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD438-0x800BD518 (224B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern void *fn_801291FC(void *);
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_800BD438(Unk_8A4B2B78 *arg0, CStruct *arg1) {
    s32 temp_r3;
    u16 var_r30;
    register u32 var_r9 __asm__("r9");
    u32 var_r27;
    s32 var_r29;
    s32 *var_walker;
    s32 *list;
    s32 obj;
    s32 temp_old;

    temp_old = arg0->unk0x98;
    arg0->unk0x9C = *((volatile s32 *)&arg1->unk0x4);
    if (temp_old != 0) {
        Mem_Free2((void *) temp_old);
    }
    var_r30 = arg0->unk0x9C;
    temp_r3 = Mem_Alloc(var_r30 * 0x18);
    var_r9 = var_r30 - 1;
    if ((s32)var_r30 != 0) {
        while (var_r9-- != 0) {
        }
    }
    arg0->unk0x98 = temp_r3;
    var_r27 = 0U;
    list = (s32 *)fn_801291FC(arg1);
    if ((u32)var_r27 < (u32)arg0->unk0x9C) {
        var_walker = list;
        var_r29 = 0;
        do {
            obj = *var_walker;
            GetVector(obj, 0, (char *) arg0->unk0x98 + var_r29, 1);
            GetFloat(obj, QB_RADIUS, (char *) arg0->unk0x98 + var_r29 + 0x10, 1);
            var_walker += 1;
            var_r29 += 0x18;
            var_r27 += 1U;
        } while (var_r27 < (u32)arg0->unk0x9C);
    }
}
