// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011ECA0-0x8011ED40 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_8038EBB8[];
extern char lbl_80302CFC[];
extern char lbl_8037B778[];
extern char fn_8011E8D0[];

s32 OSGetSoundMode(void);
void AXRegisterCallback(s32);
void memset(void *, s32, s32);
void DCFlushRange(void *, s32);
void fn_8001D4FC(s32, void *, s32);
void CleanUpSoundFX(void);
void Pcm_Init(void);

// InitSoundFX @ 0x8011ECA0
void InitSoundFX(void) {
    s32 buf[0x100];
    s32 *p;
    s32 i;
    s32 v;

    i = 0x3B;
    p = (s32 *)lbl_8038EBB8;
    p = (s32 *)((char *)p + 0x1D0);
    do {
        *p = 0;
        p = (s32 *)((char *)p - 8);
    } while (--i != 0);

    if (OSGetSoundMode() == 0) {
        v = 0;
    } else {
        v = 1;
    }
    *(s32 *)lbl_80302CFC = v;

    AXRegisterCallback((s32)fn_8011E8D0);
    memset(buf, 0, 0x400);
    DCFlushRange(buf, 0x400);
    fn_8001D4FC(*(s32 *)lbl_8037B778, buf, 0x400);
    CleanUpSoundFX();
    Pcm_Init();
}
