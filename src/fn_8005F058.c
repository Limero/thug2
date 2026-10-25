// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005F058-0x8005F098 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct VT_7A53 {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x10];
    s16 unk0x20;
    char pad0x22[0x2];
    void (*unk0x24)(void *);
} VT_7A53;

void fn_8005F058(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    VT_7A53 *temp_r9;

    *(s32 *)((char *)arg0 + 0x10) = arg3;
    *(s32 *)((char *)arg0 + 0x4) = 1;
    temp_r9 = *(VT_7A53 **)((char *)arg0 + 0x14);
    temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
}
