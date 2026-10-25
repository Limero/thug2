// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2E88-0x801A2F2C (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* vtable-method table: +0x38 is a SIGNED 16-bit `this` offset (retail uses
   `lha`, not `lwz`), +0x3C the method pointer. */
typedef struct A2E88_vt {
    char pad0x0[0x38];
    s16 unk0x38;
    s32 (*unk0x3C)(void *);
} A2E88_vt;

/* list node: +0x4 is a sentinel counter (-1 terminates), +0xC the next link */
typedef struct A2E88_node {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x4];
    struct A2E88_node *unk0xC;
} A2E88_node;

/* object: +0x14 is the method table */
typedef struct A2E88_obj {
    char pad0x0[0x14];
    A2E88_vt *unk0x14;
} A2E88_obj;

extern s32 fn_801A275C(Unk_31DE137E *arg0, s32 arg1);
extern void *fn_801A26E0(Unk_31DE137E *arg0, s32 arg1);

s32 fn_801A2E88(Unk_31DE137E *arg0, s32 arg1) {
    s32 var_r11;
    A2E88_obj *o1;
    A2E88_obj *o2;
    A2E88_vt *vt1;
    A2E88_vt *vt2;
    void *b1;
    void *b2;
    A2E88_node *w;

    w = (A2E88_node *)arg0->unk0x64;
    var_r11 = 0;
    goto chk_2;
 body_2:
    w = w->unk0xC;
    var_r11 += 1;
 chk_2:
    if (w->unk0x4 == -1) {
        w = NULL;
    }
    if (w != NULL) {
        goto body_2;
    }
    if (var_r11 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        o1 = (A2E88_obj *)fn_801A275C(arg0, arg1);
        if (o1 != NULL) {
            vt1 = o1->unk0x14;
            b1 = (char *)o1 + vt1->unk0x38;
            return vt1->unk0x3C(b1);
        }
        return 0;
    }
    o2 = (A2E88_obj *)fn_801A26E0(arg0, 0);
    vt2 = o2->unk0x14;
    b2 = (char *)o2 + vt2->unk0x38;
    return vt2->unk0x3C(b2);
}
