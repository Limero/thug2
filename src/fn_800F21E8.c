// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F21E8-0x800F2270 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009C8A8(void *, void *);
void fn_800F3334(s32, void *);
#include "structs.h"
s32 fn_800F2CF0(void *, s32);
extern char lbl_8029B418[];
typedef struct { char pad0x0[0x18]; s16 unk0x18; char pad0x1A[2]; s32 unk0x1C; } ViewF21E8;
void fn_800F21E8(Unk_78674569 *arg0, s32 arg1) {
    void *temp_r11;
    ViewF21E8 *temp_r9;

    arg0->unk0x14 = (s32)lbl_8029B418;
    fn_800F2CF0(arg0, 1);
    if ((s32) arg0->unk0x24 != 0) {
        fn_800F3334((s32) arg0->unk0x24, 3);
    }
    temp_r11 = arg0->unk0x40;
    if (temp_r11 != NULL) {
        temp_r9 = (ViewF21E8 *)((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
    }
    fn_8009C8A8(arg0, arg1);
}
