// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136BE4-0x80136CAC (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
extern char lbl_8039DAE0[];
void fn_80136888();
s32 DVDConvertPathToEntrynum(const char *);
s32 DVDFastOpen(s32, void *);
s32 DVDReadAsyncPrio(void *, void *, s32, s32, void (*)(void), s32);
s32 DVDClose(void *);
char *strncpy(char *, const char *, s32);

bool fn_80136BE4(char *path) {
    char *base = lbl_8039D940;
    s32 temp_r30;
    s32 temp_r0;
    register s32 ret __asm__("r3");

    temp_r30 = ((Unk_F5D97A51 *)base)->unk0xAC;
    if (temp_r30 != 0) {
        return false;
    }
    ((Unk_F5D97A51 *)base)->unk0xC0 = temp_r30;
    temp_r0 = DVDConvertPathToEntrynum(path);
    if (temp_r0 == -1) {
        return false;
    }
    ret = 0;
    if (DVDFastOpen(temp_r0, base + 8) == 0) {
        return false;
    }
    __asm__("" : "+r"(base));
    ((Unk_F5D97A51 *)base)->unk0xC0 = 1;
    if (DVDReadAsyncPrio(base + 8, lbl_8039DAE0, 0x20, 0,
                         fn_80136888, 2) < 0) {
        __asm__("" : "+r"(base));
        DVDClose(base + 8);
        return false;
    }
    strncpy(base + 0x44, path, 0x40);
    ((Unk_F5D97A51 *)base)->unk0x83 = (u8)temp_r30;
    return true;
}
