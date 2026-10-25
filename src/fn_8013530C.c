// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013530C-0x80135424 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_801352A8(CStruct *, s32);
void *fn_80134E1C(Unk_F8A5095F *, s32);
u32 strlen(const char *);
void *fn_8013530C(Unk_1D62F22E *arg0, s32 arg1) {
    s32 temp_r0;
    s32 lo1 = 1;
    s32 temp_r9;
    void *var_r31;

    temp_r0 = arg0->unk0x2;
    var_r31 = (char *)arg0 + 0x14;
    if (temp_r0 == 5) {
        goto Lc5;
    }
    if (temp_r0 > 5) {
        goto Lhi;
    }
    if (temp_r0 < lo1) {
        goto Lexit;
    }
    if (temp_r0 <= 2) {
        goto Lexit;
    }
    goto Lstr;
Lhi:
    if (temp_r0 == 10) {
        goto Lc10;
    }
    if (temp_r0 > 10) {
        goto Lhi2;
    }
    if (temp_r0 == 6) {
        goto Lc6;
    }
    if (temp_r0 == 7) {
        goto Lc7;
    }
    goto Lexit;
Lhi2:
    if (temp_r0 == 12) {
        goto Lc12;
    }
    goto Lexit;
Lstr:
    arg0->unk0xC += arg1;
    var_r31 += (strlen((const char *)(arg0->unk0xC)) + 4) & ~3;
    goto Lexit;
Lc7:
    temp_r9 = ((Unk_9994C3F5 *)var_r31)->unk0x8;
    arg0->unk0xC += arg1;
    var_r31 = (char *)arg0 + 0x20;
    var_r31 += (temp_r9 + 3) & ~3;
    goto Lexit;
Lc6:
    var_r31 = (char *)arg0 + 0x24;
    arg0->unk0xC += arg1;
    goto Lexit;
Lc5:
    var_r31 = (char *)arg0 + 0x20;
    arg0->unk0xC += arg1;
    goto Lexit;
Lc10:
    arg0->unk0xC += arg1;
    var_r31 = fn_801352A8((void *)(arg0->unk0xC), arg1);
    goto Lexit;
Lc12:
    arg0->unk0xC += arg1;
    var_r31 = fn_80134E1C((void *)(arg0->unk0xC), arg1);
    goto Lexit;
Lexit:
    return var_r31;
}
