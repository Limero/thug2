// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801439C0-0x80143AF4 (308B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80303150;
void fn_801CAEF8(s32);
s32 GetChecksum_3(s32, s32);
void fn_801F043C(s32);
s32 Tmr_GetTime(void);
void fn_800AAB54(s32);
void Script_RunScript(s32, s32, void *, s32, s32);

void fn_801439C0(Unk_9D99273B *arg0) {
    Unk_7258DEBD *temp_r30;
    CStruct *temp_r31;
    Unk_89391A04 *temp_r9;
    register s32 var_r26 __asm__("r26");
    register s32 var_r27 __asm__("r27");
    s32 one;
    s32 zero;

    var_r26 = 0;
    __asm__ volatile ("");
    fn_801CAEF8(arg0->unk0x2A4);
    one = 1;
    var_r27 = 0;
    fn_801F043C(GetChecksum_3((s32)arg0, QB_SKATERBALANCETRICK));
    temp_r9 = arg0->unk0x8;
    ((void (*)(void *))temp_r9->unk0x9C)((char *)arg0 + temp_r9->unk0x98);
    do {
        temp_r30 = arg0->unk0x2AC;
        temp_r31 = (s32 *)((char *)var_r27 + temp_r30->unk0x15BC);
        temp_r31 = (s32 *)((char *)temp_r31 + (s32)0x24);
        if (temp_r31->unk0x4 != 1) {
            temp_r31->unk0x4 = one;
            temp_r31->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
        if (var_r26 == 7) {
            *(s32 *)(temp_r30->unk0x15A8 + (s32)0x24) = one;
        }
        zero = 0;
        temp_r30 = arg0->unk0x2AC;
        temp_r31 = (s32 *)((char *)var_r27 + temp_r30->unk0x15BC);
        temp_r31 = (s32 *)((char *)temp_r31 + (s32)0x24);
        if (temp_r31->unk0x4 != 0) {
            temp_r31->unk0x4 = zero;
            temp_r31->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
        if (var_r26 == 7) {
            *(s32 *)(temp_r30->unk0x15A8 + (s32)0x24) = zero;
        }
        var_r26 += 1;
        var_r27 += 0xC;
    } while (var_r26 <= 0x17);
    fn_800AAB54(arg0->unk0x290 + 0x24);
    Script_RunScript(QB_INITSKATERPARTICLES, 0, arg0, 0, 0);
}
