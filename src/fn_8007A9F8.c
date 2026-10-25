// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007A9F8-0x8007AB20 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8000F320(void *);
void fn_80010E78(s32 arg0);
void fn_80010D94(s32 arg0, s32 arg1);
void fn_8000F2F8(void *, void *);
#include "structs.h"
#include "mem.h"
s32 fn_80078330(s32, s32, s32, s32);
void *memset(void *, s32, u32);
extern char lbl_802FFE98[];
void fn_8007A334(s32, s32);
bool fn_8007A9F8(Unk_C7387A53 *arg0) {
    s32 temp_r28;
    s32 temp_r3;
    Unk_80E276D1 *temp_r11;
    Unk_F5317C5D *temp_r3_2;
    Unk_9994C3F5 *temp_r3_3;
    Unk_86129748 *temp_r9;
    Unk_86129748 *temp_r9_3;

    temp_r9 = arg0->unk0xC;
    if (temp_r9->unk0xA & 0x200) {
        temp_r3 = Mem_Alloc((u16) (1 << *(u8 *) ((char *) temp_r9 + 0x6)) * (u16) (1 << *(u8 *) ((char *) temp_r9 + 0x7)) * 4);
        *(s32 *) (*(s32 *) ((char *) ((char *) arg0) + 0xC) + 0x18) = temp_r3;
        temp_r3_2 = arg0->unk0xC;
        fn_80078330((s32) temp_r3_2, temp_r3_2->unk0x10, temp_r3, *((u16 *) &temp_r3_2->unk0xA));
    } else {
        temp_r3_3 = *(void **) lbl_802FFE98;
        fn_8000F2F8(temp_r3_3, temp_r3_3->unk0x118);
        fn_80010D94(*(s32 *) ((char *) (*(void **) lbl_802FFE98) + 0x118), 0x20);
        temp_r9_3 = arg0->unk0xC;
        temp_r28 = Mem_Alloc((u16) (1 << *(u8 *) ((char *) temp_r9_3 + 0x6)) * (u16) (1 << *(u8 *) ((char *) temp_r9_3 + 0x7)) * 4);
        temp_r11 = arg0->unk0xC;
        memset((void *) temp_r28, 0xFF, (u16) (1 << *(u8 *) ((char *) temp_r11 + 0x6)) * (u16) (1 << *(u8 *) ((char *) temp_r11 + 0x7)) * 4);
        *(s32 *) (*(s32 *) ((char *) ((char *) arg0) + 0xC) + 0x18) = temp_r28;
        fn_8007A334((s32) arg0, 0);
        fn_80010E78(*(s32 *) ((char *) (*(void **) lbl_802FFE98) + 0x118));
        fn_8000F320(*(void **) lbl_802FFE98);
    }
    return true;
}
