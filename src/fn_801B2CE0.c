// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2CE0-0x801B2EAC (460B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
extern f32 lbl_802ABFF4;
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_800F0838(void *, Unk_9994C3F5 *);
s32 GetFloat(CStruct *, s32, f32 *, s32);

void fn_801B2CE0(Unk_3336C6BE *arg0, CStruct *arg1) {
    register s32 zero __asm__("r30");
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    __ps_t *src;

    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    sp8 = 0;
    if ((GetChecksum_2(arg1, QB_SKELETONNAME, &sp8, 0) != 0) && (sp8 == QB_PED_FEMALE)) {
        arg0->unk0x20 = 1;
    }
    zero = 0;
    spC = zero;
    GetStructure_2(arg1, QB_PROFILE, &spC, 0);
    if (spC != 0) {
        sp10 = zero;
        GetStructure_2(spC, QB_BOARD, &sp10, 0);
        if (sp10 != 0) {
            sp14 = zero;
            if (GetChecksum_2(sp10, QB_DESC_ID, &sp14, NULL) != 0) {
                arg0->unk0x24 |= 1;
            }
        }
    }
    GetChecksum_2(arg1, QB_NAME, (char *)arg0 + 0x58, 1);
    fn_800F0838(arg0->unk0x58, (char *)arg0 + 0x68);
    arg0->unk0xD8 = lbl_802ABFF4;
    src = arg0->unk0xC;
    arg0->unk0xB8 = src[17];
    arg0->unk0xC0 = src[18];
    arg0->unk0xA8 = arg0->unk0xB8;
    arg0->unk0xB0 = arg0->unk0xC0;
    arg0->unk0xC8 = arg0->unk0xB8;
    arg0->unk0xD0 = arg0->unk0xC0;
    GetFloat(arg1, QB_STICKTOGROUNDDISTABOVE, (char *)arg0 + 0xDC, 0);
    GetFloat(arg1, QB_STICKTOGROUNDDISTBELOW, (char *)arg0 + 0xE0, 0);
    {
        register __ps_t *s9 __asm__("r9");
        s9 = arg0->unk0xC;
    arg0->unk0x148 = s9[26];
    arg0->unk0x150 = s9[27];
    arg0->unk0x158 = s9[28];
    arg0->unk0x160 = s9[29];
    arg0->unk0x168 = s9[30];
    arg0->unk0x170 = s9[31];
    arg0->unk0x178 = s9[32];
    arg0->unk0x180 = s9[33];
    }
}
