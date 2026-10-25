// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4D50-0x800F4E0C (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
s32 fn_80039A28(void);
s32 fn_80039AD4(s32, void *, void *, s32);
void fn_80013788(s32);
s32 fn_800F3794(Unk_C7387A53 *, void *, void *);
s32 fn_800F4D50(Unk_C7387A53 *arg0, Unk_B90F48EC *arg1, CStruct *arg2) {
    s32 temp_r30;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9b;

    Mem_NewZero(0x59C);
    temp_r30 = fn_80039A28();
    if (fn_80039AD4(temp_r30, arg1, arg2, 1) == 0) {
        return 0;
    }
    temp_r9 = arg0->unk0x50;
    ((s32 (*)(char *, s32))temp_r9->unk0x5C)(
        (char *)arg0 + *(s16 *)((char *)temp_r9 + 0x58), temp_r30);
    if (arg0->unk0x20 != 0) {
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    temp_r9b = arg0->unk0x50;
    ((void (*)(char *))temp_r9b->unk0x84)(
        (char *)arg0 + *(s16 *)((char *)temp_r9b + 0x80));
    return fn_800F3794(arg0, arg1, arg2);
}
