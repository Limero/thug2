// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F36C8-0x800F3700 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0[0x88];
    s16 unk0x88;
    char pad1[0x2];
    s32 (*unk0x8C)(char *);
} TF36C8;

s32 fn_800F36C8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                s32 arg5)
{
    TF36C8 *temp_r9 = (TF36C8 *)arg0->unk0x50;

    temp_r9->unk0x8C((char *)arg0 + temp_r9->unk0x88);
    return 0;
}
