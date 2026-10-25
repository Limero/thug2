// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004C858-0x8004C900 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* arg0+0x5D8: 10 x { u32 value; u32 enabled; u8 _pad[0x10]; } */
typedef struct { u32 val; u32 flag; char _pad[0x10]; } Elem_t;

void GetElement_2(void *, s32, s32, s32);
s32 fn_800421CC(Unk_31DE137E *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

s32 fn_8004C858(Unk_C7387A53 *arg0, s32 arg1) {
    struct { void *f0; s32 f4; s32 f8; } sp8;
    Elem_t *p;
    u32 var_r31;
    s32 temp_r9;
    s32 temp_r3;
    s32 var_ctr;

    var_r31 = 0;
    GetElement_2(&sp8, arg0, arg1, 1);
    temp_r9 = fn_800421CC(sp8.f0);
    var_ctr = 0xA;
    p = (Elem_t *)((char *)arg0 + 0x5D8);
    do {
        if (p->flag != 0) {
            if (p->val > var_r31) {
                var_r31 = p->val;
            }
        }
        p++;
        var_ctr -= 1;
    } while (var_ctr != 0);
    temp_r3 = *(s32 *)&sp8.f0;
    temp_r9 = var_r31 ^ temp_r9;
    var_r31 = (temp_r9 == 0);
    if (temp_r3 != 0) {
        CObject_RemoveRefLink((CStruct *)temp_r3, (CStruct *)&sp8);
        sp8.f0 = 0;
    }
    return var_r31;
}
