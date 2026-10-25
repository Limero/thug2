// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B092C-0x801B0A04 (216B). Byte-identical.
#include "types.h"
#include "structs.h"

register s32 r31_guard __asm__("r31");

extern s32 Mem_NewZero(s32);
extern void *fn_801B0544(CStruct *, s32);
extern void *fn_801B0170(CStruct *);
extern void fn_801B0228(Unk_9994C3F5 *, s32);

void *fn_801B092C(Unk_C8FEE62D *arg0) {
    s32 temp_r3;

    temp_r3 = (s32)fn_801B0544((void *)Mem_NewZero(0xC), 5);
    arg0->unk0x4 = temp_r3;
    temp_r3 = (s32)fn_801B0544((void *)Mem_NewZero(0xC), 5);
    arg0->unk0x8 = temp_r3;
    temp_r3 = (s32)fn_801B0544((void *)Mem_NewZero(0xC), 0xA);
    arg0->unk0xC = temp_r3;
    temp_r3 = (s32)fn_801B0170((void *)Mem_NewZero(0x14));
    arg0->unk0x1C = temp_r3;
    fn_801B0228(temp_r3, 0);
    temp_r3 = (s32)fn_801B0170((void *)Mem_NewZero(0x14));
    arg0->unk0x10 = temp_r3;
    fn_801B0228(temp_r3, 0);
    temp_r3 = (s32)fn_801B0170((void *)Mem_NewZero(0x14));
    arg0->unk0x18 = temp_r3;
    fn_801B0228(temp_r3, 0);
    temp_r3 = (s32)fn_801B0170((void *)Mem_NewZero(0x14));
    arg0->unk0x14 = temp_r3;
    fn_801B0228(temp_r3, 0);
    return arg0;
}
