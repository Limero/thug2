// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800546A0-0x80054720 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// structs.h has no class for the sentinel-tagged list link (payload
// pointer at +0x4 doubling as the -1 terminator tag, next link at +0xC), so
// the node is described locally.  structs.h DOES have the payload class.
typedef struct IdleListNode IdleListNode;
struct IdleListNode {
    s32 unk0x0;
    Unk_FFAD6788 *unk0x4;   /* payload; == (void *)-1 marks the terminator */
    s32 unk0x8;
    IdleListNode *unk0xC;   /* next link */
};

extern IdleListNode *lbl_80364C28;
s32 fn_80055E74(Unk_FFAD6788 *, s32);

s32 fn_800546A0(s32 arg0) {
    s32 temp_r0;
    s32 var_r3;
    IdleListNode *temp_r9;
    IdleListNode *var_r11;
    IdleListNode *var_r31;

    var_r11 = lbl_80364C28;
    if ((s32) var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9 = var_r11->unk0xC;
            temp_r0 = (s32) temp_r9->unk0x4;
            var_r31 = temp_r9;
            if (temp_r0 == -1) {
                var_r31 = NULL;
            }
            var_r3 = fn_80055E74(var_r11->unk0x4, arg0);
            if (var_r3 != 0) {
                return var_r3;
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
    return 0;
}
