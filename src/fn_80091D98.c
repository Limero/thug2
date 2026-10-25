// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80091D98-0x80091DD4 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Registers a 0x60-byte .bss buffer (lbl_803792D8) with fn_8026A07C, passing
// a saved value from lbl_803017F4 and a callback (fn_80091CF8). The two
// 0x8xxxxxxx addresses are extern symbols so ngccc emits the lis+addi
// (address) form rather than lis+ori. Suggested rename:
// RegisterAudioBufferWithCallback.
#include "types.h"
extern char lbl_803792D8[];
extern char lbl_803017F4[];
extern void fn_80091CF8(void);
s32 fn_8026A07C(void *, void *, void *, void *);
void fn_80091D98(void) {
    fn_8026A07C(lbl_803792D8, *(s32 *)&lbl_803017F4, 0x60, (void *)fn_80091CF8);
}