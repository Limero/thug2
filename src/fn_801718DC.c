// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801718DC-0x80171958 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_8016F120(s32, s32, Unk_DB0E2BAB *);
void fn_80170930(void *, s32);
void fn_801718DC(Unk_E9D95610 *arg0) {
    s32 sp8;
    s32 temp_r3;
    s32 temp_r4;
    s32 n;
    char *var_r30;
    void *var_r31;
    void *spp;
    register s32 a0 __asm__("r28");

    a0 = (s32) arg0;
    var_r30 = (char *) a0 + 0xC;
    var_r31 = (char *) a0 + 0x15C;
    spp = &sp8;
    n = 2;
    do {
        temp_r4 = ((CStruct *) var_r31)->unk0x0;
        temp_r3 = *(s32 *) ((char *) var_r31 - 0x8);
        var_r31 += 0x190;
        GetStructure_2(temp_r3, temp_r4, spp, 1);
        fn_8016F120(a0, sp8, (Unk_DB0E2BAB *) var_r30);
        var_r30 += 0x190;
        n -= 1;
    } while (n != 0);
    fn_80170930((void *) a0, 0);
    *(s32 *) ((char *) a0 + 0x354) = n;
}
