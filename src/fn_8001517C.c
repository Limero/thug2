// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001517C-0x800151F4 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// Per-object callback record reached through some_object->unk0x3C.
// 0x30 is a SIGNED halfword displacement, 0x34 the callback, 0x3C a link to
// another record of the same shape.
typedef struct VT_1517C {
    char pad0x0[0x30];
    s16 unk0x30;
    char pad0x32[0x2];
    void (*unk0x34)(void *);
    char pad0x38[0x4];
    struct VT_1517C *unk0x3C;
} VT_1517C;

extern Unk_C7387A53 *lbl_803C9C38[];
s32 fn_80013238(Unk_C7387A53 *self);

void fn_8001517C(void) {
    s32 i;
    Unk_C7387A53 *e;
    Unk_C7387A53 *e2;
    for (i = 0; i < 0x10; i++) {
        e = lbl_803C9C38[i];
        if (e != NULL) {
            if (fn_80013238(e) != 0) {
                VT_1517C *v;
                e2 = lbl_803C9C38[i];
                v = ((VT_1517C *)e2)->unk0x3C;
                v->unk0x34((char *)e2 + v->unk0x30);
            }
        }
    }
}
