// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041338-0x80041460 (296B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-thread-jumps
#include "types.h"

typedef struct Unk_59AB5482 {
    struct Unk_59AB5482 *unk0x0;
    struct Unk_59AB5482 *unk0x4;
    struct Unk_59AB5482 *unk0x8;
} Unk_59AB5482;

typedef struct Unk_31DE137E {
    char pad0x0[0x64];
    struct Unk_C8FEE62D *unk0x64;
} Unk_31DE137E;

typedef struct Unk_C8FEE62D {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1C[0x54];
    struct Unk_C8FEE62D *unk0x70;
} Unk_C8FEE62D;

void CObject_AddRefLink(Unk_59AB5482 *, Unk_59AB5482 *);
void CObject_RemoveRefLink(Unk_59AB5482 *, Unk_59AB5482 *);

s32 *fn_80041338(Unk_59AB5482 *arg0, Unk_31DE137E *arg1, s32 arg2, s32 *arg3) {
    Unk_59AB5482 sp8;
    s32 *sp8a;
    register Unk_59AB5482 *sp8p __asm__("r26");
    s32 *temp_r31;
    s32 *temp_r3;
    s32 var_r30;

    var_r30 = 0;
    sp8a = (s32 *)&sp8;
    sp8a[1] = 0;
    sp8a[2] = 0;
    sp8p = (Unk_59AB5482 *)sp8a;

    temp_r3 = arg1->unk0x64;
    sp8.unk0x0 = temp_r3;
    if (temp_r3 != NULL) {
        CObject_AddRefLink(temp_r3, sp8p);
    }
    while (sp8.unk0x0 != NULL) {
        if (arg2 == 0) {
            if ((s32)*arg3 == var_r30) {
                break;
            }
        } else {
            if (((Unk_C8FEE62D *)sp8.unk0x0)->unk0x18 == arg2) {
                if (arg3 == NULL) {
                    break;
                }
                *arg3 = var_r30;
                break;
            }
        }
        temp_r31 = ((Unk_C8FEE62D *)sp8.unk0x0)->unk0x70;
        if (sp8.unk0x0 != NULL) {
            CObject_RemoveRefLink(sp8.unk0x0, sp8p);
            sp8.unk0x0 = NULL;
        }
        sp8.unk0x0 = temp_r31;
        if (temp_r31 != NULL) {
            CObject_AddRefLink(temp_r31, sp8p);
        }
        var_r30 += 1;
    }
    arg0->unk0x4 = NULL;
    arg0->unk0x8 = NULL;
    arg0->unk0x0 = sp8.unk0x0;
    if (sp8.unk0x0 != NULL) {
        CObject_AddRefLink(sp8.unk0x0, arg0);
    }
    if (sp8.unk0x0 != NULL) {
        CObject_RemoveRefLink(sp8.unk0x0, sp8p);
        sp8.unk0x0 = NULL;
    }
    return arg0;
}
