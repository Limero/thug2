// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136338-0x8013644C (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
extern bool lbl_8039D9F0;
void fn_80136280(void);
void fn_80136338(s32 arg0) {
    s32 temp_r10;
    register s32 temp_r9 __asm__("r9");
    char *p;
    register char *p2 __asm__("r11");
    char *aF4;
    char *aF0;
    char *aF8;
    char *aEC;
    register char *aF8b __asm__("r10");
    register u32 m __asm__("r9");

    if (arg0 == -1) {
        lbl_8039D9F0 = 1;
        return;
    }
    if (arg0 == -3) {
        return;
    }
    p = lbl_8039D940;
    aF4 = p + 0xF4;
    aF0 = p + 0xF0;
    aF8 = p + 0xF8;
    ((Unk_C6CED771 *)p)->unk0xBC = 0;
    *(s32 *)(aF4 + (((Unk_C6CED771 *)p)->unk0xE4 << 4)) = ((Unk_C6CED771 *)p)->unk0xD4;
    *(s32 *)(aF0 + (((Unk_C6CED771 *)p)->unk0xE4 << 4)) = arg0;
    *(s32 *)(aF8 + (((Unk_C6CED771 *)p)->unk0xE4 << 4)) = 1;
    temp_r10 = ((Unk_C6CED771 *)p)->unk0xD0;
    temp_r9 = ((Unk_094E2326 *)p)->unk0xD4 + 1U;
    ((Unk_C6CED771 *)p)->unk0xD4 = temp_r9;
    ((Unk_C6CED771 *)p)->unk0xCC = ((Unk_C6CED771 *)p)->unk0xCC + temp_r10;
    if (temp_r9 < ((Unk_C6CED771 *)p)->unk0x9C) {
        aEC = p + 0xEC;
        ((Unk_C6CED771 *)p)->unk0xD0 = *(s32 *)(*(s32 *)(aEC + (((Unk_C6CED771 *)p)->unk0xE4 << 4)) + temp_r10 - 0x1C);
    } else {
        ((Unk_C6CED771 *)p)->unk0xD0 = 0;
    }
    p2 = lbl_8039D940;
    m = (u32)((Unk_B6371D19 *)p2)->unk0xE4;
    m = (m + 1) % 10;
    ((Unk_B6371D19 *)p2)->unk0xE4 = m;
    aF8b = p2 + 0xF8;
    if (*(s32 *)(aF8b + (m << 4)) == 0) {
        fn_80136280();
    }
}
