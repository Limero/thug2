// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196DA4-0x80196E7C (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80303150[];

s32 Tmr_GetTime(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void AddInteger(CStruct *, s32, s32);

register s32 g31 __asm__("r31");

void fn_80196DA4(void *arg0) {
    char *var_r9;
    s32 var_ctr;
    s32 temp_r3;
    s32 temp_r0;

    temp_r3 = Tmr_GetTime();
    temp_r0 = *(s32 *)&lbl_80303150 + temp_r3;
    ((Unk_A57A8CE9 *)arg0)->unk0x524 = 0;
    ((Unk_A57A8CE9 *)arg0)->unk0x52C = 0;
    ((Unk_A57A8CE9 *)arg0)->unk0x548 = 0;
    ((Unk_A57A8CE9 *)arg0)->unk0x528 = temp_r0;
    GetInteger(((Unk_A57A8CE9 *)arg0)->unk0x20, QB_BEAT_WINDOW_TIME,
                (s32 *)((char *)arg0 + (s32)0x544), 1);
    GetInteger(((Unk_A57A8CE9 *)arg0)->unk0x20, QB_TOTAL_TO_WIN,
                (s32 *)((char *)arg0 + (s32)0x54C), 1);
    AddInteger(((Unk_A57A8CE9 *)arg0)->unk0x20, QB_TRICKS_COMPLETED, 0);
    var_r9 = (char *)arg0 + (s32)0x74;
    var_ctr = 0x1E;
    arg0 = (char *)arg0 + (s32)0x550;
    do {
        ((Unk_DB0E2BAB *)var_r9)->unk0x14 = 1;
        ((Unk_DB0E2BAB *)var_r9)->unk0x0 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x4 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x10 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x8 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x20 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x24 = 1;
        ((Unk_DB0E2BAB *)var_r9)->unk0x18 = 0;
        *((s32 *)arg0) = 0;
        var_r9 += 0x28;
        arg0 = (char *)arg0 + 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
