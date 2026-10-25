// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002E34C-0x8002E3A8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80305F9C[];
s32 *fn_8021B55C(s32 arg0, s32 arg1);
void fn_80031EC8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

typedef struct {
    char pad0[0x64];
    u32 unk0x64;
    char pad1[0x10];
    void *unk0x78;
} O2E34C;

typedef struct {
    char pad0[0x18];
    s32 unk0x18;
} N2E34C;

void fn_8002E34C(O2E34C *arg0) {
    s32 *p;

    p = fn_8021B55C(*(s32 *)lbl_80305F9C, 0);
    fn_80031EC8(arg0, ((N2E34C *)arg0->unk0x78)->unk0x18,
                ((arg0->unk0x64 >> 29) & 1) ^ 1, *p, 1);
}
