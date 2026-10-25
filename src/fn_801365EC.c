// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801365EC-0x80136708 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
extern s32 lbl_80303434;
s32 DVDReadAsyncPrio(s32, s32, s32, s32, s32, s32);
void fn_801365EC(void);
void fn_801365EC(void) {
    s32 temp_r11;
    s32 temp_r4;
    s32 temp_r0;
    u32 mod2;
    s32 temp_r12;
    s32 idxv;
    char *p;
    char *aF0;
    char *aEC;
    char *aF8;
    char *aF4;
    register s32 cc __asm__("r9");

    p = lbl_8039D940;
    if (((Unk_74BF3C95 *)p)->unk0xB0 != 0) {
        return;
    }
    aF0 = p + 0xF0;
    aEC = p + 0xEC;
    aF8 = p + 0xF8;
    aF4 = p + 0xF4;
    temp_r11 = ((Unk_74BF3C95 *)p)->unk0xD0;
    cc = ((Unk_74BF3C95 *)p)->unk0xCC;
    ((Unk_74BF3C95 *)p)->unk0xCC = cc + temp_r11;
    *(s32 *)(aF0 + (((Unk_74BF3C95 *)p)->unk0xE4 << 4)) = temp_r11;
    temp_r4 = lbl_80303434 - 1;
    idxv = ((Unk_74BF3C95 *)p)->unk0xE4;
    temp_r0 = *(s32 *)(aEC + (idxv << 4));
    temp_r12 = *(s32 *)(temp_r0 + ((Unk_74BF3C95 *)p)->unk0xD0 - 0x1C);
    lbl_80303434 = temp_r4;
    ((Unk_74BF3C95 *)p)->unk0xD0 = temp_r12;
    *(s32 *)(aF8 + (((Unk_74BF3C95 *)p)->unk0xE4 << 4)) = 1;
    *(s32 *)(aF4 + (((Unk_74BF3C95 *)p)->unk0xE4 << 4)) = ((Unk_74BF3C95 *)p)->unk0xD4;
    ((Unk_74BF3C95 *)p)->unk0xD4 = ((Unk_74BF3C95 *)p)->unk0xD4 + 1;
    mod2 = (u32)((Unk_74BF3C95 *)p)->unk0xE4 + 1;
    mod2 = mod2 % 10;
    ((Unk_74BF3C95 *)p)->unk0xE4 = mod2;
    if (temp_r4 != 0) {
        if (DVDReadAsyncPrio((s32)(p + 8), *(s32 *)(aEC + (mod2 << 4)), ((Unk_74BF3C95 *)p)->unk0xD0, ((Unk_74BF3C95 *)p)->unk0xCC, (s32)fn_801365EC, 2) < 0) {
            ((Unk_74BF3C95 *)p)->unk0xB0 = 1;
        }
    } else {
        ((Unk_74BF3C95 *)p)->unk0xB8 = temp_r4;
        ((Unk_74BF3C95 *)p)->unk0xB4 = 1;
    }
}
