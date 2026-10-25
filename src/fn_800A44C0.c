// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A44C0-0x800A456C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* Array element: 5 s32 words, stride 0x14 (see the sibling fn_800A456C). */
typedef struct {
    s32 unk0x0;   /* script handle — tested, then passed as fn_800A5BF4's arg1 */
    s32 unk0x4;   /* reset to QB_NULL_SCRIPT whenever bit 0x40000000 of unk0x10 is set */
    s32 unk0x8;
    s32 unk0xC;   /* freed through CStruct_delete(ptr, 3) and cleared */
    s32 unk0x10;  /* flags: bit 0x40000000 selects the reset */
} Node_t;

s32 fn_800A5BF4(void *, void *, s32);
void CStruct_delete(void *, s32);
extern void * lbl_80301A78;

void fn_800A44C0(CStruct *arg0, s32 arg1) {
    Node_t *node;
    s32 script;
    s32 free_me;
    s32 i;
    s32 count;

    i = 0;
    count = arg0->unk0x4;
    if (i < count) {
        do {
            node = (Node_t *)((char *)arg0->unk0x0 + i * 0x14);
            if (node->unk0x10 & QB_UNKNOWN_0x40000000) {
                script = *(s32 *)((char *)arg0->unk0x0 + i * 0x14);
                if (script != 0) {
                    fn_800A5BF4(lbl_80301A78, script, arg1);
                }
                free_me = node->unk0xC;
                node->unk0x4 = QB_NULL_SCRIPT;
                if (free_me != 0) {
                    CStruct_delete(free_me, 3);
                    node->unk0xC = 0;
                }
            }
            count = arg0->unk0x4;
            i += 1;
        } while (i < count);
    }
}
