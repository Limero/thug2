// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D1380-0x801D1458 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-interblock
#include "types.h"

/* M6.89d: the corpus-merged Unk_71062261 has 0x15A8 inside a pad region and
   types 0x15BC as `s32`; both are really pointers.  File-local typedef. */
typedef struct {
    char pad0x0[0x15A8];
    void *unk0x15A8;
    char pad0x15AC[0x10];
    void *unk0x15BC;
    char pad0x15C4[0x1];
} Rec_801D1380;

extern s32 lbl_80303150;      /* .data:0x80303150, size 0x4 */
s32 Tmr_GetTime(void);        /* .text:0x80124F44, scope:global */

void fn_801D1380(Rec_801D1380 *arg0) {
    s32 *node;
    s32 count = 0x17;
    s32 f;

    do {
        if (count != 1) {
            node = (s32 *)((char *)((s32)(count * 0xC) + (s32)arg0->unk0x15BC));
            node = (s32 *)((char *)node + 0x24);
            f = 1;
            if (node[1] != f) {
                node[1] = f;
                node[2] = lbl_80303150 + Tmr_GetTime();
            }
            if (count == 7) {
                *(s32 *)((char *)arg0->unk0x15A8 + 0x24) = f;
            }
            node = (s32 *)((char *)((s32)(count * 0xC) + (s32)arg0->unk0x15BC));
            node = (s32 *)((char *)node + 0x24);
            f = 0;
            if (node[1] != f) {
                node[1] = f;
                node[2] = lbl_80303150 + Tmr_GetTime();
            }
            if (count == 7) {
                *(s32 *)((char *)arg0->unk0x15A8 + 0x24) = f;
            }
        }
    } while (0 != count--);
}
