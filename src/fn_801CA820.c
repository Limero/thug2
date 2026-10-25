// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CA820-0x801CA870 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: fn_8017EBAC 2-arg + s16 field + obj temp - EXACT, M5.45
s32 Mem_NewZero(s32);
void *fn_8017E1EC(void);
void fn_8017EBAC(Unk_667BA59C *, s32);
void fn_801CA820(Unk_31DE137E *arg0) {
    void *obj;

    if ((s32) arg0->unk0x1C == 0) {
        Mem_NewZero(0x155C);
        obj = fn_8017E1EC();
        arg0->unk0x1C = obj;
        fn_8017EBAC(obj, *(s16 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1A));
    }
}

