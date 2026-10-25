// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBBC4-0x800CBC24 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"

typedef struct Node_800CBBC4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    struct Node_800CBBC4 *unkC;
} Node_800CBBC4;

typedef struct Obj_800CBBC4 {
    char _pad0x00[0x38];
    Node_800CBBC4 *unk38;
} Obj_800CBBC4;

void fn_8002F754(void *arg0, f32 farg1);

void fn_800CBBC4(Obj_800CBBC4 *arg0, f32 farg0) {
    volatile double _dummy;
    Node_800CBBC4 *p;
    Node_800CBBC4 *q;

    p = arg0->unk38;
    __asm__("" : "+r"(p));
    __asm__("" : : "r"(arg0));
    goto test;
body:
    fn_8002F754(q, farg0);
    p = q->unkC;
    goto test;
test:
    if (p->unk4 == -1) {
        p = NULL;
    }
    q = p;
    __asm__("" : "+r"(p));
    if (q != NULL) {
        goto body;
    }
}
