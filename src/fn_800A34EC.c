// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A34EC-0x800A3528 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0[0x20];
    s16 unk0x20;
    char pad1[0x2];
    s32 (*unk0x24)(char *, void *, s32);
} TA34EC;

void fn_800A34EC(Unk_C7387A53 *arg0, CScript *arg1, s32 arg2)
{
    TA34EC *temp_r9;

    arg1->unk0x34 = arg2;
    temp_r9 = (TA34EC *)arg0->unk0x2C;
    temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20, arg1, arg1->unk0x18);
}
