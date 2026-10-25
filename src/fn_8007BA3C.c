// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BA3C-0x8007BAA8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80058800(s32, s32);
extern char lbl_80295BD8[];
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    char pad0xA[0x2];
    s32 unk0xC;
} Unk_8007BA3C_vt;
void fn_8007BA3C(Unk_C7387A53 *arg0, s32 arg1) {
    void *temp_r11;
    Unk_8007BA3C_vt *temp_r9;

    temp_r11 = arg0->unk0x54;
    arg0->unk0x50 = (s32)lbl_80295BD8;
    if (temp_r11 != NULL) {
        temp_r9 = *(Unk_8007BA3C_vt **)((char *)temp_r11 + 0x10);
        ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)temp_r11 + temp_r9->unk0x8, 3);
    }
    fn_80058800(arg0, arg1);
}
