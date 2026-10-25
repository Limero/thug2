// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001D768-0x8001D814 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u32 lbl_803627E4;
extern u32 lbl_803629F4[2];
extern u32 lbl_803629FC[2];
extern u32 lbl_80362A94;
extern u32 lbl_80362A98;
extern u32 lbl_80362A9C;
extern u32 lbl_80362AA0[2];
extern u32 lbl_80362AA8;
extern u32 lbl_80362AAC;
extern u32 lbl_80362AB0;
extern u32 lbl_80362AB4;
extern u32 lbl_80362AB8;
extern u32 lbl_80362ABC;
u32 ARGetBaseAddress(void);
void fn_8001D768(void) {
    u32 base;
    u32 *p_aac;
    lbl_80362A94 = 0;
    lbl_80362A98 = 0;
    lbl_80362A9C = 0;
    lbl_80362AA0[0] = 0;
    p_aac = &lbl_80362AAC;
    base = ARGetBaseAddress();
    *p_aac = base;
    lbl_80362AB4 = 0x00FFFC00;
    lbl_80362AB8 = 0x00FFF800;
    lbl_80362ABC = 0x00FFF7FC;
    lbl_80362AB0 = 0x00FFF7FC;
    lbl_803627E4 = base;
    lbl_803629F4[0] = 0x00FFFC00;
    lbl_803629FC[0] = 0x00FFF800;
    lbl_80362AA8 = 0x00FFF7FC;
}
