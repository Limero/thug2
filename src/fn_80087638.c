// Identification: appearance/material initializer for the skater-graphics component
// (base ctor fn_80066834, vtables 0x80296710/0x80296728). Resolves the appearance-material
// keyword (arg3) in the active-appearance table via fn_8005CF80 and stores the resulting
// handle at unk0x174; maps the QB blend-mode keyword (arg4) to a renderer blend-mode index
// via fn_80081794, stored as a byte at unk0x170. Takes two unused leading args (r4/r5).
// Suggested rename: InitAppearanceMaterials.
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80087638-0x800876BC (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80081794(s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
void fn_80066834(void);
extern Unk_9994C3F5 * lbl_80366478;
extern char lbl_80296710[];
extern char lbl_80296728[];
void *fn_80087638(Unk_DCEB657B *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk_C7387A53 *temp_r3;

    fn_80066834();
    arg0->unk0x20 = (s32)lbl_80296710;
    arg0->unk0x8 = (s32)lbl_80296728;
    arg0->unk0x174 = 0;
    temp_r3 = (Unk_C7387A53 *)fn_8005CF80(lbl_80366478, arg3);
    if (temp_r3 != NULL) {
        arg0->unk0x174 = (s32)temp_r3->unk0xC;
    }
    arg0->unk0x170 = (u8)fn_80081794(arg4);
    return arg0;
}
