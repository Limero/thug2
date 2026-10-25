// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2AD8-0x800F2B64 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800137C4(void *);
#include "structs.h"
s32 fn_800F34F0(s32, s32, s32);
typedef struct {
    char pad0[0x10];
    s16 off1;
    char pad1[2];
    void *fn1;
    char pad2[0x30];
    s16 off2;
    char pad3[2];
    void *fn2;
} VT2AD8;
#define V1CALL() ((s32 (*)(void *))(*(VT2AD8 **)((char *)r31 + 0x50))->fn2)((char *)r31 + (*(VT2AD8 **)((char *)r31 + 0x50))->off2)
#define V2CALL() ((s32 (*)(void *))(*(VT2AD8 **)((char *)r31 + 0x50))->fn1)((char *)r31 + (*(VT2AD8 **)((char *)r31 + 0x50))->off1)

s32 fn_800F2AD8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    void *r31;
    sp8 = arg1;
    r31 = (void *)fn_800F34F0(arg0->unk0x24, &sp8, 1);
    if (r31 != 0) {
        goto bottom;
body:
        fn_800137C4(0);
bottom:
        if (V1CALL() == 0) {
            goto body;
        }
        return V2CALL();
    }
    return 0;
}
