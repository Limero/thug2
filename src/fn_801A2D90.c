// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2D90-0x801A2E28 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct NodeA2CF8 {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x4];
    struct NodeA2CF8 *unk0xC;
} NodeA2CF8;

typedef struct ObjA2CF8 {
    char pad0x0[0x64];
    NodeA2CF8 *unk0x64;
} ObjA2CF8;

void *fn_801A26E0(void *, s32);
void *fn_801A275C(void *, s32);
s32 fn_800AB3E4(Unk_C7387A53 *, s32);

bool fn_801A2D90(ObjA2CF8 *arg0, s32 arg1, Unk_C7387A53 *arg2) {
    NodeA2CF8 *p;
    s32 count;
    void *temp_r3;

    p = arg0->unk0x64;
    count = 0;
    while ((p->unk0x4 == -1 ? (p = NULL) : p), p != NULL) {
        p = p->unk0xC;
        count++;
    }
    if (count == 0) {
        return false;
    }
    if (arg1 == 0) {
        fn_800AB3E4(fn_801A26E0(arg0, 0), arg2);
    } else {
        temp_r3 = fn_801A275C(arg0, arg1);
        if (temp_r3 != NULL) {
            fn_800AB3E4(temp_r3, arg2);
        }
    }
    return true;
}
