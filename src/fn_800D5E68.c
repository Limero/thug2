// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5E68-0x800D5F10 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
void fn_800F078C(s32, void *);
void fn_800D8908(Unk_C7387A53 *, s32);
void *GetChecksum_3(void *, s32);
bool fn_800D5E68(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp18;
    s32 sp8[4];
    s32 temp_r30;
    void *temp_r3;
    Unk_C8FEE62D *temp_r9;

    sp18 = 0;
    GetChecksum_2(arg1, 0, &sp18, 0);
    temp_r30 = fn_800F0F84(sp18, 1);
    fn_800F078C(temp_r30, &sp8[0]);
    {
        void *u = (void *)arg0->unk0xC;
        __ps_t t0;
        __ps_t t1;
        t0 = ((__ps_t *)&sp8[0])[0];
        ((__ps_t *)u)[11] = t0;
        t1 = ((__ps_t *)&sp8[0])[1];
        ((__ps_t *)u)[12] = t1;
    }
    fn_800D8908(arg0, temp_r30);
    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    temp_r9 = ((CScript *)temp_r3)->unk0x18;
    ((s32 (*)(void *))temp_r9->unk0x14)(temp_r3 + * (s16 *) ((char *)temp_r9 + (s32)0x10));
    return true;
}
