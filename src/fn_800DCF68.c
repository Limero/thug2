// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DCF68-0x800DCFF0 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Model setup: fetches the QB_MODEL object into arg0+0x44, builds a
// sub-arg via fn_800F2AD8, then dispatches through the handler at
// temp_r9->unk0x44 when arg0->unk0x1C is non-NULL.
// Suggested rename: SetupModelAndDispatch
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_800F2AD8(void *, s32, s32);
extern s32 lbl_80301B48;
void fn_800DCF68(Unk_C8FEE62D *arg0) {
    s32 temp_r3_2;
    void *temp_r10;
    CScript *temp_r3;
    Unk_DB0E2BAB *temp_r9;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    arg0->unk0x44 = temp_r3;
    {
        s32 arg0v = lbl_80301B48;
        temp_r3_2 = fn_800F2AD8(arg0v, *(s32 *)(temp_r3->unk0x210 + 0x34), 0);
    }
    temp_r10 = arg0->unk0x1C;
    if (temp_r10 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r10)->unk0x8;
        ((s32 (*)(void *, void *, void *))temp_r9->unk0x44)(temp_r10 + temp_r9->unk0x40, *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x44) + 0x210), temp_r3_2);
    }
}
