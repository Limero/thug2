// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012543C-0x80125480 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80303248;
typedef struct MemNode {
    s32 unk0x0;
    s32 unk0x4;
    char _pad0x8[8];
    struct MemNode *unk0x10;
} MemNode;
void fn_8012543C(s32 arg0) {
    register s32 a0 __asm__("r8");
    register s32 node __asm__("r3");
    a0 = arg0;
    node = *((s32 *)(((a0 * 4) & 0x3FFC) + *(s32 *)&lbl_80303248));
    if ((node != NULL) && (((MemNode *)node)->unk0x4 != a0)) {
loop_2:
        node = (s32)((MemNode *)node)->unk0x10;
        if (node != NULL) {
            if (((MemNode *)node)->unk0x4 == a0) {
                return;
            }
            goto loop_2;
        }
    }
}
