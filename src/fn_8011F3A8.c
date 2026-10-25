// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011F3A8-0x8011F590 (488B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_80302E04[];
extern void *lbl_80302E24[];
extern s32 lbl_80302E44[];
extern s32 lbl_80302E64[];
extern void *lbl_80302E84[];
extern s32 lbl_80302EA4[];
extern void *lbl_80302EC4[];
extern s32 DefaultTexData[];
extern s32 DVDReadAsyncPrio(void *, void *, s32, s32, void *, s32);
s32 fn_8011F3A8(void *fileInfo, void *addr, s32 length, s32 offset, void *cb) {
    s32 i;
    s32 found = 0;
    s32 slot;

    for (i = 0; i < 8; i++) {
        if (fileInfo == lbl_80302E04[i] && addr == lbl_80302E24[i] &&
            length == lbl_80302E44[i] && offset == lbl_80302E64[i]) {
            found = 1;
            break;
        }
    }
    if (found) {
        slot = -1;
        for (i = 0; i < 8; i++) {
            if (DefaultTexData[i] == -1) {
                slot = i;
                break;
            }
        }
        if (slot == -1) {
            DVDReadAsyncPrio(fileInfo, addr, length, offset, cb, 2);
        }
        lbl_80302E84[slot] = cb;
        lbl_80302EA4[slot] = length;
        lbl_80302EC4[slot] = fileInfo;
        DefaultTexData[slot] = 8;
        return 1;
    }
    for (i = 6; i >= 0; i--) {
        lbl_80302E04[i + 1] = lbl_80302E04[i];
        lbl_80302E24[i + 1] = lbl_80302E24[i];
        lbl_80302E44[i + 1] = lbl_80302E44[i];
        lbl_80302E64[i + 1] = lbl_80302E64[i];
    }
    lbl_80302E04[0] = fileInfo;
    lbl_80302E24[0] = addr;
    lbl_80302E44[0] = length;
    lbl_80302E64[0] = offset;
    return DVDReadAsyncPrio(fileInfo, addr, length, offset, cb, 2);
}
