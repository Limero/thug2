// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A33BC-0x801A3438 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct A33BC_node {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x4];
    struct A33BC_node *unk0xC;
} A33BC_node;

typedef struct A33BC_self {
    char pad0x0[0x64];
    A33BC_node *unk0x64;
} A33BC_self;

void *fn_801A26E0(A33BC_self *, s32);
s32 fn_801A275C(A33BC_self *, s32);
s32 fn_800AB348(void *);

s32 fn_801A33BC(A33BC_self *arg0, s32 arg1) {
    s32 var_r11;
    void *var_r3;
    A33BC_node *var_r9;
    register s32 t __asm__("r3");

    var_r9 = arg0->unk0x64;
    var_r11 = 0;
    goto check;
    do {
loop_2:
        var_r9 = var_r9->unk0xC;
        var_r11 += 1;
check:
        if (var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
    } while (var_r9 != NULL);
    if (var_r11 != 0) {
        if (arg1 == 0) {
            var_r3 = fn_801A26E0(arg0, 0);
        } else {
            var_r3 = fn_801A275C(arg0, arg1);
        }
        t = (s32) var_r3;
        if (t != 0) {
            return fn_800AB348((void *) t);
        }
        return 0;
    }
    return 0;
}
