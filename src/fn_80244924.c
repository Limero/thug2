// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80244924-0x802449DC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801F9594(Unk_C7387A53 *, s32);
void fn_80243F88(Unk_C8FEE62D *, s32);
void fn_80244924(Unk_5AA7B5D7 *arg0) {
    void *temp_r31;
    void *temp_r31_2;
    Unk_5AA7B5D7 *temp_r9;
    CScript *var_r3;
    CStruct *var_r3_2;

    var_r3 = arg0->unk0xC;
    if (var_r3 != NULL) {
        do {
            temp_r31 = var_r3->unk0x18;
            if (var_r3 != NULL) {
                fn_80243F88(var_r3, 3);
            }
            var_r3 = temp_r31;
        } while (var_r3 != NULL);
    }
    arg0->unk0xC = 0;
    temp_r9 = (char *)arg0 + 1;
    *(u8 *)((char *)arg0 + (s32)0x8) = 0xFF;
    *(u8 *)((char *)arg0 + (s32)0x7) = 0xFF;
    *(u8 *)((char *)arg0 + (s32)0xA) = 0;
    *(u8 *)((char *)arg0 + (s32)0x9) = 0;
    *(u8 *)((char *)arg0 + (s32)0x1) = 0;
    *(u8 *)((char *)temp_r9 + (s32)0x1) = 0;
    *(u8 *)((char *)temp_r9 + (s32)0x2) = 0;
    *(u8 *)((char *)temp_r9 + (s32)0x3) = 0;
    *(u8 *)((char *)temp_r9 + (s32)0x4) = 0;
    *(u8 *)((char *)temp_r9 + (s32)0x5) = 0;
    var_r3_2 = arg0->unk0x10;
    if (var_r3_2 != NULL) {
        do {
            temp_r31_2 = var_r3_2->unk0x4;
            if (var_r3_2 != NULL) {
                fn_801F9594(var_r3_2, 3);
            }
            var_r3_2 = temp_r31_2;
        } while (var_r3_2 != NULL);
    }
    arg0->unk0x10 = NULL;
}
