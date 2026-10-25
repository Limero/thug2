// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CB178-0x800CB218 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);

typedef struct {
    char pad0x0[0x18];
    s16 unk0x18;
    char pad0x1A[0x2];
    s32 unk0x1C;
} VT_t;

void fn_800CB178(Unk_DB0E2BAB *arg0) {
    VT_t *temp_r9;
    register s32 t __asm__("r9");
    void *p;
    s32 fp;

    t = arg0->unk0x38;
    goto check;
    do {
        temp_r9 = *(VT_t **)((char *)p + 0x14);
        fp = temp_r9->unk0x1C;
        __asm__("" : "+r"(fp));
        ((s32 (*)(void *))fp)(p + temp_r9->unk0x18);
        t = ((Unk_C8FEE62D *)p)->unk0xC;
    check:;
        if (((Unk_C8FEE62D *)t)->unk0x4 == -1) {
            t = 0;
        }
        p = (void *)t;
    } while (p != NULL);
    arg0->unk0x20 = GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    arg0->unk0x24 = GetChecksum_3(arg0->unk0xC, QB_MODEL);
    arg0->unk0x1C = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
}
// FLAG: -fno-schedule-insns
