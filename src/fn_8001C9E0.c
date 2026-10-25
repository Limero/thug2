// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001C9E0-0x8001CA24 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_803213CC;
extern void *lbl_803213D0;
extern void *lbl_803213D4;
void VISetNextFrameBuffer(void *);
void VIFlush(void);
void VIWaitForRetrace(void);
void __hwInitVI(void) {
    VISetNextFrameBuffer(lbl_803213CC);
    lbl_803213D4 = lbl_803213D0;
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}
