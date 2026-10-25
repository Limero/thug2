// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F9AC-0x8009FA3C (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { s16 off; s16 pad; void (*fn)(void *, s32); } Ent;
typedef struct { char pad[0x48]; Ent e; } Vt;
typedef struct { char pad[0x18]; Vt *vt; } Obj;
typedef struct Node { char pad[0x10]; struct Node *next; char pad2[4]; Vt *vt; } Link;
void fn_8009F9AC(Obj *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r0;
    s32 var_r9;
    Link *var_r31;

    temp_r0 = *(s32 *)((char *)arg0 + 0x114);
    var_r9 = 1;
    if ((temp_r0 & 4) == 0) {
        var_r9 = 0;
    }
    if (arg1 != var_r9) {
        if (arg1 != 0) {
            *(s32 *)((char *)arg0 + 0x114) = temp_r0 | 4;
        } else {
            *(s32 *)((char *)arg0 + 0x114) = temp_r0 & ~4;
        }
        var_r31 = *(Link **)((char *)arg0 + 0x110);
        if (var_r31 != 0) {
            do {
                var_r31->vt->e.fn((char *)var_r31 + var_r31->vt->e.off, arg1);
                var_r31 = var_r31->next;
            } while (var_r31 != 0);
        }
    }
}
