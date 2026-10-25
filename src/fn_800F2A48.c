// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2A48-0x800F2AD8 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800137C4(void *);
#include "structs.h"
s32 fn_800F34F0(s32, s32, s32);
typedef struct {
    char pad0[0x48];
    s16 off;
    char pad1[2];
    void *fn;
} VT2A48;
#define VCALL() ((s32 (*)(void *))(*(VT2A48 **)((char *)r31 + 0x50))->fn)((char *)r31 + (*(VT2A48 **)((char *)r31 + 0x50))->off)

void *fn_800F2A48(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    void *r31;
    sp8 = arg1;
    r31 = (void *)fn_800F34F0(arg0->unk0x24, &sp8, 1);
    if (r31 == 0) {
        goto done;
    }
    if (VCALL() != 0) {
        goto done;
    }
    goto bottom;
body:
    fn_800137C4(0);
bottom:
    if (VCALL() == 0) {
        goto body;
    }
done:
    return r31;
}
