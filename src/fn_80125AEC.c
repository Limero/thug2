// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125AEC-0x80125C70 (388B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029E4B4[];
extern char lbl_8029E4D8[];
extern char lbl_8029E4EC[];
extern char lbl_8029E510[];
extern char lbl_8029E51C[];
extern char lbl_8029E524[];
extern char lbl_8029E52C[];
extern char lbl_8029E534[];
extern char lbl_8029E53C[];
extern char lbl_8029E550[];
extern char lbl_8029E558[];
extern char lbl_8029E568[];
extern char lbl_802FFE98[];

void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8001075C(s32);
void fn_80010760(void);
void fn_8001BC9C(s32);
void fn_80125020(u32, u32);
void fn_80125DAC(s32, s32);
void fn_80125E20(s32, s32);
void fn_80125E94(s32, s32);
void fn_80125F08(s32, s32);
void fn_80125F7C(s32, s32);
void fn_80125FF0(s32, s32);
void fn_80126064(s32, s32);
void fn_801260D8(s32, s32);
void fn_8012614C(s32, s32);
void AllocateChecksumNameLookupTables(void);

// Script_AllocatePools @ 0x80125AEC
void Script_AllocatePools(s32 arg0) {
    Unk_C7387A53 *temp_r3;

    fn_8001075C((s32)lbl_8029E4B4);
    AllocateChecksumNameLookupTables();
    fn_80010760();
    temp_r3 = *(Unk_C7387A53 **)lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x164);
    fn_8001BC9C(1);
    fn_8001075C((s32)lbl_8029E4D8);
    fn_80125DAC(300, (s32)lbl_8029E4D8);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E4EC);
    fn_80125E20(86000, (s32)lbl_8029E510);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E51C);
    fn_80125E94(19800, (s32)lbl_8029E51C);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E524);
    fn_80125F08(9500, (s32)lbl_8029E524);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E52C);
    fn_80125F7C(800, (s32)lbl_8029E52C);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E534);
    fn_80125FF0(7000, (s32)lbl_8029E534);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E53C);
    fn_80126064(12500, (s32)lbl_8029E53C);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E550);
    fn_801260D8(300, (s32)lbl_8029E550);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E558);
    fn_8012614C(100, (s32)lbl_8029E558);
    fn_80010760();
    fn_8001075C((s32)lbl_8029E568);
    fn_80125020(190000, 7000);
    fn_80010760();
    fn_8000F320(*(Unk_F12C5E01 **)lbl_802FFE98);
    fn_8001BC9C(3);
}
